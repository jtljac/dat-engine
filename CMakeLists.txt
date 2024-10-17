cmake_minimum_required(VERSION 3.22)

project(dat-engine VERSION 1.0.0
                   DESCRIPTION "Top Level"
                   LANGUAGES CXX)

set(DAT_ENGINE_TITLE "Dat Engine")
string(TIMESTAMP TODAY "%Y/%m/%d")
set(DAT_ENGINE_BUILD_DATE ${TODAY})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

add_library(dat-engine STATIC)

#################################################
# Config Variables                              #
#################################################

# Engine Variables
set(DAT_ENGINE_TARGET_PLATFORM "linux" CACHE STRING "The target platform to build for")
set_property(CACHE DAT_ENGINE_TARGET_PLATFORM PROPERTY STRINGS linux windows macos)

# CVars

set(DAT_ENGINE_MAX_INTEGER_CVARS 500 CACHE STRING "The maximum number of Integer CVars")
set(DAT_ENGINE_MAX_BOOL_CVARS 200 CACHE STRING "The maximum number of Boolean CVars")
set(DAT_ENGINE_MAX_FLOAT_CVARS 200 CACHE STRING "The maximum number of Float CVars")
set(DAT_ENGINE_MAX_STRING_CVARS 200 CACHE STRING "The maximum number of String CVars")

# Assets
#set(projectAssetDir "" CACHE FILEPATH "The asset directory for the project")
#set(assetDest "${CMAKE_BINARY_DIR}/Engine" CACHE FILEPATH "Destination Path of the asset directory in the compiled project")

# Testing
set(DAT_ENGINE_ENABLE_TESTS OFF CACHE BOOL "Whether to enable testing")


#################################################
# Environment Setup                             #
#################################################

# Ensure debug flag is set when posix
IF(NOT MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
ENDIF()

# Optimisations
if(MSVC)
    target_compile_options(dat-engine PUBLIC /arch:SSE4.1 /arch:AVX)
else()
    target_compile_options(dat-engine PUBLIC -march=native)
endif()

add_subdirectory(first-party)
add_subdirectory(third-party)
add_subdirectory(tools)
add_subdirectory(dat-engine)

# Examples
add_subdirectory(examples)


#################################################
# Testing                                       #
#################################################

if (${DAT_ENGINE_ENABLE_TESTS})
    message("DatEngine Testing has been enabled")
    add_subdirectory(tests)
else()
    message("Dat Engine Testing has been disabled")
endif ()