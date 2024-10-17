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
namespace DatEngine::DatMaths {
    // If these aren't commented then it's because there's nothing to add with a comment
    /* -------------------------------------------- */
    /*  Square Root                                 */
    /* -------------------------------------------- */

    float sqrt(float value);

    float invSqrt(float value);

    /* -------------------------------------------- */
    /*  Trigonometry                                */
    /* -------------------------------------------- */

    // TODO: See if any of these can be approximated

    // Sin
    template<floating_point type>
    inline type sin(type value) {
        return std::sin(value);
    }

    template<floating_point type>
    inline type asin(type value) {
        return std::asin(value);
    }

    // Cos
    template<floating_point type>
    inline type cos(type value) {
        return std::cos(value);
    }

    template<floating_point type>
    inline type acos(type value) {
        return std::acos(value);
    }

    // Tan

    template<floating_point type>
    inline type tan(type value) {
        return std::tan(value);
    }

    template<floating_point type>
    inline type atan(type value) {
        return std::atan(value);
    }

    template<floating_point type>
    inline type atan2(type x, type y) {
        return std::atan2(x, y);
    }

    /* -------------------------------------------- */
    /*  Interpolation                               */
    /* -------------------------------------------- */

    /**
     * A concept defining requirements for a lerping function
     * <br>
     * This concept should permit classes like vectors and to support lerping
     * @tparam type The type of the values being lerped between
     * @tparam alphaType The type of the value used to interpolate
     */
    template<typename type, typename alphaType>
    concept lerpable = requires(type a, type b, alphaType alpha) {
        requires floating_point<alphaType>;
        {a + b} -> std::same_as<type>;
        {a * alpha} -> std::same_as<type>;
        {b * alpha} -> std::same_as<type>;
    };

    /**
     * Get a value a certain percentage (determined by the alpha) between the two points a and b.
     * <br>
     * Should be faster but less accurate than std::lerp(), which has a lot going on to ensure accuracy
     * @tparam type The type of be values being interpolated
     * @tparam alphaType The type of the the value used to interpolate
     * @param a The start value
     * @param b The end value
     * @param alpha The value used to interpolate
     * @return the interpolated value
     */
    template<typename type, floating_point alphaType = float>
    requires lerpable<type, alphaType>
    type lerp(type a, type b, alphaType alpha) {
        return a * (1 - alpha) + b * alpha;
    }

    /**
     * Get how far between two given values (a & b) a given value (value) is
     * @tparam type The type of be values being interpolated
     * @param value The value in the range
     * @param a The start of the range
     * @param b The end of the range
     * @return A value representing har far between a & b the given value is
     */
    template<floating_point type>
    type invLerp(type value, type a, type b) {
        return (value - a) / (b - a);
    }

    /**
     * Mostly linear with a slight gentle slowing near 0 and 1, clamped between 0 and 1
     * <br>
     * Source: https://thebookofshaders.com/glossary/?search=smoothstep
     * @tparam type The type of the value
     * @param value The value to convert
     * @return the value converted to smoothstep
     */
    template<floating_point type>
    type smoothStep(type value) {
        value = clamp(value, 0, 1);
        return std::pow(value, 2) * (3 - (2 * value));
    }

    /**
     * A specified number of discrete steps between 0 and 1
     * @tparam type The type of the value
     * @param value The value to convert
     * @param steps The number of steps to the end
     * @return the value converted to stepped
     */
    template<floating_point type>
    type step(type value, int steps) {
        return std::floor(value * steps) / (steps - 1);
    }

    /**
     * Slow around 0, fairly linear after 0.5
     * <br>
     * Source (modified to include exponents): https://easings.net/#easeInQuad
     * @tparam type The type of the value
     * @param value The value to convert
     * @param exponent How extreme the effect is
     * @return the value converted to ease in
     */
    template<floating_point type>
    type easeIn(type value, type exponent) {
        value = clamp(value, 0, 1);
        return std::pow(value, exponent);
    }

    /**
     * Slow around 0, mostly linear before 0.5
     * Source (modified to include exponents): https://easings.net/#easeOutQuad
     * @tparam type The type of the value
     * @param value The value to convert
     * @param exponent How extreme the effect is
     * @return the value converted to ease out
     */
    template<floating_point type>
    type easeOut(type value, type exponent) {
        value = clamp(value, 0, 1);
        return 1 - std::pow(1 - value, exponent);
    }

    /**
     * Slow around 0, linear around 0.5, slow around 1
     * @tparam type The type of the value
     * @param value The value to convert
     * @param exponent How extreme the effect is
     * @return the value converted to ease in out
     */
    template<floating_point type>
    type easeInOut(type value, type exponent) {
        value = clamp(value, 0, 1);
        return value < 0.5f ? easeIn(2 * value, exponent) * 0.5 : easeOut(2 * value - 1, exponent) * 0.5;
    }

    /* -------------------------------------------- */
    /*  Misc                                        */
    /* -------------------------------------------- */

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

    /**
     * clamp a value to a range
     * <br>
     * Values exceeding the max will return the max, values less than the min will return the min
     * @tparam type The type of the min, max, and value parameters
     * @param value The value to clamp
     * @param min The minimum value to clamp the value to
     * @param max The maximum value to clamp the value to
     * @return min if the value is less than min, max if the value is greater than max, value in all other cases
     */
    template<typename type>
    requires comparable_to<type, type>
    bool clamp(type value, type min, type max) {
        return DatMaths::max(DatMaths::min(value, max), min);
    }
}