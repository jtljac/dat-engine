#pragma once

#include <maths/vector/Vec3.h>
#include <util/TypeTraits.h>

namespace DatEngine::DatMaths {
    template<floating_point TComponent>
    struct Quaternion {
        typedef Quaternion TQuat;

        Vector<3, TComponent> vec;
        TComponent s;
    };
} // namespace DatEngine::DatMaths
