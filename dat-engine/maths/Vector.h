#pragma once

#include "vector/Vec1.h"
#include "vector/Vec2.h"
#include "vector/Vec3.h"
#include "vector/Vec4.h"
#include "vector/VecN.h"

namespace DatEngine::DatMaths {
    /** A floating point 1 component vector */
    using vec1 = Vector<1, float>;

    /** An integer 1 component vector */
    using ivec1 = Vector<1, int>;

    /** An unsigned integer 1 component vector */
    using uvec1 = Vector<1, unsigned int>;

    /** A double precision floating point 1 component vector */
    using dvec1 = Vector<1, double>;

    /* -------------------------------------------- */

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

    /* -------------------------------------------- */

    /** A floating point n component vector */
    template<int size>
        requires(size > 4)
    using vecn = Vector<size, float>;

    /** A integer n component vector */
    template<int size>
        requires(size > 4)
    using ivecn = Vector<size, int>;

    /** A unsigned integer n component vector */
    template<int size>
        requires(size > 4)
    using uvecn = Vector<size, unsigned int>;

    /** A double precision floating point n component vector */
    template<int size>
        requires(size > 4)
    using dvecn = Vector<size, double>;
} // namespace DatEngine::DatMaths
