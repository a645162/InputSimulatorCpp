// Input Simulator macOS Implementation
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

#ifdef __APPLE__

#include <iostream>

#include "InputSimulator/Platform/macOS/xInputSimulatorImplMacOS.hpp"
#include "InputSimulator/Utils/NotImplementedException.hpp"
#include "InputSimulator/KeyboardKeyCode.hpp"
#include "InputSimulator/Utils/TimeSleep.hpp"

#define SLEEP_TIME_MS 1

XInputSimulatorImplMacOs::XInputSimulatorImplMacOs() {
    //TODO
    //this->initCurrentMousePosition();

#ifdef DEBUG_MODE
    std::cout << "Constructor " << std::endl;
#endif

    this->currentX = 500;
    this->currentY = 500;

    CGDirectDisplayID displayID = CGMainDisplayID();

    this->displayX = CGDisplayPixelsWide(displayID);
    this->displayY = CGDisplayPixelsHigh(displayID);
}

//void XInputSimulatorImplMacOs::initMouseEvent(int button)
//{

//}

void XInputSimulatorImplMacOs::initCurrentMousePosition() {
    throw NotImplementedException();
}

void XInputSimulatorImplMacOs::mouseMoveTo(int x, int y) {

    //TODO screen check see moveRelative

    CGEventRef mouseEv = CGEventCreateMouseEvent(
            nullptr, kCGEventMouseMoved,
            CGPointMake(x, y),
            kCGMouseButtonLeft);

#ifdef DEBUG_MODE
    std::cout << "Move: " << mouseEv << std::endl;
#endif

    CGEventPost(kCGHIDEventTap, mouseEv);

    CFRelease(mouseEv);

    this->currentX = x;
    this->currentY = y;
}

void XInputSimulatorImplMacOs::mouseMoveRelative(int x, int y) {
    int newX = this->currentX + x;
    int newY = this->currentY + y;

    if (newX < 0 || newX > this->displayX || newY < 0 || newY > this->displayY) {
        std::cerr << "Mouse moved beyond screensize." << std::endl;
        return;
    }

#ifdef DEBUG_MODE
    std::cout << "NewX: " << newX << " NewY: " << newY << std::endl;
#endif

    CGEventRef mouseEv =
            CGEventCreateMouseEvent(
                    nullptr, kCGEventMouseMoved,
                    CGPointMake(newX, newY),
                    kCGMouseButtonLeft
            );

    CGEventPost(kCGHIDEventTap, mouseEv);

    CFRelease(mouseEv);

    this->currentX = newX;
    this->currentY = newY;
}

void XInputSimulatorImplMacOs::mouseDown(int button) {
    CGEventRef mouseEv =
            CGEventCreateMouseEvent(
                    nullptr, kCGEventLeftMouseDown,
                    CGPointMake(this->currentX, this->currentY),
                    kCGMouseButtonLeft
            ); // use int button from parameter

    CGEventPost(kCGHIDEventTap, mouseEv);

    CFRelease(mouseEv);
}

void XInputSimulatorImplMacOs::mouseUp(int button) {
    CGEventRef mouseEv = CGEventCreateMouseEvent(
            nullptr, kCGEventLeftMouseUp,
            CGPointMake(this->currentX, this->currentY),
            kCGMouseButtonLeft); // use int button from parameter

    CGEventPost(kCGHIDEventTap, mouseEv);

    CFRelease(mouseEv);
}

void XInputSimulatorImplMacOs::mouseClick(int button) {
    this->mouseDown(button);
    TimeSleep(SLEEP_TIME_MS);
    this->mouseUp(button);
    TimeSleep(SLEEP_TIME_MS);
}

void XInputSimulatorImplMacOs::mouseScrollX(int length) {
    int scrollDirection = -1; // 1 left -1 right

    if (length < 0) {
        length *= -1;
        scrollDirection *= -1;
    }

    //length *= 100;

    for (int cnt = 0; cnt < length; cnt++) {
#ifdef DEBUG_MODE
        std::cout << "Scroll X" << std::endl;
#endif

        CGEventRef scrollEv = CGEventCreateScrollWheelEvent(
                nullptr, kCGScrollEventUnitLine, // kCGScrollEventUnitLine //kCGScrollEventUnitPixel
                2, //CGWheelCount 1 = y; 2 = xy; 3 = xyz
                0,
                scrollDirection); // length of scroll from -10 to 10 higher values lead to undef behavior

        CGEventPost(kCGHIDEventTap, scrollEv);

        CFRelease(scrollEv);
        TimeSleep(SLEEP_TIME_MS);
    }
}

