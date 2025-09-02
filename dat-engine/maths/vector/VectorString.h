#pragma once

#include <sstream>
#include <string>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "VecN.h"

namespace DatEngine::DatMaths {
    template<typename TComponent>
    std::string to_string(const Vector<2, TComponent>& vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "}";
    }

    template<typename TComponent>
    std::string to_string(const Vector<3, TComponent>& vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "}";
    }

    template<typename TComponent>
    std::string to_string(const Vector<4, TComponent>& vec) {
        return "{" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", "
               + std::to_string(vec.w) + "}";
    }

    template<int size, typename TComponent>
        requires(size > 4)
    std::string to_string(const Vector<size, TComponent>& vec) {
        // All vector sizes could use this function, but the string streaming is slower so when possible use specific
        // above
        std::stringstream stream;
        stream << "{" << vec[0];

        for (int i = 1; i < size; ++i) {
            stream << ", " << vec[i];
        }

        stream << "}";

        return stream.str();
    }
} // namespace DatEngine::DatMaths

template<typename ostream, int vecSize, typename TVec>
ostream& operator<<(ostream& stream, DatEngine::DatMaths::Vector<vecSize, TVec> vec) {
    return stream << DatEngine::DatMaths::to_string<vecSize, TVec>(vec);
}
