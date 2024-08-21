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
    set(PLATFORM_SOURCE_FILES ./src/xinputsimulatorimpllinux.cpp ./src/xinputsimulatorimpllinux.h)
endif (UNIX AND NOT APPLE)

# Apple
if (APPLE)
    find_library(APP_SERVICES ApplicationServices)
    find_library(CARBON Carbon)
    find_library(CORE_FOUNDATION CoreFoundation)
    set(EXTRA_LIBS ${APP_SERVICES_LIBRARY} ${CARBON} ${CORE_FOUNDATION})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(PLATFORM_SOURCE_FILES ./src/xinputsimulatorimplmacos.cpp ./src/xinputsimulatorimplmacos.h)
endif (APPLE)

# Windows
if (WIN32)
    #find_library(USER_32 User32.Lib)
    #set(EXTRA_LIBS ${USER_32})
    set(PLATFORM_SOURCE_FILES ./src/xinputsimulatorimplwin.cpp ./src/xinputsimulatorimplwin.h)
endif (WIN32)

set(SOURCE_FILES

        ./src/main.cpp

        ./src/notimplementedexception.cpp
        ./src/notimplementedexception.h

        ./src/xinputsimulator.cpp
        ./src/xinputsimulator.h

        ./src/xinputsimulatorimpl.cpp
        ./src/xinputsimulatorimpl.h

        ${PLATFORM_SOURCE_FILES}
)

add_executable(XInputSimulator ${SOURCE_FILES})
target_link_libraries(XInputSimulator ${EXTRA_LIBS})
