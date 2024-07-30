/**
 * Type-traits and concepts used by dat-engine
 */

#pragma once

#include <type_traits>
#include <concepts>

namespace DatEngine {
    /* -------------------------------------------- */
    /*  Concepts                                    */
    /* -------------------------------------------- */

    /**
     * Concept for testing if a value is an integer type
     */
    template <typename T>
    concept integral = std::is_integral_v<T>;

    /**
     * Concept for testing if a value is an unsigned integer type
     */
    template <typename T>
    concept uIntegral = std::is_integral_v<T> && std::is_unsigned_v<T>;

    /**
     * Concept for testing if a value is a signed integer type
     */
    template <typename T>
    concept sIntegral = std::is_integral_v<T> && std::is_signed_v<T>;

    /**
     * Concept for testing if a value is an floating point number
     */
    template <typename T>
    concept floating_point = std::is_floating_point_v<T>;


    /**
     * Concept for testing if a value is a number (floating point or integral)
     */
    template <typename T>
    concept numeric = integral<T> || floating_point<T>;

    /**
     * Concept for testing if a class is a subclass of another
     * @tparam T The class to test
     * @tparam base The base class to check if T is a child of
     */
    template <typename T, typename base>
    concept subClass = std::is_base_of_v<base, T>;

    /**
     * Concept for testing if a class is a super class of another
     * @tparam T The class to test
     * @tparam base The child class to check if T is a superclass of
     */
    template <typename T, typename sub>
    concept baseClass = std::is_base_of_v<T, sub>;

    /**
     * Concept for testing if a type is exactly the type `exactType`
     * @tparam T The type to test
     * @tparam exactType The class to check if `T` matchss
     */
    template <typename T, typename exactType>
    concept exactClass = std::same_as<T, exactType>;

    /**
     * Concept for testing if a type is convertable to another type
     * @tparam T The class to test
     * @tparam convertsToType The type to check T can convert to
     */
    template <typename T, typename convertsToType>
    concept convertsTo = std::convertible_to<T, convertsToType>;

    /**
     * Concept for testing if a type is comparible to another type
     * @tparam lhType The type on the left hand of the comparison
     * @tparam rhType The type on the right hand of the comparison
     */
    template<typename lhType, typename rhType>
    concept comparable_to = requires(lhType lh, rhType rh) {
        {lh < rh} -> std::convertible_to<bool>;
        {lh > rh} -> std::convertible_to<bool>;
        {lh <= rh} -> std::convertible_to<bool>;
        {lh >= rh} -> std::convertible_to<bool>;
    };

    /* -------------------------------------------- */
    /*  SFINAE Shortcuts                            */
    /* -------------------------------------------- */
    // Created using http://web.archive.org/web/20170705074036/https://rmf.io/cxx11/almost-static-if

    namespace detail {
        /**
         * A hack to prevent compilation errors with the EnableIf SFINAE shortcut
         */
        enum class enabler {};
    }

    /**
     * A SFINAE shortcut for std::enable_if
     */
    template <typename Condition>
    using EnableIf = typename std::enable_if<Condition::value, detail::enabler>::type;

    /**
     * A SFINAE shortcut for an inverse std::enable_if
     */
    template <typename Condition>
    using DisableIf = typename std::enable_if<!Condition::value, detail::enabler>::type;
}