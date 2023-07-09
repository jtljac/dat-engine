cmake_minimum_required(VERSION 3.22)


set(DAT_ENGINE_RENDER_API "vulkan" CACHE STRING "The renderAPI to use")
set_property(CACHE DAT_ENGINE_RENDER_API PROPERTY STRINGS vulkan directx opengl)

set(ALLOWED_RENDER_API "")

list(REMOVE_DUPLICATES ALLOWED_RENDER_API)

if (${DAT_ENGINE_TARGET_PLATFORM} STREQUAL "linux")
    list(APPEND ALLOWED_RENDER_API "vulkan")
    list(APPEND ALLOWED_RENDER_API "opengl")
elseif (${DAT_ENGINE_TARGET_PLATFORM} STREQUAL "windows")
    list(APPEND ALLOWED_RENDER_API "vulkan")
    list(APPEND ALLOWED_RENDER_API "directx")
endif()

if (NOT ${DAT_ENGINE_RENDER_API} IN_LIST ALLOWED_RENDER_API)
    message(SEND_ERROR "Render API Error: Platform ${DAT_ENGINE_TARGET_PLATFORM} does not allow ${DAT_ENGINE_RENDER_API} render api")
endif ()

if (${DAT_ENGINE_RENDER_API} STREQUAL "vulkan")
    message("Using Vulkan renderer")

endif ()

target_sources(dat-engine PRIVATE
        "IRenderer.h" "source/IRenderer.cpp"
        "IWindow.h" "source/IWindow.cpp"
)