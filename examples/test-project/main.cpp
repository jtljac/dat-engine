//
// Created by jacob on 27/06/23.
//


#include <iostream>

#include <SDL.h>
#include <util/logger.h>
#include <rendering/vulkan/vulkan-renderer.h>

int main() {
    VulkanRenderer renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    DatLog::init();
    renderer.initialise();
}