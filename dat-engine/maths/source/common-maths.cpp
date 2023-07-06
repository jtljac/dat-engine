//
// Created by jacob on 06/07/23.
//

#include "../common-maths.h"

float DatMaths::sqrt(float value) {
    // TODO: This could be converted to intrinsics if it doesn't already convert into _mm_sqrt_ss
    return std::sqrt(value);
}

float DatMaths::invSqrt(float value) {
    // TODO: This could be converted to intrinsics if it doesn't already convert into _mm_rsqrt_ss
    return 1/std::sqrt(value);
}
