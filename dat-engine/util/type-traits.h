//
// Created using http://web.archive.org/web/20170705074036/https://rmf.io/cxx11/almost-static-if
//

#pragma once

#include <type_traits>
#include <concepts>

template <typename T>
concept integral = std::is_integral_v<T>;

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

template <typename T>
concept numeric = integral<T> || floating_point<T>;

template<typename lhType, typename rhType>
concept comparable_to = requires(lhType lh, rhType rh) {
    {lh < rh} -> std::convertible_to<bool>;
    {lh > rh} -> std::convertible_to<bool>;
    {lh <= rh} -> std::convertible_to<bool>;
    {lh >= rh} -> std::convertible_to<bool>;
};


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