// Input Simulator Linux Implementation
// Modified by: Haomin Kong

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

#ifndef X_INPUT_SIMULATOR_IMPL_LINUX_H
#define X_INPUT_SIMULATOR_IMPL_LINUX_H

#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#undef Bool //fix C #define Bool int in C++ Qt moc from x11

#include "InputSimulator/Common/xInputSimulatorImpl.hpp"

class XInputSimulatorImplLinux : public XInputSimulatorImpl
{
private:
    Display* display;
    Window root;
    XEvent event;

    size_t displayX;
    size_t displayY;

    void initMouseEvent(int button);

public:
    XInputSimulatorImplLinux();
    ~XInputSimulatorImplLinux() override;

    void mouseMoveTo(int x, int y) override;
    void mouseMoveRelative(int x, int y) override;
    void mouseDown(int button) override;
    void mouseUp(int button) override;
    void mouseClick(int button) override;
    void mouseScrollX(int length) override;
    void mouseScrollY(int length) override;

    void keyDown(int key) override;
    void keyUp(int key) override;
    void keyClick(int key) override;

    int charToKeyCode(char key_char) override;
    void keySequence(const std::string& sequence) override;
};

#endif // __linux__

#endif // X_INPUT_SIMULATOR_IMPL_LINUX_H
