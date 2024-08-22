// Keyboard Macros and Function for Windows Keyboard
// Created by Haomin Kong on 2024/8/22.
// https://github.com/a645162/InputSimulatorCpp
// Notice: This project and `XInputSimulator` are licensed under the GPL-3.0 License.

#ifdef _WIN32
#ifndef INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_WINDOWS_H
#define INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_WINDOWS_H

#include <Windows.h>

// Most was defined in `WinUser.h`
/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x3A - 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */

#define VK_0 0x30
#define VK_9 0x39

#define VK_A 0x41
#define VK_Z 0x5A

#endif // INPUT_SIMULATOR_CPP_KEYBOARD_KEY_CODE_WINDOWS_H
#endif
