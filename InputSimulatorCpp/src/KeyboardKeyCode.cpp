// Keyboard Macros and Function
// Created by Haomin Kong on 2024/8/23.
// https://github.com/a645162/InputSimulatorCpp
// Notice: This project and `XInputSimulator` are licensed under the GPL-3.0 License.

#include "InputSimulator/KeyboardKeyCode.hpp"

char ConvertUpperCaseToLowerCase(char key_char) {
    if (key_char >= 'A' && key_char <= 'Z') {
        key_char = static_cast<char>(key_char + ('a' - 'A'));
    }

    return key_char;
}

char ConvertLowerCaseToUpperCase(char key_char) {
    if (key_char >= 'a' && key_char <= 'z') {
        key_char = static_cast<char>(key_char - ('a' - 'A'));
    }

    return key_char;
}
