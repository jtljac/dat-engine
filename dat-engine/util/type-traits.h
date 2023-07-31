//
//
//

#pragma once

#include <type_traits>
#include <concepts>

/* -------------------------------------------- */
/*  Concepts                                    */
/* -------------------------------------------- */

template <typename T>
concept integral = std::is_integral_v<T>;

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

template <typename T>
concept numeric = integral<T> || floating_point<T>;

template <typename T, typename base>
concept subClass = std::is_base_of_v<base, T>;

template <typename T, typename exactType>
concept exactClass = std::same_as<T, exactType>;

template <typename T, typename convertsToType>
concept convertsTo = std::convertible_to<T, convertsToType>;

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