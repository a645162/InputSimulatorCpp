# Example/CMakeLists.txt
# Author: Haomin Kong

cmake_minimum_required(VERSION 3.5)

project(InputSimulatorExample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(
        InputSimulatorCppLib NAMES
        InputSimulatorCore
)
include_directories(../InputSimulatorCpp/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(
        ${PROJECT_NAME}

        ./src/main.cpp

        ./src/library.cpp
)
target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        InputSimulatorCore
)

# Windows Extra Build Options
if (WIN32)
    if (MINGW)
        target_compile_options(${PROJECT_NAME} PRIVATE -std=c++11)
    endif (MINGW)

    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
    endif (MSVC)
endif (WIN32)
