#pragma once

#include <maths/vector/Vec3.h>
#include <util/TypeTraits.h>

namespace DatEngine::DatMaths {
    template<TypeTraits::CFloating TComponent>
    struct Quaternion {
        typedef Quaternion TQuat;

        Vector<3, TComponent> vec;
        TComponent s;
    };
} // namespace DatEngine::DatMaths
