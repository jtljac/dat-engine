//
// Created by jacob on 08/07/23.
//

#pragma once

#include "iwindow.h"
#include <SDL.h>
#include <vector>
#include <string>

class IRenderer {
protected:
    std::vector<iwindow*> windows;

    virtual bool initialise() = 0;
    virtual void cleanup() = 0;

    virtual iwindow* createWindow(int width, int height, std::string name, uint32_t flags) {
//        SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    }
};
