# FindInputSimulator.cmake
# Try to find InputSimulatorCppLib

# Once done, this will define:
#   InputSimulatorCppLib_FOUND - System has InputSimulatorCppLib
#   InputSimulatorCppLib_INCLUDE_DIRS - The InputSimulatorCppLib include directories
#   InputSimulatorCppLib_LIBRARIES - The libraries needed to use InputSimulatorCppLib

find_path(InputSimulatorCppLib_INCLUDE_DIR
        NAMES InputSimulatorCore.hpp
        PATHS /usr/include /usr/local/include /opt/local/include
)

if(WIN32)
    find_library(InputSimulatorCppLib_LIBRARY
            NAMES InputSimulatorCore.lib
            PATHS "C:/Program Files/InputSimulatorCppLib/lib"
            "C:/Program Files (x86)/InputSimulatorCppLib/lib"
            ${CMAKE_INSTALL_PREFIX}/lib
    )
elseif(APPLE)
    find_library(InputSimulatorCppLib_LIBRARY
            NAMES InputSimulatorCore
            PATHS /usr/local/lib /usr/lib /opt/local/lib
            ${CMAKE_INSTALL_PREFIX}/lib
    )
else()
    find_library(InputSimulatorCppLib_LIBRARY
            NAMES InputSimulatorCore
            PATHS /usr/lib /usr/local/lib /opt/local/lib
            ${CMAKE_INSTALL_PREFIX}/lib
    )
endif()

set(InputSimulatorCppLib_INCLUDE_DIRS ${InputSimulatorCppLib_INCLUDE_DIR})
set(InputSimulatorCppLib_LIBRARIES ${InputSimulatorCppLib_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(InputSimulatorCppLib
        DEFAULT_MSG
        InputSimulatorCppLib_LIBRARY InputSimulatorCppLib_INCLUDE_DIR
)

mark_as_advanced(InputSimulatorCppLib_INCLUDE_DIR InputSimulatorCppLib_LIBRARY)

if(InputSimulatorCppLib_FOUND)
    message(STATUS "Found InputSimulatorCppLib: ${InputSimulatorCppLib_LIBRARIES}")
else()
    message(WARNING "Could not find InputSimulatorCppLib")
endif()
