//
// Created by jacob on 28/07/23.
//

#pragma once

#include <util/type-traits.h>
#include <maths/vector/vec3.h>

namespace DatEngine::DatMaths {
    template<floating_point componentType>
    struct Quaternion {
        typedef Quaternion<componentType> quatType;

        Vector<3, componentType> vec;
        componentType s;
    };
}