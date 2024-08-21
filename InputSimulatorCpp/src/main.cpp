//    Copyright 2013 Dustin Bensing

//    This file is part of XInputSimulator.

//    XInputSimulator is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.

//    XInputSimulator is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser Public License for more details.

//    You should have received a copy of the GNU Lesser Public License
//    along with XInputSimulator.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>

#include "xInputSimulator.hpp"
#include "Platform/Windows/WindowsKeyboardExtra.hpp"
#include "Utils/TimeSleep.hpp"

int main() {
    std::cout << "Hello World!" << std::endl;

    XInputSimulator &sim = XInputSimulator::getInstance();

    std::cout << "Mouse Simulation:" << std::endl;
    TimeSleep();
    sim.mouseMoveTo(500, 400);
    TimeSleep();
    sim.mouseMoveRelative(400, -100);
    TimeSleep();
    sim.mouseDown(XIS::LEFT_MOUSE_BUTTON);
    TimeSleep();
    sim.mouseMoveRelative(0, 300);
    TimeSleep();
    sim.mouseUp(XIS::LEFT_MOUSE_BUTTON);
    TimeSleep();
    //scroll down and up
    sim.mouseScrollY(10);
    TimeSleep();
    sim.mouseScrollY(-10);
    //scroll left and right
    TimeSleep();
    sim.mouseScrollX(10);
    TimeSleep();
    sim.mouseScrollX(-10);

    std::cout << "Keyboard Simulation:" << std::endl;
#if defined(__linux__) || defined(__APPLE__)
    char anA = 'a';
    cout << "a: " << (int)anA << " " << sim.charToKeyCode(anA) << endl;
    std::cout << std::endl;
    TimeSleep();
    sim.keyClick(sim.charToKeyCode(anA));
    std::cout << std::endl;
    TimeSleep();
    sim.keySequence(" Simple sentence Here 123 ");
#elif _WIN32
    // Ctrl+A
    sim.keyDown(VK_CONTROL);
    sim.keyClick(VK_A);
    sim.keyUp(VK_CONTROL);
#endif

    TimeSleep();

    std::cout << "Done!" << std::endl;

    return 0;
}
