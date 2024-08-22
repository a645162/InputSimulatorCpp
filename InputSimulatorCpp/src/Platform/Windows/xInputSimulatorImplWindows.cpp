// Input Simulator Windows Implementation
// Modified by: Haomin Kong

// The Original Author was not implemented Windows version
// So that I implemented it myself ^_^

// Original License:
/**
    Copyright 2013 Dustin Bensing

    This file is part of XInputSimulator.

    XInputSimulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    XInputSimulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser Public License for more details.

    You should have received a copy of the GNU Lesser Public License
    along with XInputSimulator.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef _WIN32

#include "InputSimulator/Platform/Windows/xInputSimulatorImplWindows.hpp"
#include "InputSimulator/Utils/NotImplementedException.hpp"
#include "InputSimulator/KeyboardKeyCode.hpp"
#include "InputSimulator/Utils/TimeSleep.hpp"

#include <Windows.h>

#define KEYEVENTF_KEYDOWN 0
#define MOUSEEVENTF_HWHEEL 0x01000

XInputSimulatorImplWin::XInputSimulatorImplWin() {
    this->initCurrentMousePosition();
}

void XInputSimulatorImplWin::initCurrentMousePosition() {
    POINT p;
    if (GetCursorPos(&p)) {
        this->currentX = p.x;
        this->currentY = p.y;
    }
}

void XInputSimulatorImplWin::mouseMoveTo(int x, int y) {
    SetCursorPos(x, y);

    this->currentX = x;
    this->currentY = y;
}

void XInputSimulatorImplWin::mouseMoveRelative(int x, int y) {
    int newX = this->currentX + x;
    int newY = this->currentY + y;

    SetCursorPos(newX, newY);

    this->currentX = newX;
    this->currentY = newY;
}

void XInputSimulatorImplWin::mouseDown(int button) {
    INPUT in = {0};
    in.type = INPUT_MOUSE;
    in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &in, sizeof(INPUT));
    ZeroMemory(&in, sizeof(INPUT));
}

void XInputSimulatorImplWin::mouseUp(int button) {
    INPUT in = {0};
    in.type = INPUT_MOUSE;
    in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &in, sizeof(INPUT));
    ZeroMemory(&in, sizeof(INPUT));
}

void XInputSimulatorImplWin::mouseClick(int button) {
    this->mouseDown(button);
    TimeSleep(1);
    this->mouseUp(button);
    TimeSleep(1);
}

void XInputSimulatorImplWin::mouseScrollX(int length) {
    int scrollDirection = 1 * 50; // 1 left -1 right

    if (length < 0) {
        length *= -1;
        scrollDirection *= -1;
    }

    for (int cnt = 0; cnt < length; cnt++) {
        INPUT in;
        in.type = INPUT_MOUSE;
        in.mi.dx = 0;
        in.mi.dy = 0;
        in.mi.dwFlags = MOUSEEVENTF_HWHEEL;
        in.mi.time = 0;
        in.mi.dwExtraInfo = 0;
        in.mi.mouseData = scrollDirection;// WHEEL_DELTA;
        SendInput(1, &in, sizeof(in));
    }
}

void XInputSimulatorImplWin::mouseScrollY(int length) {
    int scrollDirection = -1 * 50; // 1 up -1 down

    if (length < 0) {
        length *= -1;
        scrollDirection *= -1;
    }

    for (int cnt = 0; cnt < length; cnt++) {
        INPUT in;
        in.type = INPUT_MOUSE;
        in.mi.dx = 0;
        in.mi.dy = 0;
        in.mi.dwFlags = MOUSEEVENTF_WHEEL;
        in.mi.time = 0;
        in.mi.dwExtraInfo = 0;
        in.mi.mouseData = scrollDirection;// WHEEL_DELTA;
        SendInput(1, &in, sizeof(in));
    }
}

void XInputSimulatorImplWin::keyDown(int key) {
    keybd_event(static_cast<BYTE>(key), 0, KEYEVENTF_KEYDOWN, 0);
}

void XInputSimulatorImplWin::keyUp(int key) {
    keybd_event(static_cast<BYTE>(key), 0, KEYEVENTF_KEYUP, 0);
}

void XInputSimulatorImplWin::keyClick(int key) {
    keyDown(key);
    TimeSleep(1);
    keyUp(key);
    TimeSleep(1);
}

int XInputSimulatorImplWin::charToKeyCode(char key_char) {
    // Convert to lower case
    key_char = ConvertUpperCaseToLowerCase(key_char);

    /*
     * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
     * 0x3A - 0x40 : unassigned
     * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
     */
    if (key_char >= 'a' && key_char <= 'z') {
        return key_char - 'a' + VK_A;
    }

    if (key_char >= '0' && key_char <= '9') {
        return key_char - '0' + VK_0;
    }

    if (key_char == ' ') {
        return VK_SPACE;
    }

    return -1;
}

void XInputSimulatorImplWin::keySequence(const std::string &sequence) {
    for (char ch: sequence) {
        int key_code = charToKeyCode(ch);
        keyClick(key_code);
        TimeSleep(5);
    }
}

#endif //_WIN32
