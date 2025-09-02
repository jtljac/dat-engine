#pragma once

#include <cstdint>

namespace DatEngine::DatGpu {
    /** The available fullscreen modes */
    enum class WindowMode : uint8_t {
        /** A window with a title bar */
        Windowed,
        /** A window without a title bar */
        Borderless,
        /** Dedicated fullscreen mode */
        Fullscreen
    };

    class IGpu {
    public:
        virtual ~IGpu() = default;

        /**
         * Get the SDL window flags required by the renderer
         *
         * @return SDL window flags for the renderer
         */
        virtual int getWindowFlags() = 0;

        /**
         * Initialise the renderer
         *
         * @return @code true@endcode when the initialisation was successful
         */
        virtual void initialise();

        /**
         * Draw a single frame
         */
        virtual void draw() = 0;

        /**
         * Clean-up the renderer and all memory used by it for shutting down
         */
        virtual void cleanup() = 0;
    };
} // namespace DatEngine::DatGpu
