#pragma once

#include <maths/vector.h>

struct SDL_Window;

namespace DatEngine {

    class IWindow {
    protected:
        SDL_Window* window;

        DatMaths::uvec2 getDimensions() {

        }
    };
}
