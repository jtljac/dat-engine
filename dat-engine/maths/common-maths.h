//
// Created by jacob on 05/07/23.
//

#pragma once
#include <util/type-traits.h>
#include <cmath>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
// TODO: Test min and max
namespace DatMaths {
    /**
     * Get the square root of the given value
     * @param value The value to Square Root
     * @return the square root of the value
     */
    float sqrt(float value);

    /**
     * Get the inverse of the square root of the given value
     * @param value The value to Inverse Square Root
     * @return the inverse square root of the value
     */
    float invSqrt(float value);

    /**
     * Compare two values and return the smallest one
     * @tparam lhType The type of the left hand value
     * @tparam rhType The type of the right hand value
     * @param lh The left hand value
     * @param rh The right hand value
     * @return lh if it is smaller than rh, otherwise rh
     */
    template<typename lhType, typename rhType>
    requires comparable_to<lhType, rhType>
    bool min(lhType lh, rhType rh) {
        return lh < rh ? lh : rh;
    }

    /**
     * Compare two values and return the bigger value
     * @tparam lhType The type of the left hand value
     * @tparam rhType The type of the right hand value
     * @param lh The left hand value
     * @param rh The right hand value
     * @return lh if it is bigger than rh, otherwise rh
     */
    template<typename lhType, typename rhType>
    requires comparable_to<lhType, rhType>
    bool max(lhType lh, rhType rh) {
        return lh > rh ? lh : rh;
    }
}