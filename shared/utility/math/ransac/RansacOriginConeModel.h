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

#ifndef UTILITY_MATH_RANSAC_RANSACORIGINPLANE_H
#define UTILITY_MATH_RANSAC_RANSACORIGINPLANE_H

#include <armadillo>

namespace utility {
namespace math {
namespace ransac {

    class RansacOriginConeModel {
    public:
        static constexpr size_t REQUIRED_POINTS = 3;
        using DataPoint = arma::vec3;

        RansacOriginConeModel() {}

        bool regenerate(const std::vector<DataPoint>& pts);

        double calculateError(const DataPoint& p) const;

        template <typename Iterator>
        void refineModel(Iterator& first, Iterator& last, const double& candidateThreshold) {
            //refine model using least squares
            // TODO add a least squares regression
            //leastSquaresUpdate(first,last,candidateThreshold);
        }

        arma::vec3 centre;
        double radius;
    };

}
}
}

#endif
