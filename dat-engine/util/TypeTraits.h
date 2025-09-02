/*
 * Type-traits and concepts used by dat-engine
 */

#pragma once

#include <concepts>
#include <type_traits>

namespace DatEngine {
    /* -------------------------------------------- */
    /*  Concepts                                    */
    /* -------------------------------------------- */

    /**
     * Concept for testing if a value is an integer type
     */
    template<typename T>
    concept integral = std::is_integral_v<T>;

    /**
     * Concept for testing if a value is an unsigned integer type
     */
    template<typename T>
    concept uIntegral = std::is_integral_v<T> && std::is_unsigned_v<T>;

    /**
     * Concept for testing if a value is a signed integer type
     */
    template<typename T>
    concept sIntegral = std::is_integral_v<T> && std::is_signed_v<T>;

    /**
     * Concept for testing if a value is a floating point number
     */
    template<typename T>
    concept floating_point = std::is_floating_point_v<T>;


    /**
     * Concept for testing if a value is a number (floating point or integral)
     */
    template<typename T>
    concept CNumeric = integral<T> || floating_point<T>;

    template<typename T>
    concept CEnumType = std::is_enum_v<T>;

    template<typename T>
    concept CIntegralEnumType = CEnumType<T> && CNumeric<std::underlying_type_t<T>>;


    /**
     * Concept for testing if a class is a subclass of another
     * @tparam T The class to test
     * @tparam base The base class to check if T is a child of
     */
    template<typename T, typename TBase>
    concept CSubClass = std::is_base_of_v<TBase, T>;

    /**
     * Concept for testing if a class is a super class of another
     * @tparam T The class to test
     * @tparam TSub The child class to check if T is a superclass of
     */
    template<typename T, typename TSub>
    concept CBaseClass = std::is_base_of_v<T, TSub>;

    /**
     * Concept for testing if a type is exactly the type `exactType`
     * @tparam T The type to test
     * @tparam TExact The class to check if `T` matchss
     */
    template<typename T, typename TExact>
    concept CExactClass = std::same_as<T, TExact>;

    /**
     * Concept for testing if a type is convertable to another type
     * @tparam T The class to test
     * @tparam TConvertTo The type to check T can convert to
     */
    template<typename T, typename TConvertTo>
    concept CConvertsTo = std::convertible_to<T, TConvertTo>;

    /**
     * Concept for testing if a type is comparable to another type
     * @tparam TLh The type on the left hand of the comparison
     * @tparam TRh The type on the right hand of the comparison
     */
    template<typename TLh, typename TRh>
    concept CComparableTo = requires(TLh lh, TRh rh) {
        { lh < rh } -> std::convertible_to<bool>;
        { lh > rh } -> std::convertible_to<bool>;
        { lh <= rh } -> std::convertible_to<bool>;
        { lh >= rh } -> std::convertible_to<bool>;
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
    } // namespace detail

    /**
     * A SFINAE shortcut for std::enable_if
     */
    template<typename Condition>
    using EnableIf = std::enable_if_t<Condition::value, detail::enabler>;

    /**
     * A SFINAE shortcut for an inverse std::enable_if
     */
    template<typename Condition>
    using DisableIf = std::enable_if_t<!Condition::value, detail::enabler>;
} // namespace DatEngine
