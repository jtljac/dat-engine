#pragma once

#include <iostream>
#include <maths/vector.h>

#include <gpu/igpu.h>

struct SDL_Window;

namespace DatEngine {
    enum class EngineRunningState {

    };

    // TODO: Split into server and client
    class Engine {
        /** Singleton instance of the engine */
        static Engine* instance;

        /** The window user interacts with */
        SDL_Window* window = nullptr;

        /** The renderer for the engine */
        DatGPU::igpu* gpu = nullptr;
        // Asset Manager
        // Input Manager
        // Audio Engine
        // UI

        /** Whether the engine wants to close */
        bool shouldClose = false;

        Engine() = default;

    public:
        /**
         * Get the global engine instance for the engine
         *
         * @return The engine instance
         */
        static Engine* getInstance() {
            assert(instance && "You must initialise the engine first.");
            return instance;
        }

        /**
         * Initialise the supportive components of the engine (Logger, etc)
         *
         * @return @code true@endcode if successful
         */
        static bool preInit();

        /**
         *
         * @param renderer The renderer to use for the engine
         * @return @code true@endcode if successful
         */
        static bool init(DatGPU::igpu* renderer);

        /**
         * Kick off the main engine loop
         */
        void startLoop();

        /**
         * Cleanup the engine
         */
        static void cleanup();

        // Util
        /**
         * Get the window being used by the engine
         *
         * @return The window used by the engine
         */
        [[nodiscard]] SDL_Window* getWindow() const;
    };
}