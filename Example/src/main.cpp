// Input Simulator Cpp Example
// Created by Haomin Kong on 2024/8/22.
//

#include <iostream>

#include "InputSimulator/xInputSimulator.hpp"
#include "InputSimulator/KeyboardKeyCode.hpp"
#include "InputSimulator/Utils/TimeSleep.hpp"

#define ENABLE_MOUSE_SIMULATION

#define ENABLE_KEYBOARD_SIMULATION
#define ENABLE_KEYBOARD_SIMULATION_SHORTCUT
#define ENABLE_KEYBOARD_SIMULATION_TEXT

int main() {
    std::cout << "Hello InputSimulatorCpp Example!" << std::endl;

#ifdef DEBUG_MODE
    std::cout << "Debug Mode" << std::endl;
#endif

    XInputSimulator &sim = XInputSimulator::getInstance();

#ifdef ENABLE_MOUSE_SIMULATION
    std::cout << "Mouse Simulation" << std::endl;
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
#endif // ENABLE_MOUSE_SIMULATION

#ifdef ENABLE_KEYBOARD_SIMULATION
    std::cout << "Keyboard Simulation" << std::endl;
#ifdef ENABLE_KEYBOARD_SIMULATION_SHORTCUT
#if defined(__linux__)
    // Ctrl+A
    sim.keyDown(XK_Control_L);
    TimeSleep(1);
    sim.keyClick(38);
    TimeSleep(1);
    sim.keyUp(XK_Control_L);
    TimeSleep(1);
#elif defined(__APPLE__)
    // Ctrl+A
    sim.keyDown(KEY_COMMAND);
    sim.keyClick(KEY_A);
    sim.keyUp(KEY_COMMAND);
#elif _WIN32
    // Ctrl+A
    sim.keyDown(VK_CONTROL);
    sim.keyClick(VK_A);
    sim.keyUp(VK_CONTROL);
#endif // __linux__ || __APPLE__ || _WIN32
#endif // ENABLE_KEYBOARD_SIMULATION

#ifdef ENABLE_KEYBOARD_SIMULATION_TEXT
    constexpr char single_key_char = 'a';
    std::cout
            << "a: " << static_cast<int>(single_key_char)
            << " " << sim.charToKeyCode(single_key_char)
            << std::endl;
    std::cout << std::endl;
    TimeSleepSeconds(1);
    sim.keyClick(sim.charToKeyCode(single_key_char));
    std::cout << std::endl;
    TimeSleepSeconds(1);

    sim.keySequence(" Simple sentence Here 123 !");
#endif // ENABLE_KEYBOARD_SIMULATION_TEXT
#endif // ENABLE_KEYBOARD_SIMULATION

    TimeSleepSeconds();

    std::cout << "Done!" << std::endl;

    return 0;
}
