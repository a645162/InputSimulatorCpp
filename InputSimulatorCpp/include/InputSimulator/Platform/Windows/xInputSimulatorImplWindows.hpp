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

#ifndef X_INPUT_SIMULATOR_IMPL_WINDOWS_H
#define X_INPUT_SIMULATOR_IMPL_WINDOWS_H

#include "InputSimulator/Common/xInputSimulatorImpl.hpp"

class XInputSimulatorImplWin : public XInputSimulatorImpl {
private:
    int currentX;
    int currentY;

    void initCurrentMousePosition();

public:
    XInputSimulatorImplWin();

    ~XInputSimulatorImplWin() {}

    virtual void mouseMoveTo(int x, int y) override;

    virtual void mouseMoveRelative(int x, int y) override;

    virtual void mouseDown(int button) override;

    virtual void mouseUp(int button) override;

    virtual void mouseClick(int button) override;

    virtual void mouseScrollX(int length) override;

    virtual void mouseScrollY(int length) override;

    virtual void keyDown(int key) override;

    virtual void keyUp(int key) override;

    virtual void keyClick(int key) override;

    virtual int charToKeyCode(char key_char) override;

    virtual void keySequence(const std::string &sequence) override;
};

#endif // X_INPUT_SIMULATOR_IMPL_WINDOWS_H

#endif //_WIN32
