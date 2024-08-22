# CheckCMakeVersion.cmake

# Compare CMake Version
function(compare_cmake_version major_version minor_version)
    # Get CMake version
    string(REPLACE "." ";" CMAKE_VERSION_LIST ${CMAKE_VERSION})
    list(GET CMAKE_VERSION_LIST 0 CMAKE_MAJOR_VERSION)
    list(GET CMAKE_VERSION_LIST 1 CMAKE_MINOR_VERSION)

    # Check CMake version
    if (CMAKE_MAJOR_VERSION GREATER major_version OR
    (CMAKE_MAJOR_VERSION EQUAL major_version AND CMAKE_MINOR_VERSION GREATER minor_version))
        set(CMAKE_VERSION_IS_GREATER TRUE PARENT_SCOPE)
    else ()
        set(CMAKE_VERSION_IS_GREATER FALSE PARENT_SCOPE)
    endif ()
endfunction()

# Macro for Linux
macro(add_macro_linux)
    if (UNIX AND NOT APPLE)
        set(LINUX TRUE)
    else ()
        set(LINUX FALSE)
    endif ()
endmacro()

# Check CMake Version
macro(check_cmake_version)
    compare_cmake_version(3 25)
    if (CMAKE_VERSION_IS_GREATER)
        message(STATUS "CMake support `LINUX` macro (CMake Version is 3.25 or higher)")
    else ()
        message(STATUS "Add `LINUX` macro")
        add_macro_linux()
    endif ()
endmacro()
