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

#ifndef MESSAGES_OUTPUT_SAY_H
#define MESSAGES_OUTPUT_SAY_H

#include <string>

namespace messages {
    namespace output {

        /**
         * TODO document
         *
         * @author Trent Houliston
         */
        struct Say : public std::string {
            Say(std::string message) : std::string(message) {};
        };

    }  // output
}  // messages

#endif  // MESSAGES_OUTPUT_SAY_H