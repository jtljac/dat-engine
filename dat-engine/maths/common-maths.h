//
// Created by jacob on 05/07/23.
//

#pragma once
#include <util/type-traits.h>
#include <cmath>

namespace DatMaths {
    /**
     * Get the square root of the given value
     * @param value The value to Square Root
     * @return the square root of the value
     */
    float sqrt(float value) {
        // TODO: This could be converted to intrinsics if it doesn't already convert into _mm_sqrt_ss
        return std::sqrt(value);
    }

    /**
     * Get the inverse of the square root of the given value
     * @param value The value to Inverse Square Root
     * @return the inverse square root of the value
     */
    float invSqrt(float value) {
        // TODO: This could be converted to intrinsics if it doesn't already convert into _mm_rsqrt_ss
        return 1/std::sqrt(value);
    }
}