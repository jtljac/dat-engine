cmake_minimum_required(VERSION 3.22)

if(WIN32)
    add_subdirectory(windows)
elseif (UNIX)
    add_subdirectory(unix)
ENDIF()

# Figure out a way to detect between x86 and arm
add_subdirectory(x86)