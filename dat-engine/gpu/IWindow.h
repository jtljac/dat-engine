#pragma once

#include <maths/Vector.h>

struct SDL_Window;

namespace DatEngine {

    class IWindow {
    protected:
        SDL_Window* window;

        DatMaths::uvec2 getDimensions();
    };
} // namespace DatEngine
