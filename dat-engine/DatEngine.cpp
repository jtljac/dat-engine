#include "util/Exception/DatException.h"

#include <DatEngine.h>

#include <SDL3/SDL.h>

#include <util/CVar.h>
#include <util/Logger.h>

using namespace DatEngine;

extern CVarInt windowWidthCVar;
extern CVarInt windowHeightCVar;
extern CVarEnum<DatGpu::WindowMode> windowModeCVar;

Engine* Engine::instance = nullptr;

bool Engine::preInit() {
    // Logger
    // Asset Manager
    // Input
    // Busses
    // Console?
    // Localisation?
    // GPU?
    DatLog::init();

    return true;
}

void Engine::init(DatGpu::IGpu* renderer) {
    instance = new Engine;
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
        throw DatException(fmt::format("Failed to initialize SDL - %s", SDL_GetError()));
    }

    CORE_INFO("Initialised Dat Engine");

    int windowFlags = renderer->getWindowFlags();

    switch (windowModeCVar.getEnum()) {
        case DatGpu::WindowMode::Borderless:
            windowFlags |= SDL_WINDOW_BORDERLESS;
            break;
        case DatGpu::WindowMode::Fullscreen:
            windowFlags |= SDL_WINDOW_FULLSCREEN;
            break;
        default:;
    }

    instance->window = SDL_CreateWindow("Dat Engine", windowWidthCVar.get(), windowHeightCVar.get(), windowFlags);

    if (instance->window == nullptr) {
        throw DatException(fmt::format("Failed to create window - {}", SDL_GetError()));
    }

    instance->gpu = renderer;

    renderer->initialise();
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

SDL_Window* Engine::getWindow() const { return window; }
