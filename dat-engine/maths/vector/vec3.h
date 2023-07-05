//
// Created by jacob on 04/07/23.
//

#pragma once

#include <compare>
#include <cmath>
#include <util/type-traits.h>

#include "vec-forward.h"
#include "maths/numbers.h"
#include "maths/common-maths.h"

namespace DatMaths {
    template<typename vecType>
    struct Vector<3, vecType> {
        typedef Vector<3, vecType> type;
        vecType x, y, z;

        // Statics
        //   North
        //   East
        //   South
        //   West
        //   Up
        //   Down

        // Initialisation
        //   Units
        //   Vec2
        //   Vec4
        //   Array
        //   Copy

        // Maths
        //   Add
        //   Minus
        //   Negation
        //   multiply
        //   Divide
        //   Dot Product
        //   Cross Product

        /**
         *Get the magnitude of the vector
         * @return the magnitude of the vector
         */
        vecType length() {
            return DatMaths::sqrt(lengthSquared());
        }

        /**
         * Get the magnitude squared of the vector
         * <br>
         * This saves an expensive sqrt operation so is preferable for some comparisons
         * @return The magnitude squared of the vector
         */
        vecType lengthSquared() {
            return x * x + y * y + z * z;
        }

        //   Normalise
        /**
         * Normalise the vector in place
         */
        void normalise() {
            vecType invLength = DatMaths::invSqrt(lengthSquared());
            x *= invLength;
            y *= invLength;
            z *= invLength;
        }

        /**
         * Get the normalised copy of this vector
         * @return a normalised copy of this vector
         */
        type normalised() {
            vecType invLength = DatMaths::invSqrt(lengthSquared());

            return {
                x * invLength,
                y * invLength,
                z * invLength
            };
        }

        // Comparison
        template<typename otherType>
        bool operator==(const Vector<3, otherType>& rhs) const {
            return x == rhs.x &&
                   y == rhs.y &&
                   z == rhs.z;
        }

        /**
         * Check if this vector is equal to another within a small tolerances
         * @tparam otherType The type of the other vector
         * @param rhs The other vector to compare to
         * @param tolerance How close the two vectors needs to be to be regarded as equal
         * @return true if equal within a tolerance
         */
        template<typename otherType>
        bool equal(const Vector<3, otherType>& rhs, otherType tolerance = static_cast<otherType>(numbers::tinyNumber)) const {
            return std::abs(x - rhs.x) < tolerance &&
                   std::abs(y - rhs.y) < tolerance &&
                   std::abs(z - rhs.z) < tolerance;
        }

        template<typename otherType>
        bool operator!=(const Vector<3, otherType>& rhs) const {
            return !operator==(rhs);
        };

        template<typename otherType>
        bool operator<(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() < rhs.lengthSquared();
        };

        template<typename otherType>
        bool operator>(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() > rhs.lengthSquared();
        };

        template<typename otherType>
        bool operator<=(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() <= rhs.lengthSquared();
        };

        template<typename otherType>
        bool operator>=(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() >= rhs.lengthSquared();
        };

        template<typename otherType>
        std::strong_ordering operator<=>(const Vector<3, otherType>& rhs) {
            return this->lengthSquared() <=> rhs.lengthSquared();
        }


    };
}