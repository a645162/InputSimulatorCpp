# InputSimulatorCpp/CMakeLists.txt
# Author: Haomin Kong

cmake_minimum_required(VERSION 3.5)
project(InputSimulatorCppLib VERSION 0.1.0 LANGUAGES CXX)
set(NAME_CORE_LIB "InputSimulatorCore")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INPUT_SIMULATOR_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(INPUT_SIMULATOR_SOURCE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")

#message(STATUS "Header Files: ${INPUT_SIMULATOR_INCLUDE_DIRS}")
#message(STATUS "Source Files: ${INPUT_SIMULATOR_SOURCE_DIRS}")

if (BUILD_SHARED_LIBS)
    set(LIB_TYPE "SHARED")
else ()
    set(LIB_TYPE "STATIC")
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
    set(PLATFORM_NAME "Apple macOS")

    find_library(APP_SERVICES ApplicationServices)
    find_library(CARBON Carbon)
    find_library(CORE_FOUNDATION CoreFoundation)

    set(EXTRA_LIBS ${APP_SERVICES_LIBRARY} ${CARBON} ${CORE_FOUNDATION})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (APPLE)

# Linux X11(X.Org)
if (LINUX)
    set(PLATFORM_NAME "Linux")

    find_library(X_11 X11)
    find_library(X_TST Xtst)

    set(EXTRA_LIBS ${X_11} ${X_TST})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (LINUX)

message(STATUS "Platform: ${PLATFORM_NAME}")

file(GLOB_RECURSE SOURCE_FILES
        "${INPUT_SIMULATOR_SOURCE_DIRS}/*.cpp"
        "${INPUT_SIMULATOR_SOURCE_DIRS}/*.hpp"
        "${INPUT_SIMULATOR_SOURCE_DIRS}/*.c"
        "${INPUT_SIMULATOR_SOURCE_DIRS}/*.h"
)
#message(STATUS "Source Files: ${SOURCE_FILES}")

# For CLion(Not necessary)
file(GLOB_RECURSE HEADER_FILES
        "${INPUT_SIMULATOR_INCLUDE_DIRS}/*.cpp"
        "${INPUT_SIMULATOR_INCLUDE_DIRS}/*.hpp"
        "${INPUT_SIMULATOR_INCLUDE_DIRS}/*.c"
        "${INPUT_SIMULATOR_INCLUDE_DIRS}/*.h"
)

include_directories(${INPUT_SIMULATOR_INCLUDE_DIRS})

# Core Lib
add_library(
        ${NAME_CORE_LIB} ${LIB_TYPE}

        ${HEADER_FILES}
        ${SOURCE_FILES}
)
target_link_libraries(${NAME_CORE_LIB} ${EXTRA_LIBS})
target_include_directories(${NAME_CORE_LIB} PUBLIC ${INPUT_SIMULATOR_LIB_HEADER_DIR})

# Windows Extra Build Options
if (WIN32)
    if (MINGW)
        target_compile_options(${NAME_CORE_LIB} PRIVATE -std=c++11)
        set_target_properties(${NAME_CORE_LIB} PROPERTIES PREFIX "")
    endif (MINGW)

    if (MSVC)
        target_compile_options(${NAME_CORE_LIB} PRIVATE /utf-8)
        set_target_properties(${NAME_CORE_LIB} PROPERTIES DEBUG_POSTFIX "d")
    endif (MSVC)
endif (WIN32)

install(TARGETS ${NAME_CORE_LIB} ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
install(DIRECTORY ${INPUT_SIMULATOR_LIB_HEADER_DIR} DESTINATION include)

set(CPACK_PACKAGE_NAME "InputSimulatorCppLib")
set(CPACK_PACKAGE_VENDOR "Haomin Kong")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${PROJECT_SOURCE_DIR}/README.md)
set(CPACK_NSIS_MODIFY_PATH ON)
include(CPack)
