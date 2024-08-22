// Cross Platform Time Sleep Function
// Created by Haomin Kong on 2024/8/22.
// https://github.com/a645162/InputSimulatorCpp
// Notice: This project and `XInputSimulator` are licensed under the GPL-3.0 License.

#include "InputSimulator/Utils/TimeSleep.hpp"

#ifdef __linux__

#include <unistd.h>

#elif __APPLE__

#include <unistd.h>

#elif _WIN32

#include <windows.h>

#endif

#include <chrono>
#include <thread>

void TimeSleep(long ms) {
#if defined(__linux__) || defined(__APPLE__)
    usleep(ms * 1000);
#elif defined(_WIN32)
    Sleep(ms);
#endif
}

// C++ 11
void TimeSleepStd(long ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void TimeSleepSeconds(int seconds) {
#ifdef __linux__
    sleep(seconds);
#elif __APPLE__
    sleep(seconds);
#elif _WIN32
    Sleep(1000 * seconds);
#endif
}
