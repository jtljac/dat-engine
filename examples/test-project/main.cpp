//
// Created by jacob on 27/06/23.
//


#include <iostream>

#include <SDL.h>
#include <rendering/vulkan/vulkan-renderer.h>
#include <util/logger.h>

#include "dat-engine.h"

using namespace DatEngine;

int main() {
    VulkanRenderer renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    DatLog::init();
    renderer.initialise();
}