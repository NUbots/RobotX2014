/*
 * This file is part of the NUbots Codebase.
 *
 * The NUbots Codebase is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The NUbots Codebase is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the NUbots Codebase.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 NUBots <nubots@nubots.net>
 */

#include "NUbugger.h"

#include "messages/support/nubugger/proto/Message.pb.h"
#include "messages/input/Image.h"
#include "messages/vision/VisualHorizon.h"
#include "messages/vision/ImagePointScan.h"
#include "messages/vision/ClassifiedImage.h"
// #include "messages/vision/VisionObjects.h"

#include "utility/time/time.h"

namespace modules {
namespace support {
    using messages::support::nubugger::proto::Message;
    using utility::time::getUtcTimestamp;

    using messages::vision::proto::VisionObject;
    using messages::vision::VisualHorizon;
    using messages::vision::ClassifiedImage;
    using messages::vision::ObjectClass;
    using messages::vision::ImagePointScan;
    using messages::input::Image;

    void NUbugger::provideVision() {
        handles["image"].push_back(on<Trigger<Image<0>>, Options<Single, Priority<NUClear::LOW>>>([this](const Image<0>& image) {

            Message message;
            message.set_type(Message::IMAGE);
            message.set_filter_id(1);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* imageData = message.mutable_image();

            imageData->mutable_dimensions()->set_x(image.width());
            imageData->mutable_dimensions()->set_y(image.height());

            std::string* imageBytes = imageData->mutable_data();

            imageData->set_camera_id(0);

            // TODO work out the format
            imageData->set_format(messages::input::proto::Image::YCbCr444);

            // Reserve enough space in the image data to store the output
            imageBytes->reserve(image.source.size());

            imageBytes->insert(imageBytes->begin(), std::begin(image.source), std::end(image.source));


            send(message);
        }));

        handles["image"].push_back(on<Trigger<Image<1>>, Options<Single, Priority<NUClear::LOW>>>([this](const Image<1>& image) {

            Message message;
            message.set_type(Message::IMAGE);
            message.set_filter_id(2);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* imageData = message.mutable_image();

            imageData->mutable_dimensions()->set_x(image.width());
            imageData->mutable_dimensions()->set_y(image.height());

            std::string* imageBytes = imageData->mutable_data();

            imageData->set_camera_id(1);

            // TODO work out the format
            imageData->set_format(messages::input::proto::Image::YCbCr444);

            // Reserve enough space in the image data to store the output
            imageBytes->reserve(image.source.size());

            imageBytes->insert(imageBytes->begin(), std::begin(image.source), std::end(image.source));


            send(message);
        }));

        handles["image"].push_back(on<Trigger<Image<2>>, Options<Single, Priority<NUClear::LOW>>>([this](const Image<2>& image) {

            Message message;
            message.set_type(Message::IMAGE);
            message.set_filter_id(3);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* imageData = message.mutable_image();

            imageData->mutable_dimensions()->set_x(image.width());
            imageData->mutable_dimensions()->set_y(image.height());

            std::string* imageBytes = imageData->mutable_data();

            imageData->set_camera_id(2);

            // TODO work out the format
            imageData->set_format(messages::input::proto::Image::YCbCr444);

            // Reserve enough space in the image data to store the output
            imageBytes->reserve(image.source.size());

            imageBytes->insert(imageBytes->begin(), std::begin(image.source), std::end(image.source));


            send(message);
        }));

        handles["image"].push_back(on<Trigger<Image<3>>, Options<Single, Priority<NUClear::LOW>>>([this](const Image<3>& image) {

            Message message;
            message.set_type(Message::IMAGE);
            message.set_filter_id(4);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* imageData = message.mutable_image();

            imageData->mutable_dimensions()->set_x(image.width());
            imageData->mutable_dimensions()->set_y(image.height());

            std::string* imageBytes = imageData->mutable_data();

            imageData->set_camera_id(3);

            // TODO work out the format
            imageData->set_format(messages::input::proto::Image::YCbCr444);

            // Reserve enough space in the image data to store the output
            imageBytes->reserve(image.source.size());

            imageBytes->insert(imageBytes->begin(), std::begin(image.source), std::end(image.source));


            send(message);
        }));

        // handles["visual_horizon"].push_back(on<Trigger<VisualHorizon<0>>, Options<Single, Priority<NUClear::LOW>>>([this] (const VisualHorizon<0>& horizon) {

        //     Message message;
        //     message.set_type(Message::VISUAL_HORIZON);
        //     message.set_filter_id(1);
        //     message.set_utc_timestamp(getUtcTimestamp());

        //     auto* h = message.mutable_visual_horizon();

        //     h->set_camera_id(0);

        //     h->mutable_lens()->mutable_radial()->set_fov(horizon.image->lens.parameters.radial.fov);
        //     h->mutable_lens()->mutable_radial()->set_pitch(horizon.image->lens.parameters.radial.pitch);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_x(horizon.image->lens.parameters.radial.centre[0]);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_y(horizon.image->lens.parameters.radial.centre[1]);

        //     for(uint i = 0; i < horizon.horizon.n_rows; ++i) {
        //         auto* hPoint = h->add_normals();

        //         hPoint->set_x(horizon.horizon(i, 0));
        //         hPoint->set_y(horizon.horizon(i, 1));
        //         hPoint->set_z(horizon.horizon(i, 2));
        //     }

        //     send(message);
        // }));


        // handles["visual_horizon"].push_back(on<Trigger<VisualHorizon<1>>, Options<Single, Priority<NUClear::LOW>>>([this] (const VisualHorizon<1>& horizon) {

        //     Message message;
        //     message.set_type(Message::VISUAL_HORIZON);
        //     message.set_filter_id(2);
        //     message.set_utc_timestamp(getUtcTimestamp());

        //     auto* h = message.mutable_visual_horizon();

        //     h->set_camera_id(1);

        //     h->mutable_lens()->mutable_radial()->set_fov(horizon.image->lens.parameters.radial.fov);
        //     h->mutable_lens()->mutable_radial()->set_pitch(horizon.image->lens.parameters.radial.pitch);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_x(horizon.image->lens.parameters.radial.centre[0]);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_y(horizon.image->lens.parameters.radial.centre[1]);

        //     for(uint i = 0; i < horizon.horizon.n_rows; ++i) {
        //         auto* hPoint = h->add_normals();

        //         hPoint->set_x(horizon.horizon(i, 0));
        //         hPoint->set_y(horizon.horizon(i, 1));
        //         hPoint->set_z(horizon.horizon(i, 2));
        //     }

        //     send(message);
        // }));

        // handles["visual_horizon"].push_back(on<Trigger<VisualHorizon<2>>, Options<Single, Priority<NUClear::LOW>>>([this] (const VisualHorizon<2>& horizon) {

        //     Message message;
        //     message.set_type(Message::VISUAL_HORIZON);
        //     message.set_filter_id(3);
        //     message.set_utc_timestamp(getUtcTimestamp());

        //     auto* h = message.mutable_visual_horizon();

        //     h->set_camera_id(2);

        //     h->mutable_lens()->mutable_radial()->set_fov(horizon.image->lens.parameters.radial.fov);
        //     h->mutable_lens()->mutable_radial()->set_pitch(horizon.image->lens.parameters.radial.pitch);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_x(horizon.image->lens.parameters.radial.centre[0]);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_y(horizon.image->lens.parameters.radial.centre[1]);

        //     for(uint i = 0; i < horizon.horizon.n_rows; ++i) {
        //         auto* hPoint = h->add_normals();

        //         hPoint->set_x(horizon.horizon(i, 0));
        //         hPoint->set_y(horizon.horizon(i, 1));
        //         hPoint->set_z(horizon.horizon(i, 2));
        //     }

        //     send(message);
        // }));


        // handles["visual_horizon"].push_back(on<Trigger<VisualHorizon<3>>, Options<Single, Priority<NUClear::LOW>>>([this] (const VisualHorizon<3>& horizon) {

        //     Message message;
        //     message.set_type(Message::VISUAL_HORIZON);
        //     message.set_filter_id(4);
        //     message.set_utc_timestamp(getUtcTimestamp());

        //     auto* h = message.mutable_visual_horizon();

        //     h->set_camera_id(3);

        //     h->mutable_lens()->mutable_radial()->set_fov(horizon.image->lens.parameters.radial.fov);
        //     h->mutable_lens()->mutable_radial()->set_pitch(horizon.image->lens.parameters.radial.pitch);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_x(horizon.image->lens.parameters.radial.centre[0]);
        //     h->mutable_lens()->mutable_radial()->mutable_centre()->set_y(horizon.image->lens.parameters.radial.centre[1]);

        //     for(uint i = 0; i < horizon.horizon.n_rows; ++i) {
        //         auto* hPoint = h->add_normals();

        //         hPoint->set_x(horizon.horizon(i, 0));
        //         hPoint->set_y(horizon.horizon(i, 1));
        //         hPoint->set_z(horizon.horizon(i, 2));
        //     }

        //     send(message);
        // }));

        handles["point_scan"].push_back(on<Trigger<ImagePointScan<0>>, Options<Single, Priority<NUClear::LOW>>>([this] (const ImagePointScan<0>& scan) {

            Message message;
            message.set_type(Message::POINT_SCAN);
            message.set_filter_id(1);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* s = message.mutable_point_scan();

            s->set_camera_id(0);

            s->mutable_lens()->mutable_radial()->set_fov(scan.horizon->image->lens.parameters.radial.fov);
            s->mutable_lens()->mutable_radial()->set_pitch(scan.horizon->image->lens.parameters.radial.pitch);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_x(scan.horizon->image->lens.parameters.radial.centre[0]);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_y(scan.horizon->image->lens.parameters.radial.centre[1]);

            for(auto& set : scan.points) {
                for(auto& point : set.second) {
                    auto* p = s->add_points();

                    p->set_colour(set.first);
                    p->mutable_ray()->set_x(point[0]);
                    p->mutable_ray()->set_y(point[1]);
                }
            }

            send(message);
        }));

        handles["point_scan"].push_back(on<Trigger<ImagePointScan<1>>, Options<Single, Priority<NUClear::LOW>>>([this] (const ImagePointScan<1>& scan) {

            Message message;
            message.set_type(Message::POINT_SCAN);
            message.set_filter_id(2);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* s = message.mutable_point_scan();

            s->set_camera_id(1);

            s->mutable_lens()->mutable_radial()->set_fov(scan.horizon->image->lens.parameters.radial.fov);
            s->mutable_lens()->mutable_radial()->set_pitch(scan.horizon->image->lens.parameters.radial.pitch);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_x(scan.horizon->image->lens.parameters.radial.centre[0]);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_y(scan.horizon->image->lens.parameters.radial.centre[1]);

            for(auto& set : scan.points) {
                for(auto& point : set.second) {
                    auto* p = s->add_points();

                    p->set_colour(set.first);
                    p->mutable_ray()->set_x(point[0]);
                    p->mutable_ray()->set_y(point[1]);
                }
            }

            send(message);
        }));

        handles["point_scan"].push_back(on<Trigger<ImagePointScan<2>>, Options<Single, Priority<NUClear::LOW>>>([this] (const ImagePointScan<2>& scan) {

            Message message;
            message.set_type(Message::POINT_SCAN);
            message.set_filter_id(3);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* s = message.mutable_point_scan();

            s->set_camera_id(2);

            s->mutable_lens()->mutable_radial()->set_fov(scan.horizon->image->lens.parameters.radial.fov);
            s->mutable_lens()->mutable_radial()->set_pitch(scan.horizon->image->lens.parameters.radial.pitch);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_x(scan.horizon->image->lens.parameters.radial.centre[0]);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_y(scan.horizon->image->lens.parameters.radial.centre[1]);

            for(auto& set : scan.points) {
                for(auto& point : set.second) {
                    auto* p = s->add_points();

                    p->set_colour(set.first);
                    p->mutable_ray()->set_x(point[0]);
                    p->mutable_ray()->set_y(point[1]);
                }
            }

            send(message);
        }));

        handles["point_scan"].push_back(on<Trigger<ImagePointScan<3>>, Options<Single, Priority<NUClear::LOW>>>([this] (const ImagePointScan<3>& scan) {

            Message message;
            message.set_type(Message::POINT_SCAN);
            message.set_filter_id(4);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* s = message.mutable_point_scan();

            s->set_camera_id(3);

            s->mutable_lens()->mutable_radial()->set_fov(scan.horizon->image->lens.parameters.radial.fov);
            s->mutable_lens()->mutable_radial()->set_pitch(scan.horizon->image->lens.parameters.radial.pitch);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_x(scan.horizon->image->lens.parameters.radial.centre[0]);
            s->mutable_lens()->mutable_radial()->mutable_centre()->set_y(scan.horizon->image->lens.parameters.radial.centre[1]);

            for(auto& set : scan.points) {
                for(auto& point : set.second) {
                    auto* p = s->add_points();

                    p->set_colour(set.first);
                    p->mutable_ray()->set_x(point[0]);
                    p->mutable_ray()->set_y(point[1]);
                }
            }

            send(message);
        }));

        handles["classified_image"].push_back(on<Trigger<ClassifiedImage<ObjectClass, 0>>, Options<Single, Priority<NUClear::LOW>>>([this](const ClassifiedImage<ObjectClass, 0>& image) {

            Message message;
            message.set_type(Message::CLASSIFIED_IMAGE);
            message.set_filter_id(1);
            message.set_utc_timestamp(getUtcTimestamp());

            auto* imageData = message.mutable_classified_image();
            imageData->set_camera_id(0);

            imageData->mutable_dimensions()->set_x(image.dimensions[0]);
            imageData->mutable_dimensions()->set_y(image.dimensions[1]);

            // Add the vertical segments to the list
            for(const auto& segment : image.verticalSegments) {
                auto* s = imageData->add_segment();

                s->set_colour(uint(segment.first));
                s->set_subsample(segment.second.subsample);

                auto* start = s->mutable_start();
                start->set_x(segment.second.start[0]);
                start->set_y(segment.second.start[1]);

                auto* end = s->mutable_end();
                end->set_x(segment.second.end[0]);
                end->set_y(segment.second.end[1]);
            }

            // Add the horizontal segments to the list
            for(const auto& segment : image.horizontalSegments) {
                auto* s = imageData->add_segment();

                s->set_colour(uint(segment.first));
                s->set_subsample(segment.second.subsample);

                auto* start = s->mutable_start();
                start->set_x(segment.second.start[0]);
                start->set_y(segment.second.start[1]);

                auto* end = s->mutable_end();
                end->set_x(segment.second.end[0]);
                end->set_y(segment.second.end[1]);
            }

            // Add in the actual horizon (the points on the left and right side)
            auto* horizon = imageData->mutable_horizon();
            horizon->mutable_normal()->set_x(image.horizon.normal[0]);
            horizon->mutable_normal()->set_y(image.horizon.normal[1]);
            horizon->set_distance(image.horizon.distance);

            for(const auto& visualHorizon : image.visualHorizon) {
                auto* vh = imageData->add_visual_horizon();

                vh->set_x(visualHorizon[0]);
                vh->set_y(visualHorizon[1]);
            }

            send(message);
        }));

        // handles["balls"].push_back(on<Trigger<std::vector<Ball>>, Options<Single, Priority<NUClear::LOW>>>([this] (const std::vector<Ball>& balls) {

        //     Message message;
        //     message.set_type(Message::VISION_OBJECT);
        //     message.set_filter_id(1);
        //     message.set_utc_timestamp(getUtcTimestamp());

        //     auto* object = message.mutable_vision_object();
        //     object->set_type(VisionObject::BALL);

        //     for(const auto& b : balls) {

        //         auto* ball = object->add_ball();

        //         auto* circle = ball->mutable_circle();
        //         circle->set_radius(b.circle.radius);
        //         circle->mutable_centre()->set_x(b.circle.centre[0]);
        //         circle->mutable_centre()->set_y(b.circle.centre[1]);
        //     }

        //     send(message);

        // }));

        // handles["goals"].push_back(on<Trigger<std::vector<Goal>>, Options<Single, Priority<NUClear::LOW>>>([this] (const std::vector<Goal>& goals) {

        //     Message message;
        //     message.set_type(Message::VISION_OBJECT);
        //     message.set_filter_id(2);
        //     message.set_utc_timestamp(getUtcTimestamp());

        //     auto* object = message.mutable_vision_object();

        //     object->set_type(VisionObject::GOAL);

        //     for(const auto& g : goals) {
        //         auto* goal = object->add_goal();

        //         goal->set_side(g.side == Goal::Side::LEFT ? VisionObject::Goal::LEFT
        //                      : g.side == Goal::Side::RIGHT ? VisionObject::Goal::RIGHT
        //                      : VisionObject::Goal::UNKNOWN);

        //         auto* quad = goal->mutable_quad();
        //         quad->mutable_tl()->set_x(g.quad.getTopLeft()[0]);
        //         quad->mutable_tl()->set_y(g.quad.getTopLeft()[1]);
        //         quad->mutable_tr()->set_x(g.quad.getTopRight()[0]);
        //         quad->mutable_tr()->set_y(g.quad.getTopRight()[1]);
        //         quad->mutable_bl()->set_x(g.quad.getBottomLeft()[0]);
        //         quad->mutable_bl()->set_y(g.quad.getBottomLeft()[1]);
        //         quad->mutable_br()->set_x(g.quad.getBottomRight()[0]);
        //         quad->mutable_br()->set_y(g.quad.getBottomRight()[1]);
        //     }

        //     send(message);
        // }));
    }
}
}