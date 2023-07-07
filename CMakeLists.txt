cmake_minimum_required(VERSION 3.22)

project(dat-engine VERSION 1.0.0 DESCRIPTION "Top Level")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(DAT_ENGINE_TARGET_PLATFORM "linux" CACHE STRING "The target platform to build for")
set_property(CACHE DAT_ENGINE_TARGET_PLATFORM PROPERTY STRINGS linux windows macos)

# Ensure debug flag is set when posix
IF(NOT MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
ENDIF()

add_library(dat-engine STATIC dat-engine/maths/vector.h dat-engine/maths/vector/vec-forward.h dat-engine/maths/vector/vec3.h dat-engine/util/type-traits.h dat-engine/maths/numbers.h dat-engine/maths/common-maths.h)

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

#set(projectAssetDir "" CACHE FILEPATH "The asset directory for the project")
#set(assetDest "${CMAKE_BINARY_DIR}/Engine" CACHE FILEPATH "Destination Path of the asset directory in the compiled project")

# Examples
add_subdirectory(examples)