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

#ifndef MESSAGES_VISION_IMAGESEGMENTSCAN_H
#define MESSAGES_VISION_IMAGESEGMENTSCAN_H

#include <map>
#include <armadillo>

#include "messages/vision/ImagePointScan.h"

namespace messages {
    namespace vision {

        template <int camID>
        struct ImageSegmentScan {

            struct Segment {
                arma::vec2 start;
                arma::vec2 end;

                Segment* previous;
                Segment* next;
            };

            std::multimap<uint32_t, Segment> segments;
            std::shared_ptr<const ImagePointScan<camID>> pointScan;
        };

    }  // vision
}  // messages

#endif  // MESSAGES_VISION_CLASSIFIEDIMAGE_H
