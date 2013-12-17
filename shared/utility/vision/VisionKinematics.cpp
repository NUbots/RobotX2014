/*
 * This file is part of NUBots Utility.
 *
 * NUBots Utility is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NUBots Utility is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NUBots Utility.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 NUBots <nubots@nubots.net>
 */

#include "VisionKinematics.h"

namespace utility {
    namespace vision {

        VisionKinematics::VisionKinematics() {
            m_FOV = {0, 0};
            m_effectiveCameraDistancePixels = 0;

            m_headPitch = m_headYaw = m_bodyRoll = 0;

            neck_position = {0, 0, 0};

            m_imageSize = {0, 0};
            m_imageCentre = {0, 0};
            m_tanHalfFOV = {0, 0};
            m_screenToRadialFactor = {0, 0};
        }

        VisionKinematics::VisionKinematics(const SensorCalibration& calibration) {
            setCalibration(calibration);
        }

        void VisionKinematics::setCalibration(const SensorCalibration& calibration) {
            m_sensorCalibration = calibration;
            preCalculateTransforms();
        }

        SensorCalibration VisionKinematics::getCalibration() {
          return m_sensorCalibration;
        }

        /**
          * Applies radial distortion correction to the given pixel location.
          * @param pt The pixel location to correct.
          */
        arma::vec2 VisionKinematics::correctDistortion(float RADIAL_CORRECTION_COEFFICIENT, const arma::vec2& point) {
            //get position relative to centre
            arma::vec2 halfSize = m_imageSize * 0.5;
            arma::vec2 centreRelative = point - halfSize;

            // Calculate correction factor -> 1+kr^2
        //    double correctionFactor = (1 + (VisionConstants::RADIAL_CORRECTION_COEFFICIENT * centreRelative.squareAbs());
            double correctionFactor = (1 + (RADIAL_CORRECTION_COEFFICIENT * arma::dot(centreRelative, centreRelative));

            // Multiply by factor.
            arma::vec2 result = centreRelative * correctionFactor;

            // Scale the edges back out to meet again.
            result[0] /= (1 + (RADIAL_CORRECTION_COEFFICIENT * halfSize[0] * halfSize[0]));
            result[1] /= (1 + (RADIAL_CORRECTION_COEFFICIENT * halfSize[1] * halfSize[1]));

            // Get the original position back from the centre relative position.
            return (result + halfSize);
        }

        void VisionKinematics::preCalculateTransforms() {
            #define ROLL   0        // X-axis
            #define PITCH  1        // Y-axis
            #define YAW    2        // Z-axis

            // Uses the following member variables:
            // m_headPitch, m_headYaw, m_bodyRoll, m_bodyPitch, m_sensorCalibration

            // Results written to:
            // m_camVector, m_camV2RobotRotation

            // Varibles for orientations.
            arma::vec3 cameraOrientation = m_sensorCalibration.m_cameraAngleOffset;
            arma::vec3 headOrientation = {0, 0, 0};
            arma::vec2 bodyOrientation = m_sensorCalibration.m_bodyAngleOffset;

            // Add the joint values.
            headOrientation[PITCH] += m_headPitch;
            headOrientation[YAW] += m_headYaw;

            bodyOrientation[ROLL] += m_bodyRoll;
            bodyOrientation[PITCH] += m_bodyPitch;

            // Calculate rotation matrices
            arma::mat bodyRoll_rot = utility::math::matrix::xRotMatrix(bodyOrientation[ROLL]);
            arma::mat bodyPitch_rot = utility::math::matrix::yRotMatrix(bodyOrientation[PITCH]);

            arma::mat headPitch_rot = utility::math::matrix::yRotMatrix(headOrientation[PITCH]);
            arma::mat headYaw_rot = utility::math::matrix::zRotMatrix(headOrientation[YAW]);

            arma::mat cameraRoll_rot = utility::math::matrix::xRotMatrix(cameraOrientation[ROLL]);
            arma::mat cameraPitch_rot = utility::math::matrix::yRotMatrix(cameraOrientation[PITCH]);
            arma::mat cameraYaw_rot = utility::math::matrix::zRotMatrix(cameraOrientation[YAW]);
            arma::mat headV2RobotRotation = bodyRoll_rot * bodyPitch_rot * headYaw_rot * headPitch_rot;

            m_camVector = (headV2RobotRotation * m_sensorCalibration.m_cameraPositionOffset) + m_neckPosition;
            m_camV2RobotRotation = headV2RobotRotation * cameraPitch_rot * cameraRoll_rot * cameraYaw_rot;

            #undef ROLL   0
            #undef PITCH  1
            #undef YAW    2
        }

        void VisionKinematics::calculateRepresentationsFromPixelLocation(NUPoint& point, bool known_distance, double val) const {
            // Calculate the radial position (relative to the camera vector) from the pixel position.
            point.screenAngular[0] = atan((m_imageCentre[0] - point.screenCartesian[0]) * m_screenToRadialFactor[0]);
            point.screenAngular[1] = atan((m_imageCentre[1] - point.screenCartesian[1]) * m_screenToRadialFactor[1]);

            if (known_distance) {
                // In this case val represents known distance (for e.g. found by perspective comparison).
                arma::vec3 imagePositionSpherical({val, point.screenAngular[0], point.screenAngular[1]});
                point.neckRelativeRadial = utility::math::coordinates::Cartesian2Spherical(camV2RobotRotation * utility::math::coordinates::Spherical2Cartesian(imagePositionSpherical));
            }

            else {
                // In this case val represents known height
                // Calculate the radial position relative to
                point.neckRelativeRadial = distanceToPoint(point.screenCartesian, val);
            }

            point.groundCartesian[0] = cos(point.neckRelativeRadial[2]) * cos(point.neckRelativeRadial[1]) * point.neckRelativeRadial[0];
            point.groundCartesian[1] = cos(point.neckRelativeRadial[2]) * sin(point.neckRelativeRadial[1]) * point.neckRelativeRadial[0];
        }

        void VisionKinematics::calculateRepresentationsFromPixelLocation(std::vector<NUPoint>& points, bool knownDistance, double val) const {
            for (NUBots& point : points) {
                calculateRepresentationsFromPixelLocation(point, knownDistance, val);
            }
        }

        void VisionKinematics::calculateRepresentationsFromGroundCartesianLocation(NUPoint& point) const {
            //           (top down view)                (side view)         //
            //                     /|                  __________           //
            //                    / |                 |\e                   //
            //                   /  |                 | \                   //
            //      ground_dist /   |                 |  \                  //
            //                 /    | y        neck_h |   \ neck_dist       //
            //                /     |                 |    \                //
            //               /      |                 |     \               //
            //              /B______|                 |______\              //
            //                   x                   ground_dist            //

            // B - bearing
            // e - elevation


            // Get bearing from ground position.
            point.neckRelativeRadial[1] = atan2(point.groundCartesian[1], point.groundCartesian[0]);

            // Get distance along ground.
            double groundDistance = arma::norm(point.groundCartesian, 2);

            // Use this and the known neck height to determine the neck distance.
            point.neckRelativeRadial[0] = sqrt((groundDistance * groundDistance) + (m_neckPosition[2] * m_neckPosition[2]);

            // And the neck bearing.
            point.neckRelativeRadial[1] = atan2(groundDistance, m_neckPosition[2]);

            /// @todo We need to find the screen relative coordinates
        }

        void VisionKinematics::calculateRepresentationsFromGroundCartesianLocation(std::vector<NUPoint>& points) const {
            for (NUPoint& point : points) {
                calculateRepresentationsFromGroundCartesianLocation(point);
            }
        }

        //NUPoint VisionKinematics::calculateRepresentations(const arma::vec2& point, bool ground = true, double val = 0.0) const {
        //    NUPoint np;
        //    np.screenCartesian = point;
        //    calculateRepresentations(np);
        //    return np;
        //}

        //std::vector<NUPoint> VisionKinematics::calculateRepresentations(const vector<arma::vec2>& points, bool ground = true, double val = 0.0) const
        //{
        //    std::vector<NUPoint> nps;
        //
        //    for (const auto& point : points) {
        //        nps.push_back(calculateRepresentations(point));
        //    }
        //
        //    return nps;
        //}


        ///// @note Assumes radial calculation already done
        //void VisionKinematics::radial2DToRadial3D(NUPoint& point, double distance) const {
        //    arma::vec3 imagePositionSpherical({distance, point.screenAngular[0], point.screenAngular[1]});
        //    point.neckRelativeRadial = utility::math::coordinates::Cartesian2Spherical(camV2RobotRotation * utility::math::coordinates::Spherical2Cartesian(imagePositionSpherical));
        //}

        double VisionKinematics::getCameraDistanceInPixels() const {
            return m_effectiveCameraDistancePixels;
        }


        arma::vec2& VisionKinematics::getFOV() const {
            return FOV;
        }

        /**
          * Calculates the distance to a point at a given height
          * @param pixel The pixel location in the image relative to the top left of the screen.
          * @param object_height The height of the point to be measured (from the ground).
          * @return A 3 dimensional vector containing the distance, bearing and elevation to the point.
          */
        arma::vec3 VisionKinematics::distanceToPoint(arma::vec2 pixel, double objectHeight) const {
            arma::vec3 result;

            arma::mat vcam(3, 1, fill::zeros);
            vcam[0][0] = m_effectiveCameraDistancePixels;
            vcam[1][0] = (m_imageSize[0] * 0.5) - pixel[0];
            vcam[2][0] = (m_imageSize[1] * 0.5) - pixel[1];

            arma::mat roboVdir = camV2RobotRotation * vcam;
            double alpha = (objectHeight - camVector[2][0]) / roboVdir[2][0];
            arma::mat v2FieldPoint = (alpha * roboVdir) + camVector;

            result[0] = arma::norm(arma::vec3({v2FieldPoint[0][0], v2FieldPoint[1][0], (objectHeight - camVector[2][0])}), 2);
            result[1] = std::atan2((double)v2FieldPoint[1][0], (double)v2FieldPoint[0][0]);
            result[2] = std::asin((objectHeight - (double)camVector[2][0]) / (double)result[0]);

            return result;
        }

        //void VisionKinematics::screenToGroundCartesian(NUPoint& point) const {
        //    arma::vec3 v = distanceToPoint(point.screenCartesian, 0.0);
        //
        //    arma::vec3 sphericalFootRelative = Kinematics::TransformPosition(ctgRransform, v);
        //
        //    arma::vec3 cartesianFootRelative = mathGeneral::Spherical2Cartesian(sphericalFootRelative);
        //
        //    point.groundCartesian = arma::vec2({cartesianFootRelative[0], cartesianFootRelative[1]});
        //}

        //void VisionKinematics::screenToGroundCartesian(vector<NUPoint>& points) const {
        //    for (NUPoint& point : points) {
        //        screenToGroundCartesian(point);
        //    }
        //}

        //NUPoint VisionKinematics::screenToGroundCartesian(const arma::vec2& point) const {
        //    NUPoint ground;
        //    ground.screenCartesian = point;
        //    screenToGroundCartesian(ground);
        //    return ground;
        //}

        //std::vector<NUPoint> VisionKinematics::screenToGroundCartesian(const std::vector<arma::vec2>& points) const {
        //    std::vector<NUPoint> groundPoints;
        //
        //    for (const arma::vec2& point : points) {
        //        groundPoints.push_back(screenToGroundCartesian(point));
        //    }
        //
        //    return groundPoints;
        //}

        void VisionKinematics::setSensors(double headPitch, double headYaw, double bodyRoll, double bodyPitch, arma::vec3 neckPosition) {
            m_headPitch = headPitch;
            m_headYaw = headYaw;
            m_bodyPitch = bodyPitch;
            m_bodyRoll = bodyRoll;
            m_neckPosition = neckPosition;

            preCalculateTransforms();
        }

        void VisionKinematics::setCamParams(arma::vec2 imageSize, arma::vec2 FOV) {
            m_imageSize = imageSize;
            m_imageCentre = m_imageSize * 0.5;
            m_FOV = FOV;
            m_tanHalfFOV = arma::vec2({tan(m_FOV[0] * 0.5), tan(m_FOV[1] * 0.5)});
            m_screenToRadialFactor[0] = arma::vec2({m_tanHalfFOV[0] / m_imageCentre[0], m_tanHalfFOV[1] / m_imageCentre[1]});
            //m_screenToRadialFactor[0] = arma::vec2({m_FOV[0] / m_imageCentre[0], m_FOV[1] / m_imageCentre[1]});

            m_effectiveCameraDistancePixels = m_imageCentre[0] / m_tanHalfFOV[0];
        }

    }
}
        