// Keyboard Macros and Function
// Created by Haomin Kong on 2024/8/23.
// https://github.com/a645162/InputSimulatorCpp
// Notice: This project and `XInputSimulator` are licensed under the GPL-3.0 License.

#ifndef INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_H
#define INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_H

#ifdef _WIN32

#include "Platform/Windows/KeyboardKeyCodeWindows.hpp"

#elif __APPLE__

#include "Platform/macOS/KeyboardKeyCodeMacOS.hpp"

#elif __linux__

#include "Platform/Linux/KeyboardKeyCodeLinux.hpp"

#endif

#endif // INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_H
