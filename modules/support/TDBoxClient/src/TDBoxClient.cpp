/*
 * This file is part of NUbots Codebase.
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

#include "TDBoxClient.h"

#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

extern "C" {
    #include <sys/socket.h>
    #include <arpa/inet.h>
}

#include "messages/support/Configuration.h"
#include "messages/input/GPS.h"

#include "messages/robotx/UnderwaterPinger.h"
#include "messages/robotx/LightSequence.h"
#include "messages/robotx/AutonomousMode.h"
#include "messages/robotx/CurrentTask.h"

namespace modules {
namespace support {

    using messages::support::Configuration;
    using messages::input::GPS;
    using messages::robotx::UnderwaterPinger;
    using messages::robotx::LightSequence;
    using messages::robotx::AutonomousMode;
    using messages::robotx::CurrentTask;

    void TDBoxClient::reconnect() {
        // Open a file descriptor to the target address
        if(fd) {
            close(fd);
        }

        // Open a new socket
        fd = socket(AF_INET, SOCK_STREAM, 0);

        if (fd < 0) {
            std::system_error(errno, std::system_category(), "Failed to open socket for Technical Director Box");
        }

        // Get the information we need to connect
        sockaddr_in serverAddress;

        std::memset(&serverAddress, 0, sizeof(sockaddr_in));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.s_addr = inet_addr(host.c_str());

        if (connect(fd, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
            std::system_error(errno, std::system_category(), "Failed to connect to the Technical Director Box");
        }
    }

    std::string TDBoxClient::nmeaUTCTime() {

        std::time_t t1 = NUClear::clock::to_time_t(NUClear::clock::now());
        std::tm* wtf = gmtime(&t1);
        std::vector<char> timeOutput(7, 0);
        strftime(timeOutput.data(), timeOutput.size(), "%H%M%S", wtf);

        return timeOutput.data();
    }

    void TDBoxClient::sendNMEA(const std::vector<std::string>& messages) {

        std::lock_guard<std::mutex> lock(sendMutex);

        std::stringstream s;

        // Output the start
        s << "$";

        // Output our list
        for(uint i = 0; i < messages.size(); ++i) {
            s << messages[i];

            // If we have more data comma separate
            if(i < messages.size() - 1) {
                s << ",";
            }
        }

        // Checksum and finish
        uint checksum = 0;
        std::string msg = s.str();
        for(uint i = 1; i < msg.size(); ++i) {
            checksum ^= msg[i];
        }
        s << "*";
        s << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << checksum;
        s << "\r\n";

        // Rebuild the string with the checksum
        msg = s.str();

        // Write to the socket
        int result = send(fd, msg.data(), msg.size(), MSG_NOSIGNAL);

        // Reconnect
        if(result == -1) {
            reconnect();
        }


    }

    TDBoxClient::TDBoxClient(std::unique_ptr<NUClear::Environment> environment)
        : Reactor(std::move(environment)) {


        on<Trigger<Configuration<TDBoxClient>>>([this](const Configuration<TDBoxClient>& config) {

            // Get our config
            port = config["port"].as<uint>();
            host = config["host"].as<std::string>();

            reconnect();
        });

        on<Trigger<Every<1, std::chrono::seconds>>, With<GPS>, With<AutonomousMode>, With<CurrentTask>>([this](const time_t&, const GPS& gps, const AutonomousMode& aut, const CurrentTask& task) {

            // Get our GPS strings
            std::string la = std::to_string(std::fabs(gps.lattitude));
            std::string ns = gps.lattitude > 0 ? "N" : "S";
            std::string lo = std::to_string(std::fabs(gps.longitude));
            std::string ew = gps.longitude > 0 ? "E" : "W";

            std::string a = aut.on ? "2" : "1";
            std::string t = std::to_string(task.ID);

            sendNMEA({
                "RXHRT",       // Header
                nmeaUTCTime(), // Time
                la,            // Latitude
                ns,            // Latitude Direction
                lo,            // Longitude
                ew,            // Longitude Direction
                "NCSTL",       // Team ID
                a,           // Vehicle Mode (1 = rc, 2 = autonomous)
                t            // Current task
            });
        });

        on<Trigger<UnderwaterPinger>>([this](const UnderwaterPinger& pinger) {

            std::string la = std::to_string(std::fabs(pinger.latitude));
            std::string ns = pinger.latitude > 0 ? "N" : "S";
            std::string lo = std::to_string(std::fabs(pinger.longitude));
            std::string ew = pinger.longitude > 0 ? "E" : "W";
            std::string depth = std::to_string(std::fabs(pinger.depth));

            sendNMEA({
                "RXSEA",       // Header
                nmeaUTCTime(), // Time
                "NCSTL",       // Team ID
                pinger.colour, // Buoy Colour
                la,            // Latitude
                ns,            // Latitude Direction
                lo,            // Longitude
                ew,            // Longitude Direction
                depth,            // Pinger depth
            });
        });

        on<Trigger<LightSequence>>([this](const LightSequence& seq) {

            sendNMEA({
                "RXLIT",       // Header
                nmeaUTCTime(), // Time
                "NCSTL",       // Team ID
                seq.sequence   // Light Pattern
            });
        });
    }

}
}

