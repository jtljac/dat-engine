#pragma once

#include <util/type-traits.h>

namespace DatEngine::DatMaths {
    /**
     * A type representing a Vector of custom length
     * @tparam size The number of components of the vector
     * @tparam vecType The type of the vector's components
     */
    template<int size, numeric vecType>
    struct Vector;
}