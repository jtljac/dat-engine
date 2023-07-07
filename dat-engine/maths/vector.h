//
// Created by jacob on 04/07/23.
//

#pragma once

#include "vector/vec2.h"
#include "vector/vec3.h"
#include "vector/vec4.h"

namespace DatMaths {
    /** A floating point 2 component vector */
    using vec2 = Vector<2, float>;

    /** An integer 2 component vector */
    using ivec2 = Vector<2, int>;

    /** An unsigned integer 2 component vector */
    using uvec2 = Vector<2, unsigned int>;

    /** A double precision floating point 2 component vector */
    using dvec2 = Vector<2, double>;

    /* -------------------------------------------- */

    /** A floating point 3 component vector */
    using vec3 = Vector<3, float>;

    /** An integer 3 component vector */
    using ivec3 = Vector<3, int>;

    /** An unsigned integer 3 component vector */
    using uvec3 = Vector<3, unsigned int>;

    /** A double precision floating point 3 component vector */
    using dvec3 = Vector<3, double>;

    /* -------------------------------------------- */

    /** A floating point 4 component vector */
    using vec4 = Vector<4, float>;

    /** An integer 4 component vector */
    using ivec4 = Vector<4, int>;

    /** An unsigned integer 4 component vector */
    using uvec4 = Vector<4, unsigned int>;

    /** A double precision floating point 4 component vector */
    using dvec4 = Vector<4, double>;
}
