//
// Created by jacob on 13/07/23.
//

#pragma once

#include <string>
#include <sstream>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "vecn.h"

namespace DatMaths {
    template <typename componentType>
    std::string to_string(const Vector<2, componentType>& vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "}";
    }

    template <typename componentType>
    std::string to_string(const Vector<3, componentType>& vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "}";
    }

    template <typename componentType>
    std::string to_string(const Vector<4, componentType>& vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "}";
    }

    template <int size, typename componentType>
    requires (size > 4)
    std::string to_string(const Vector<size, componentType>& vec) {
        // All vector sizes could use this function, but the string streaming is slower so when possible use specific above
        std::stringstream stream;
        stream << "{" << vec[0];

        for (int i = 1; i < size; ++i) {
            stream << ", " << vec[i];
        }

        stream << "}";

        return stream.str();
    }
}

template <typename ostream, int vecSize, typename vecType>
ostream& operator<<(ostream& stream, DatMaths::Vector<vecSize, vecType> vec) {
    return stream << DatMaths::to_string<vecSize, vecType>(vec);
}