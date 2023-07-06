//
// Created by jacob on 04/07/23.
//

#pragma once

#include "vector/vec3.h"
namespace DatMaths {
    /** A floating point 3 component vector */
    using vec3 = Vector<3, float>;

    /** An integer 3 component vector */
    using ivec3 = Vector<3, int>;

    /** An unsigned integer 3 component vector */
    using uvec3 = Vector<3, unsigned int>;

    /** A double precision floating point 3 component vector */
    using dvec3 = Vector<3, double>;
}
