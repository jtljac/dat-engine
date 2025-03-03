#include <dat-engine.h>

#include <SDL3/SDL.h>

#include "util/cvar.h"
#include "util/logger.h"

using namespace DatEngine;

CVarInt windowWidthCVar("IWindowWidth", "The width of the game window", CVarCategory::Graphics, 1280, CVarFlags::Persistent);
CVarInt windowHeightCVar("IWindowHeight", "The height of the game window", CVarCategory::Graphics, 720, CVarFlags::Persistent);
CVarEnum windowModeCVar("EWindowMode", "How to display the game window", CVarCategory::Graphics,
                        DatGPU::WindowMode::Windowed, CVarFlags::Persistent);

Engine* Engine::instance = nullptr;

bool Engine::preInit() {
    DatLog::init();

    return true;
}

bool Engine::init(DatGPU::igpu* renderer) {
    instance = new Engine;
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
        CORE_CRITICAL("Failed to initialize SDL - %s", SDL_GetError());
        return false;
    }

    CORE_INFO("Initialised Dat Engine");

    int windowFlags = renderer->getWindowFlags();

    switch (windowModeCVar.getEnum()) {
        case DatGPU::WindowMode::Borderless:
            windowFlags |= SDL_WINDOW_BORDERLESS;
            break;
        case DatGPU::WindowMode::Fullscreen:
            windowFlags |= SDL_WINDOW_FULLSCREEN;
            break;
        default:;
    }

    instance->window = SDL_CreateWindow(
        "Dat Engine",
        windowWidthCVar.get(),
        windowHeightCVar.get(),
        windowFlags
    );

    if (instance->window == nullptr) {
        CORE_CRITICAL("Failed to create window - %s", SDL_GetError());
        return false;
    }

    instance->gpu = renderer;

    if (!renderer->initialise()) {
        CORE_ERROR("Failed to initialise renderer");
        renderer->cleanup();

        return false;
    }

    return true;
}

void Engine::startLoop() {

    uint64_t lastTime = SDL_GetTicks();
    while (!shouldClose) {
        uint64_t now = SDL_GetTicks();
        float deltaTime = ((float) (now - lastTime)) / 1000;

        // Input
        //   Handle SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    shouldClose = true;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                        shouldClose = true;
                    }
            }
        }

        // Update

        // Render
        gpu->draw();
        // UI

        lastTime = now;
    }
}

void Engine::cleanup() {
    delete instance;
    instance = nullptr;
}

SDL_Window* Engine::getWindow() const {
    return window;
}
