/*
* The code in this file adapted from: https://github.com/vblanco20-1/vulkan-guide/blob/164c144c4819840a9e59cc955a91b74abea4bd6f/extra-engine/string_utils.h
* Under the MIT License: https://github.com/vblanco20-1/vulkan-guide/blob/164c144c4819840a9e59cc955a91b74abea4bd6f/LICENSE.txt
*
*/

#pragma once

#include <string>
#include <string_view>
#include <cstdint>
#include <cstring>


namespace DatEngine::StringUtils {
    /**
     * Calculate the hash of a string using the FNV-1a 32bit hashing algorithm.
     */
    constexpr uint32_t fnv1a_32(char const* s, const std::size_t count) {
        return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
    }

    /**
     * Count the number of characters in a string
     * @param s The string to calculate the length of
     * @return The number of characers in the given string
     */
    constexpr size_t const_strlen(const char* s) {
        size_t size = 0;
        while (s[size]) { ++size; };

        return size;
    }

    /**
     * A structure representing a String Hash, with helpers for compile time string conversion
     */
    struct StringHash {
        /** The Hash representing the string */
        const uint32_t computedHash;

        constexpr explicit StringHash(const uint32_t hash) noexcept : computedHash(hash) {}

        constexpr StringHash(const char* s) noexcept : computedHash(fnv1a_32(s, strlen(s))) {}

        constexpr StringHash(const char* s, const std::size_t count) noexcept : computedHash(fnv1a_32(s, count)) {}

        constexpr StringHash(const std::string_view s) noexcept : computedHash(fnv1a_32(s.data(), s.size())) {}

        StringHash(const StringHash& other) = default;

        constexpr operator uint32_t() const noexcept {
            return computedHash;
        }
    };
}
