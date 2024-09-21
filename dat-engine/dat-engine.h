#pragma once

#include <iostream>
#include <maths/vector.h>

#include <rendering/irenderer.h>

struct SDL_Window;

namespace DatEngine {
    enum class EngineRunningState {

    };

    // TODO: Split into server and client
    class Engine {
        // Window
        SDL_Window* window = nullptr;
        // Renderer
        IRenderer* renderer = nullptr;
        // Asset Manager
        // Input Manager
        // Audio Engine
        // UI

        bool shouldClose = false;

        Engine() = default;

    public:
        static Engine* getInstance() {
            static Engine instance{};
            return &instance;
        }
        bool init(IRenderer* renderer);
        void startLoop();
    };
}