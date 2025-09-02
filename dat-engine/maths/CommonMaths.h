#pragma once
#include <cmath>
#include <util/TypeTraits.h>

// Keep windows maths out of this
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
    template<floating_point T>
    T sin(T value) {
        return std::sin(value);
    }

    template<floating_point T>
    T asin(T value) {
        return std::asin(value);
    }

    // Cos
    template<floating_point T>
    T cos(T value) {
        return std::cos(value);
    }

    template<floating_point T>
    T acos(T value) {
        return std::acos(value);
    }

    // Tan
    template<floating_point T>
    T tan(T value) {
        return std::tan(value);
    }

    template<floating_point T>
    T atan(T value) {
        return std::atan(value);
    }

    template<floating_point T>
    T atan2(T x, T y) {
        return std::atan2(x, y);
    }

    /* -------------------------------------------- */
    /*  Interpolation                               */
    /* -------------------------------------------- */

    /**
     * A concept defining requirements for a lerping function
     * <br>
     * This concept should permit classes like vectors and to support lerping
     * @tparam T The type of the values being lerped between
     * @tparam TAlpha The type of the value used to interpolate
     */
    template<typename T, typename TAlpha>
    concept lerpable = requires(T a, T b, TAlpha alpha) {
        requires floating_point<TAlpha>;
        { a + b } -> std::same_as<T>;
        { a* alpha } -> std::same_as<T>;
        { b* alpha } -> std::same_as<T>;
    };

    /**
     * Get a value a certain percentage (determined by the alpha) between the two points a and b.
     * <br>
     * Should be faster but less accurate than std::lerp(), which has a lot going on to ensure accuracy
     * @tparam T The type of be values being interpolated
     * @tparam TAlpha The type of the value used to interpolate
     * @param a The start value
     * @param b The end value
     * @param alpha The value used to interpolate
     * @return the interpolated value
     */
    template<typename T, floating_point TAlpha = float>
        requires lerpable<T, TAlpha>
    T lerp(T a, T b, TAlpha alpha) {
        return a * (1 - alpha) + b * alpha;
    }

    /**
     * Get how far between two given values (a & b) a given value (value) is
     * @tparam T The type of be values being interpolated
     * @param value The value in the range
     * @param a The start of the range
     * @param b The end of the range
     * @return A value representing har far between a & b the given value is
     */
    template<floating_point T>
    T invLerp(T value, T a, T b) {
        return (value - a) / (b - a);
    }

    /**
     * Mostly linear with a slight gentle slowing near 0 and 1, clamped between 0 and 1
     * <br>
     * Source: https://thebookofshaders.com/glossary/?search=smoothstep
     * @tparam T The type of the value
     * @param value The value to convert
     * @return the value converted to smoothstep
     */
    template<floating_point T>
    T smoothStep(T value) {
        value = clamp(value, 0, 1);
        return std::pow(value, 2) * (3 - (2 * value));
    }

    /**
     * A specified number of discrete steps between 0 and 1
     * @tparam T The type of the value
     * @param value The value to convert
     * @param steps The number of steps to the end
     * @return the value converted to stepped
     */
    template<floating_point T>
    T step(T value, int steps) {
        return std::floor(value * steps) / (steps - 1);
    }

    /**
     * Slow around 0, fairly linear after 0.5
     * <br>
     * Source (modified to include exponents): https://easings.net/#easeInQuad
     * @tparam T The type of the value
     * @param value The value to convert
     * @param exponent How extreme the effect is
     * @return the value converted to ease in
     */
    template<floating_point T>
    T easeIn(T value, T exponent) {
        value = clamp(value, 0, 1);
        return std::pow(value, exponent);
    }

    /**
     * Slow around 0, mostly linear before 0.5
     * Source (modified to include exponents): https://easings.net/#easeOutQuad
     * @tparam T The type of the value
     * @param value The value to convert
     * @param exponent How extreme the effect is
     * @return the value converted to ease out
     */
    template<floating_point T>
    T easeOut(T value, T exponent) {
        value = clamp(value, 0, 1);
        return 1 - std::pow(1 - value, exponent);
    }

    /**
     * Slow around 0, linear around 0.5, slow around 1
     * @tparam T The type of the value
     * @param value The value to convert
     * @param exponent How extreme the effect is
     * @return the value converted to ease in out
     */
    template<floating_point T>
    T easeInOut(T value, T exponent) {
        value = clamp(value, 0, 1);
        return value < 0.5f ? easeIn(2 * value, exponent) * 0.5 : easeOut(2 * value - 1, exponent) * 0.5;
    }

    /* -------------------------------------------- */
    /*  Misc                                        */
    /* -------------------------------------------- */

    /**
     * Compare two values and return the smallest one
     * @tparam T The type of the parameters
     * @param lh The left hand value
     * @param rh The right hand value
     * @return lh if it is smaller than rh, otherwise rh
     */
    template<typename T>
        requires CComparableTo<T, T>
    T min(T lh, T rh) {
        return lh < rh ? lh : rh;
    }

    /**
     * Compare two values and return the bigger value
     * @tparam T The type of the parameters
     * @param lh The left hand value
     * @param rh The right hand value
     * @return lh if it is bigger than rh, otherwise rh
     */
    template<typename T>
        requires CComparableTo<T, T>
    T max(T lh, T rh) {
        return lh > rh ? lh : rh;
    }

    /**
     * clamp a value to a range
     * <br>
     * Values exceeding the max will return the max, values less than the min will return the min
     * @tparam T The type of the min, max, and value parameters
     * @param value The value to clamp
     * @param min The minimum value to clamp the value to
     * @param max The maximum value to clamp the value to
     * @return min if the value is less than min, max if the value is greater than max, value in all other cases
     */
    template<typename T>
        requires CComparableTo<T, T>
    T clamp(T value, T min, T max) {
        return DatMaths::max(DatMaths::min(value, max), min);
    }
} // namespace DatEngine::DatMaths
