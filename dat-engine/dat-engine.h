#pragma once

#include <maths/vector.h>
#include <SDL.h>
#include <iostream>

enum class EngineRunningState {

};

class DatEngine {
    // Renderer
    // Asset Manager
    // Input Manager
    // Audio Engine
    // UI

    bool shouldClose;

public:
    void init() {
        SDL_Init(SDL_INIT_EVERYTHING);
    }

    void startLoop() {

        uint64_t lastTime = SDL_GetTicks64();
        while (!shouldClose) {
            uint64_t now = SDL_GetTicks();
            float deltaTime = ((float) (now - lastTime)) / 1000;

            // Input
            //   Handle SDL events
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                switch (event.type) {
                }
            }

            // Update

            // Render
            // UI
        }
    }
};