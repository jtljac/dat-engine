#pragma once

#include <util/TypeTraits.h>

namespace DatEngine::DatMaths {
    /**
     * A type representing a Vector of custom length
     * @tparam size The number of components of the vector
     * @tparam TVec The type of the vector's components
     */
    template<int size, TypeTraits::CNumeric TVec>
    struct Vector;
} // namespace DatEngine::DatMaths
