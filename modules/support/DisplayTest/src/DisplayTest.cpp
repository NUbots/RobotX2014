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

#include "DisplayTest.h"
#include "utility/nubugger/NUhelpers.h"
#include "messages/input/proto/MotionCapture.pb.h"

using utility::nubugger::graph;

namespace modules {
namespace support {

    using messages::input::proto::MotionCapture;

    DisplayTest::DisplayTest(std::unique_ptr<NUClear::Environment> environment) : Reactor(std::move(environment)) {

        // TODO: remove - just for debugging the graph
        /*on<Trigger<Every<100, std::chrono::milliseconds>>>([this](const time_t&) {

            float value = float(rand()) / RAND_MAX * 100;
            emit(graph("Debug", value));

        });*/

        on<Trigger<Network<MotionCapture>>>([this](const Network<MotionCapture>& net) {
//            auto mocap = net.data;
            NUClear::log("I got things from", net.sender);
        });
    }
}
}
