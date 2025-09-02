#pragma once
#include <type_traits>

/**
 * A macro to add bitwise operators to an enum so it can better support use as flags
 *
 * Inspired by https://stackoverflow.com/a/33971769
 *
 * @param ENUM_TYPE The enum type to attach the methods to
 */
#define ENUM_FLAGS(ENUM_TYPE)                                                                                          \
    constexpr ENUM_TYPE operator|(const ENUM_TYPE selfValue, const ENUM_TYPE inValue) {                                \
        return static_cast<ENUM_TYPE>(                                                                                 \
                static_cast<std::underlying_type_t<ENUM_TYPE>>(selfValue)                                              \
                | static_cast<std::underlying_type_t<ENUM_TYPE>>(inValue)                                              \
        );                                                                                                             \
    }                                                                                                                  \
    constexpr ENUM_TYPE operator&(const ENUM_TYPE selfValue, const ENUM_TYPE inValue) {                                \
        return static_cast<ENUM_TYPE>(                                                                                 \
                static_cast<std::underlying_type_t<ENUM_TYPE>>(selfValue)                                              \
                & static_cast<std::underlying_type_t<ENUM_TYPE>>(inValue)                                              \
        );                                                                                                             \
    }                                                                                                                  \
    constexpr ENUM_TYPE operator^(const ENUM_TYPE selfValue, const ENUM_TYPE inValue) {                                \
        return static_cast<ENUM_TYPE>(                                                                                 \
                static_cast<std::underlying_type_t<ENUM_TYPE>>(selfValue)                                              \
                ^ static_cast<std::underlying_type_t<ENUM_TYPE>>(inValue)                                              \
        );                                                                                                             \
    }


#define STRINGIFY_(X) #X
#define STRINGIFY(X) STRINGIFY_(X)

#define CAT_(a, b) a##b
#define CAT(a, b) CAT_(a, b)
