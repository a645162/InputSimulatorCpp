cmake_minimum_required(VERSION 3.10)
project(InputSimulatorCppLib)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

option(INPUT_SIMULATOR_BUILD_STATIC_LIB "Build static library." OFF)

if (INPUT_SIMULATOR_BUILD_STATIC_LIB)
    set(LIB_TYPE "STATIC")
else ()
    set(LIB_TYPE "SHARED")
endif ()

# Default Platform Name
set(PLATFORM_NAME "Unknown")

# Windows
if (WIN32)
    set(PLATFORM_NAME "Windows")

    # find_library(USER_32 User32.Lib)

    # set(EXTRA_LIBS ${USER_32})
endif (WIN32)

# Apple macOS
if (APPLE)
    set(PLATFORM_NAME "Windows")

    find_library(APP_SERVICES ApplicationServices)
    find_library(CARBON Carbon)
    find_library(CORE_FOUNDATION CoreFoundation)

    set(EXTRA_LIBS ${APP_SERVICES_LIBRARY} ${CARBON} ${CORE_FOUNDATION})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif (APPLE)

# Linux X11(X.Org)
if (LINUX)
    set(PLATFORM_NAME "Windows")

    find_library(X_11 X11)
    find_library(X_TST Xtst)

    set(EXTRA_LIBS ${X_11} ${X_TST})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif (LINUX)

message(STATUS "Platform: ${PLATFORM_NAME}")

file(GLOB_RECURSE SOURCE_FILES
        "${SOURCE_DIR}/*.cpp"
        "${SOURCE_DIR}/*.hpp"
        "${SOURCE_DIR}/*.c"
        "${SOURCE_DIR}/*.h"
)

set(XInputSimulator_SOURCE_FILES
        ./src/main.cpp

        ${SOURCE_FILES}
)

# XInputSimulator executable(GitHub OpenSource Project)
add_executable(XInputSimulator ${XInputSimulator_SOURCE_FILES})
target_link_libraries(XInputSimulator ${EXTRA_LIBS})

# InputSimulatorCppLib library(This Project)
add_library(
        ${PROJECT_NAME} ${LIB_TYPE}

        ./src/library.cpp
        ./src/library.hpp
)
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})

# Windows Extra Build Options
if (WIN32)
    if (MINGW)
        set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
    endif (MINGW)

    if (MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
    endif (MSVC)
endif (WIN32)
