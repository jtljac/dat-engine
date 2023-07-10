//
// Created by jacob on 10/07/23.
//

#pragma once

#include <maths/vector.h>

#include <SDL.h>

struct SDL_Window;

class iwindow {
protected:
    SDL_Window* window;

    DatMaths::uvec2 getDimensions() {

    }
};
