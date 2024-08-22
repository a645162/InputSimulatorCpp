// Input Simulator Cpp Example
// Created by Haomin Kong on 2024/8/22.
//

#include <iostream>

#include "InputSimulator/xInputSimulator.hpp"
#include "InputSimulator/Platform/Windows/WindowsKeyboardExtra.hpp"
#include "InputSimulator/Utils/TimeSleep.hpp"

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
    std::cout << "a: " << (int)anA << " " << sim.charToKeyCode(anA) << std::endl;
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
