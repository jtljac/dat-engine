#pragma once

#include <cstdint>

namespace DatEngine::DatRendering {
    /** The available fullscreen modes */
    enum class WindowMode : uint8_t {
        /** A window with a title bar */
        Windowed,
        /** A window without a title bar */
        Borderless,
        /** Dedicated fullscreen mode */
        Fullscreen
    };

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual int getWindowFlags() = 0;

        virtual bool initialise();

        virtual void cleanup() = 0;
    };
}