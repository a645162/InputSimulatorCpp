cmake_minimum_required(VERSION 3.10)

project(InputSimulatorCpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(CheckCMakeVersion)
check_cmake_version()

add_subdirectory(InputSimulatorCpp)
add_subdirectory(Example)
