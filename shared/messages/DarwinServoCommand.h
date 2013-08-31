/*
 * This file is part of DarwinPlatform.
 *
 * DarwinPlatform is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * DarwinPlatform is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with DarwinPlatform.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 Trent Houliston <trent@houliston.me>
 */

#ifndef MESSAGES_DARWINSERVOS_H
#define MESSAGES_DARWINSERVOS_H

#include <vector>
#include "DarwinSensors.h"

namespace messages {

    /**
     * TODO
     */
    struct DarwinServoCommand {
        DarwinSensors::Servo::ID servoId;
        float pGain;
        float iGain;
        float dGain;
        float goalPosition;
        float movingSpeed;
    };
};

#endif