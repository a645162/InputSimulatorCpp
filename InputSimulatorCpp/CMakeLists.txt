cmake_minimum_required(VERSION 3.10)
project(InputSimulatorCpp)

set(CMAKE_CXX_STANDARD 17)

#add_library(
#        ${PROJECT_NAME} SHARED
#
#        library.cpp
#)

# Linux
if (UNIX AND NOT APPLE)
    find_library(X_11 X11)
    find_library(X_TST Xtst)
    set(EXTRA_LIBS ${X_11} ${X_TST})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(PLATFORM_SOURCE_FILES src/Linux/xInputSimulatorImplLinux.cpp src/Linux/xInputSimulatorImplLinux.hpp)
endif ()

# Apple
if (APPLE)
    find_library(APP_SERVICES ApplicationServices)
    find_library(CARBON Carbon)
    find_library(CORE_FOUNDATION CoreFoundation)
    set(EXTRA_LIBS ${APP_SERVICES_LIBRARY} ${CARBON} ${CORE_FOUNDATION})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(PLATFORM_SOURCE_FILES src/macOS/xInputSimulatorImplMacOS.cpp src/macOS/xInputSimulatorImplMacOS.hpp)
endif ()

# Windows
if (WIN32)
    #find_library(USER_32 User32.Lib)
    #set(EXTRA_LIBS ${USER_32})
    set(PLATFORM_SOURCE_FILES src/Windows/xInputSimulatorImplWin.cpp src/Windows/xInputSimulatorImplWin.hpp)
endif ()

set(SOURCE_FILES
        src/NotImplementedException.cpp
        src/NotImplementedException.hpp

        src/xInputSimulator.cpp
        src/xInputSimulator.hpp

        src/Common/xInputSimulatorImpl.cpp
        src/Common/xInputSimulatorImpl.hpp

        ${PLATFORM_SOURCE_FILES}
)

set(XInputSimulator_SOURCE_FILES
        ./src/main.cpp

        ${SOURCE_FILES}
)

add_executable(XInputSimulator ${XInputSimulator_SOURCE_FILES})
target_link_libraries(XInputSimulator ${EXTRA_LIBS})