void XInputSimulatorImplMacOs::mouseScrollY(int length) {
    int scrollDirection = -1; // 1 down; -1 up

    if (length < 0) {
        length *= -1;
        scrollDirection *= -1;
    }

    //length *= 100;

    for (int cnt = 0; cnt < length; cnt++) {
#ifdef DEBUG_MODE
        std::cout << "Scroll Y" << std::endl;
#endif

        CGEventRef scrollEv = CGEventCreateScrollWheelEvent(
                nullptr, kCGScrollEventUnitLine, // kCGScrollEventUnitLine //kCGScrollEventUnitPixel
                1, //CGWheelCount 1 = y; 2 = xy; 3 = xyz
                scrollDirection); // length of scroll from -10 to 10 higher values lead to undef behavior

        CGEventPost(kCGHIDEventTap, scrollEv);

        CFRelease(scrollEv);
        TimeSleep(SLEEP_TIME_MS);
    }
}

void XInputSimulatorImplMacOs::keyDown(int key) {
    CGKeyCode keycode = key;
    CGEventRef commandDown = CGEventCreateKeyboardEvent(nullptr, keycode, true);
    CGEventPost(kCGAnnotatedSessionEventTap, commandDown);
    CFRelease(commandDown);
}

void XInputSimulatorImplMacOs::keyUp(int key) {
    CGKeyCode keycode = key;
    CGEventRef commandUp = CGEventCreateKeyboardEvent(nullptr, keycode, false);
    CGEventPost(kCGAnnotatedSessionEventTap, commandUp);
    CFRelease(commandUp);
}

void XInputSimulatorImplMacOs::keyClick(int key) {
#ifdef DEBUG_MODE
    std::cout << "Keyboard Key Click: " << key << std::endl;
#endif

    this->keyDown(key);
    TimeSleep(SLEEP_TIME_MS);
    this->keyUp(key);
    TimeSleep(SLEEP_TIME_MS);
}

CFStringRef XInputSimulatorImplMacOs::createStringForKey(CGKeyCode keyCode) {
    TISInputSourceRef currentKeyboard = TISCopyCurrentKeyboardInputSource();
    //CFDataRef layoutData = TISGetInputSourceProperty(currentKeyboard, kTISPropertyUnicodeKeyLayoutData);
    auto layoutData = (CFDataRef) TISGetInputSourceProperty(
            currentKeyboard, kTISPropertyUnicodeKeyLayoutData
    );

    const auto *keyboardLayout = (const UCKeyboardLayout *) CFDataGetBytePtr(layoutData);

    UInt32 keysDown = 0;
    UniChar chars[4];
    UniCharCount realLength;

    UCKeyTranslate(
            keyboardLayout,
            keyCode,
            kUCKeyActionDisplay,
            0,
            LMGetKbdType(),
            kUCKeyTranslateNoDeadKeysBit,
            &keysDown,
            sizeof(chars) / sizeof(chars[0]),
            &realLength,
            chars
    );

    CFRelease(currentKeyboard);

    return CFStringCreateWithCharacters(kCFAllocatorDefault, chars, 1);
}

int XInputSimulatorImplMacOs::charToKeyCode(char key_char) {
    static CFMutableDictionaryRef charToCodeDict = nullptr;
    CGKeyCode code;
    UniChar character = static_cast<unsigned char>(key_char);
    CFStringRef charStr;

    /* Generate table of keycodes and characters. */
    if (charToCodeDict == nullptr) {
        size_t i;
        charToCodeDict = CFDictionaryCreateMutable(
                kCFAllocatorDefault,
                128,
                &kCFCopyStringDictionaryKeyCallBacks,
                nullptr
        );
        if (charToCodeDict == nullptr) return UINT16_MAX;

        /* Loop through every keycode (0-127) to find its current mapping. */
        for (i = 0; i < 128; ++i) {
            CFStringRef string = createStringForKey((CGKeyCode) i);
            if (string != nullptr) {
                CFDictionaryAddValue(charToCodeDict, string, (const void *) i);
                CFRelease(string);
            }
        }
    }

    charStr = CFStringCreateWithCharacters(kCFAllocatorDefault, &character, 1);

    /* Our values may be NULL (0), so we need to use this function. */
    if (!CFDictionaryGetValueIfPresent(
            charToCodeDict,
            charStr,
            (const void **) &code)
            ) {
        code = UINT16_MAX;
    }

    CFRelease(charStr);
    return code;
}

void XInputSimulatorImplMacOs::keySequence(const std::string &sequence) {
#ifdef DEBUG_MODE
    std::cout << "Key sequence: " << sequence << std::endl;
#endif

    for (const char c: sequence) {
        const bool isUpper = isupper(c);
        int keyCode = this->charToKeyCode(ConvertUpperCaseToLowerCase(c));

#ifdef DEBUG_MODE
        std::cout << "Char: " << c << std::endl;
        std::cout << "Key Code: " << keyCode << std::endl;
        std::cout << std::endl;
#endif

        if (isUpper) {
            // Upper Case
            this->keyDown(kVK_Shift);
            TimeSleep(SLEEP_TIME_MS);
            this->keyClick(keyCode);
            TimeSleep(SLEEP_TIME_MS);
            this->keyUp(kVK_Shift);
            TimeSleep(SLEEP_TIME_MS);
        } else {
            // Lower Case
            this->keyClick(keyCode);
        }

        TimeSleep(SLEEP_TIME_MS);
    }
}

#endif // __APPLE__
