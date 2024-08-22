//
// Created by 孔昊旻 on 2024/8/22.
//

#ifndef INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_H
#define INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_H

#ifdef _WIN32

#include "Platform/macOS/KeyboardKeyCodeWindows.hpp"

#elif __APPLE__

#include "Platform/macOS/KeyboardKeyCodeMacOS.hpp"

#elif __linux__

#include "Platform/macOS/KeyboardKeyCodeLinux.hpp"

#endif

#endif // INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_H
