# CMakeLists.txt
# Author: Haomin Kong

cmake_minimum_required(VERSION 3.5)

project(InputSimulatorCpp)

SET(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/a645162/InputSimulatorCpp")

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build dynamic library." OFF)

#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMake")
# message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(DebugMode)
debug_mode_macro()

include(CheckCMakeVersion)
check_cmake_version()

add_subdirectory(InputSimulatorCpp)
#include(FindInputSimulator)

add_subdirectory(Example)
