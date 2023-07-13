//
// Created by jacob on 13/07/23.
//

#pragma once

#include <string>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

namespace DatMaths {
    template <typename vecType>
    std::string to_string(Vector<2, vecType> vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "}";
    }

    template <typename vecType>
    std::string to_string(Vector<3, vecType> vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "}";
    }

    template <typename vecType>
    std::string to_string(Vector<4, vecType> vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "}";
    }
}

template <typename ostream, int vecSize, typename vecType>
ostream& operator<<(ostream& stream, DatMaths::Vector<vecSize, vecType> vec) {
    return stream << DatMaths::to_string<vecSize, vecType>(vec);
}