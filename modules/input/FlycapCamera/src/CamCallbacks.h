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

#ifndef MODULES_INPUT_CAMCALLBACKS_H
#define MODULES_INPUT_CAMCALLBACKS_H

#include <flycapture/FlyCapture2.h>
#include "messages/input/Image.h"

namespace modules {
    namespace input {

        /**
         * @brief This class encapsulates the physical camera device. It will setup a camera device and begin streaming
         *    images
         *
         * @details
         *    This callback function converts a radial lens Bayer format image to rgb to work with NUClear.
         *
         * @author Josiah Walker
         */
        messages::input::Image<0> captureRadial(FlyCapture2::Image& image);
        messages::input::Image<0> captureBayer(FlyCapture2::Image& image);

    }  // input
}  // modules

#endif  // MODULES_INPUT_CAMCALLBACKS_H

