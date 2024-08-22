// Input Simulator Cpp Example
// Created by Haomin Kong on 2024/8/22.
//

#include <iostream>

#include "InputSimulator/xInputSimulator.hpp"
#include "InputSimulator/KeyboardKeyCode.hpp"
#include "InputSimulator/Utils/TimeSleep.hpp"

int main() {
    std::cout << "Hello World!" << std::endl;

    XInputSimulator &sim = XInputSimulator::getInstance();

    std::cout << "Mouse Simulation:" << std::endl;
    TimeSleepSeconds();
    sim.mouseMoveTo(500, 400);
    TimeSleepSeconds();
    sim.mouseMoveRelative(400, -100);
    TimeSleepSeconds();
    sim.mouseDown(XIS::LEFT_MOUSE_BUTTON);
    TimeSleepSeconds();
    sim.mouseMoveRelative(0, 300);
    TimeSleepSeconds();
    sim.mouseUp(XIS::LEFT_MOUSE_BUTTON);
    TimeSleepSeconds();
    //scroll down and up
    sim.mouseScrollY(10);
    TimeSleepSeconds();
    sim.mouseScrollY(-10);
    //scroll left and right
    TimeSleepSeconds();
    sim.mouseScrollX(10);
    TimeSleepSeconds();
    sim.mouseScrollX(-10);

    std::cout << "Keyboard Simulation:" << std::endl;
#if defined(__linux__) || defined(__APPLE__)
    char anA = 'a';
    std::cout << "a: " << (int) anA << " " << sim.charToKeyCode(anA) << std::endl;
    std::cout << std::endl;
    TimeSleepSeconds();
    sim.keyClick(sim.charToKeyCode(anA));
    std::cout << std::endl;
    TimeSleepSeconds();
    sim.keySequence(" Simple sentence Here 123 ");

    // Ctrl+A
    sim.keyDown(KEY_COMMAND);
    sim.keyClick(KEY_A);
    sim.keyUp(KEY_COMMAND);
#elif _WIN32
    // Ctrl+A
    sim.keyDown(VK_CONTROL);
    sim.keyClick(VK_A);
    sim.keyUp(VK_CONTROL);
#endif

    TimeSleepSeconds();

    std::cout << "Done!" << std::endl;

    return 0;
}
