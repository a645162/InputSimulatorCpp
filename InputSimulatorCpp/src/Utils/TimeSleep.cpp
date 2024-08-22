// Cross Platform Time Sleep Function
// Created by Haomin Kong on 2024/8/22.
// https://github.com/a645162/InputSimulatorCpp
// Notice: This project and `XInputSimulator` are licensed under the GPL-3.0 License.

#include "InputSimulator/Utils/TimeSleep.hpp"

#ifdef __linux__
//sleep
#include <unistd.h>
#elif __APPLE__
//sleep
#include <unistd.h>
#elif _WIN32
//sleep
#include <windows.h>

#endif

void TimeSleep(int seconds) {
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#ifdef __linux__
    sleep(seconds);
#elif __APPLE__
    sleep(seconds);
#elif _WIN32
    Sleep(1000 * seconds);
#endif
}
