# Check if the build type is Debug
macro(debug_mode_macro)
    # Check DEBUG_MODE is defined
    if (NOT DEFINED DEBUG_MODE)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(DEBUG_MODE ON)
        else ()
            set(DEBUG_MODE OFF)
        endif ()
    endif ()

    if (DEBUG_MODE)
        message(STATUS "Debug mode is ON")
        add_definitions(-DDEBUG_MODE)
    else ()
        message(STATUS "Debug mode is OFF")
    endif ()
endmacro()
