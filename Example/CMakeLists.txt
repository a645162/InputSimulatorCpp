# Example/CMakeLists.txt
# Author: Haomin Kong

cmake_minimum_required(VERSION 3.10)

project(InputSimulatorExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(InputSimulatorCppLib InputSimulatorCppLib)
include_directories(${INPUT_SIMULATOR_INCLUDE_DIRS})

add_executable(
        ${PROJECT_NAME}

        ./src/main.cpp

        ./include/library.hpp
        ./src/library.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE InputSimulatorCppLib)
