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

#ifdef __linux__

// usleep
#include <unistd.h>

#include "InputSimulator/Platform/Linux/xInputSimulatorImplLinux.hpp"
#include "InputSimulator/Utils/NotImplementedException.hpp"

#include <iostream>

// memset
#include <cstring>

#define USLEEP_TIME 100

XInputSimulatorImplLinux::XInputSimulatorImplLinux()
{
    if ((display = XOpenDisplay(nullptr)) == nullptr)
    {
        std::cerr << "Cannot access display server!" << std::endl;
        return;
    }

    root = DefaultRootWindow(display);

    Screen* pscr = DefaultScreenOfDisplay(display);

    this->displayX = pscr->width;
    this->displayY = pscr->height;

    //XCloseDisplay( pdsp );
}

XInputSimulatorImplLinux::~XInputSimulatorImplLinux()
{
    // Release X11 Display
    // Close the X11 display connection if it's open
    if (display != nullptr)
    {
        XCloseDisplay(display);
        // Set the display pointer to nullptr to avoid dangling pointer issues
        display = nullptr;
    }

    // delete display;
}

void XInputSimulatorImplLinux::initMouseEvent(const int button)
{
    event.xbutton.button = button; //which button
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow(display);
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(
            display, event.xbutton.window,
            &event.xbutton.root, &event.xbutton.subwindow,
            &event.xbutton.x_root, &event.xbutton.y_root,
            &event.xbutton.x, &event.xbutton.y,
            &event.xbutton.state
        );
    }
}

void XInputSimulatorImplLinux::mouseMoveTo(const int x, const int y)
{
    if (!display)
    {
        return;
    }

    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    XFlush(display);

    XEvent event;
    memset(&event, 0, sizeof (event));
}

void XInputSimulatorImplLinux::mouseMoveRelative(const int x, const int y)
{
    if (!display)
    {
        return;
    }

    XWarpPointer(display, None, None, 0, 0, 0, 0, x, y);
    XFlush(display);
}

void XInputSimulatorImplLinux::mouseDown(const int button)
{
    XTestFakeButtonEvent(display, button, true, CurrentTime);
    XFlush(display);
}

void XInputSimulatorImplLinux::mouseUp(const int button)
{
    XTestFakeButtonEvent(display, button, false, CurrentTime);
    XFlush(display);
}

void XInputSimulatorImplLinux::mouseClick(const int button)
{
    this->mouseDown(button);
    usleep(USLEEP_TIME);
    this->mouseUp(button);
}

void XInputSimulatorImplLinux::mouseScrollX(int length)
{
    int button;
    if (length < 0)
    {
        button = 6; // Scroll left button
    }
    else
    {
        button = 7; // Scroll right button
    }

    if (length < 0)
    {
        length *= -1;
    }

    for (int cnt = 0; cnt < length; cnt++)
    {
        this->mouseDown(button);
        usleep(USLEEP_TIME);
        this->mouseUp(button);
        usleep(USLEEP_TIME);
    }
}

void XInputSimulatorImplLinux::mouseScrollY(int length)
{
    int button;
    if (length < 0)
    {
        button = 4; //scroll up button
    }
    else
    {
        button = 5; //scroll down button
    }

    if (length < 0)
    {
        length *= -1;
    }

    for (int cnt = 0; cnt < length; cnt++)
    {
        this->mouseDown(button);
        usleep(USLEEP_TIME);
        this->mouseUp(button);
        usleep(USLEEP_TIME);
    }
}

void XInputSimulatorImplLinux::keyDown(const int key)
{
    XTestFakeKeyEvent(display, key, True, 0);
    XFlush(display);
}

void XInputSimulatorImplLinux::keyUp(const int key)
{
    XTestFakeKeyEvent(display, key, False, 0);
    XFlush(display);
}

void XInputSimulatorImplLinux::keyClick(const int key)
{
#ifdef DEBUG_MODE
    std::cout << "Key Click: " << key << std::endl;
#endif

    this->keyDown(key);
    usleep(USLEEP_TIME);
    this->keyUp(key);
    usleep(USLEEP_TIME);
}

int XInputSimulatorImplLinux::charToKeyCode(const char key_char)
{
    const int keyCode = XKeysymToKeycode(display, key_char);
    //    int keyCode = XKeysymToKeycode(display, XStringToKeysym(&key_char));

#ifdef DEBUG_MODE
    std::cout << "Char: " << static_cast<int>(key_char) << std::endl;
    std::cout << "Code: " << keyCode << std::endl;
#endif

    return keyCode;
}

void XInputSimulatorImplLinux::keySequence(const std::string& sequence)
{
#ifdef DEBUG_MODE
    std::cout << "Text sequence: " << sequence << std::endl;
#endif

    for (const char c : sequence)
    {
        const int keyCode = this->charToKeyCode(c);
#ifdef DEBUG_MODE
        std::cout << "Char: " << c << std::endl;
        std::cout << "Key Code: " << keyCode << std::endl;
#endif

        if (isupper(c))
        {
#ifdef DEBUG_MODE
            std::cout << "Upper " << c << std::endl;
#endif
            this->keyDown(XKeysymToKeycode(display, XK_Shift_L));
            this->keyClick(keyCode);
            this->keyUp(XKeysymToKeycode(display, XK_Shift_L));
        }
        else
        {
            this->keyClick(keyCode);
        }

        std::cout << std::endl;
    }
}

#endif // __linux__
