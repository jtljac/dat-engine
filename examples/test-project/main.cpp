//
// Created by jacob on 27/06/23.
//


#include <iostream>
#include <maths/vector.h>
#include <maths/vector/vector-string.h>

#include <SDL.h>
#include <util/logger.h>
#include <rendering/vulkan/vulkan-renderer.h>

int main() {

    DatMaths::vecn<5> test1{1.f, 2.f, 3.f, 4.f, 5.f};
    DatMaths::vecn<5> test2{2.f, 3.f, 4.f, 5.f, 1.f};

    std::cout << DatMaths::to_string(test1 + test2);
//    VulkanRenderer renderer;
//    SDL_Init(SDL_INIT_EVERYTHING);
//    DatLog::init();
//    renderer.initialise();
}