//
// Created by jacob on 04/07/23.
//

#pragma once

#include "vec-forward.h"

#include <compare>

#include <util/type-traits.h>
#include <maths/numbers.h>
#include <maths/common-maths.h>

// TODO: Create unit tests for each function
namespace DatMaths {
    template<typename componentType>
    /**
     * A struct representing a 3 component vector
     * @tparam componentType The type of the components of the vector
     */
    struct Vector<3, componentType> {
        typedef Vector<3, componentType> vecType;

        /** The components of the vector */
        componentType x, y, z;

        /* -------------------------------------------- */
        /*  Statics                                     */
        /* -------------------------------------------- */

        /**
         * A unit vector that faces north
         */
        const static vecType NORTH = vecType(0, 0, 1);

        /**
         * A unit vector that faces east
         */
        const static vecType EAST = vecType(1, 0, 0);

        /**
         * A unit vector that faces south
         */
        const static vecType SOUTH = vecType(0, 0, -1);

        /**
         * A unit vector that faces west
         */
        const static vecType WEST = vecType(-1, 0, 0);

        /**
         * A unit vector that faces up
         */
        const static vecType UP = vecType(0, -1, 0);

        /**
         * A unit vector that faces down
         */
        const static vecType north = vecType(0, 1, 0);

        /* -------------------------------------------- */
        /*  Initialisation                              */
        /* -------------------------------------------- */

        /**
         * Initialises all components to 0
         */
        Vector() : x(0), y(0), z(0) {}

        /**
         * Initialises all components to the same value
         * @param scalar The value to initialise the components to
         */
        Vector(componentType scalar) : x(scalar), y(scalar), z(scalar) {}

        /**
         * Initialises each component to their given value
         * @param x The value to initialise the x component to
         * @param y The value to initialise the y component to
         * @param z The value to initialise the z component to
         */
        Vector(componentType x, componentType y, componentType z) : x(x), y(y), z(z)  {}

        /* -------------------------------------------- */

        // Copy
        // Vec2
        /**
         * Initialise using a Vec2 and a z component
         * @tparam otherType The type of the Vec2
         * @param otherVec The Vec2 to source the values of the X and Y components from
         * @param z The value of the z component
         */
        template<typename otherType>
        Vector(const Vector<2, otherType>& otherVec, componentType z) : x(static_cast<componentType>(otherVec.x)),
                                                                        y(static_cast<componentType>(otherVec.y)),
                                                                        z(z) {}

        // Vec3
        /**
         * Initialise using the values from another Vec3
         * @tparam otherType The type of the other Vec3
         * @param otherVec The other Vec3 to source the values of the X, Y, and Z components from
         */
        template<typename otherType>
        Vector(const Vector<3, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                       y(static_cast<componentType>(otherVec.y)),
                                                       z(static_cast<componentType>(otherVec.z)) {}

        // Vec4
        /**
         * Initialise using the values from a Vec4
         * @tparam otherType The type of the Vec4
         * @param otherVec The Vec4 to source the values of the X,Y, and Z components from (w is discarded)
         */
        template<typename otherType>
        Vector(const Vector<4, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                                 y(static_cast<componentType>(otherVec.y)),
                                                                 z(static_cast<componentType>(otherVec.z)) {}

        /* -------------------------------------------- */

        // Assignment operator
        template<typename otherType>
        vecType& operator=(const Vector<3, otherType>& otherVec) {
            x = static_cast<componentType>(otherVec.x);
            y = static_cast<componentType>(otherVec.y);
            z = static_cast<componentType>(otherVec.z);
            return *this;
        }

        /* -------------------------------------------- */
        /*  Maths                                       */
        /* -------------------------------------------- */

        // Add Vector
        template<typename otherType>
        vecType operator+(const Vector<3, otherType>& rhs) const {
            return {
                x + static_cast<componentType>(rhs.x),
                y + static_cast<componentType>(rhs.y),
                z + static_cast<componentType>(rhs.z)
            };
        }

        // Add Scalar
        template<typename otherType>
        vecType operator+(const otherType rhs) const {
            return {
                    x + static_cast<componentType>(rhs),
                    y + static_cast<componentType>(rhs),
                    z + static_cast<componentType>(rhs)
            };
        }

        // Add Vector In-Place
        template<typename otherType>
        vecType& operator+=(const Vector<3, otherType>& rhs) const {
            x += static_cast<componentType>(rhs.x);
            y += static_cast<componentType>(rhs.y);
            z += static_cast<componentType>(rhs.z);

            return *this;
        }

        // Add Scalar In-Place
        template<typename otherType>
        vecType& operator+=(const otherType rhs) const {
            x += static_cast<componentType>(rhs);
            y += static_cast<componentType>(rhs);
            z += static_cast<componentType>(rhs);

            return *this;
        }

        /* -------------------------------------------- */

        // Minus Vector
        template<typename otherType>
        vecType operator-(const Vector<3, otherType>& rhs) const {
            return {
                    x - static_cast<componentType>(rhs.x),
                    y - static_cast<componentType>(rhs.y),
                    z - static_cast<componentType>(rhs.z)
            };
        }

        // Minus Scalar
        template<typename otherType>
        vecType operator-(const otherType rhs) const {
            return {
                    x - static_cast<componentType>(rhs),
                    y - static_cast<componentType>(rhs),
                    z - static_cast<componentType>(rhs)
            };
        }

        // Minus Vector In-Place
        template<typename otherType>
        vecType& operator-=(const Vector<3, otherType>& rhs) const {
            x -= static_cast<componentType>(rhs.x);
            y -= static_cast<componentType>(rhs.y);
            z -= static_cast<componentType>(rhs.z);

            return *this;
        }

        // Minus Scalar In-Place
        template<typename otherType>
        vecType& operator-=(const otherType rhs) const {
            x -= static_cast<componentType>(rhs);
            y -= static_cast<componentType>(rhs);
            z -= static_cast<componentType>(rhs);

            return *this;
        }

        /* -------------------------------------------- */

        //   Negation
        vecType operator-() {
            return {
                -x,
                -y,
                -z
            };
        }

        /* -------------------------------------------- */

        // Multiply by Components
        template<typename otherType>
        vecType operator*(const Vector<3, otherType>& rhs) const {
            return {
                    x * static_cast<componentType>(rhs.x),
                    y * static_cast<componentType>(rhs.y),
                    z * static_cast<componentType>(rhs.z)
            };
        }

        // Multiply by Scalar
        template<typename otherType>
        vecType operator*(const otherType rhs) const {
            return {
                    x * static_cast<componentType>(rhs),
                    y * static_cast<componentType>(rhs),
                    z * static_cast<componentType>(rhs)
            };
        }

        // Multiply by Components In-Place
        template<typename otherType>
        vecType& operator*=(const Vector<3, otherType>& rhs) const {
            x *= static_cast<componentType>(rhs.x);
            y *= static_cast<componentType>(rhs.y);
            z *= static_cast<componentType>(rhs.z);

            return *this;
        }

        // Multiply by Scalar In-Place
        template<typename otherType>
        vecType& operator*=(const otherType rhs) const {
            x *= static_cast<componentType>(rhs);
            y *= static_cast<componentType>(rhs);
            z *= static_cast<componentType>(rhs);

            return *this;
        }

        /* -------------------------------------------- */

        // Divide by Components
        template<typename otherType>
        vecType operator/(const Vector<3, otherType>& rhs) const {
            return {
                    x / static_cast<componentType>(rhs.x),
                    y / static_cast<componentType>(rhs.y),
                    z / static_cast<componentType>(rhs.z)
            };
        }

        // Divide by Scalar
        template<typename otherType>
        vecType operator/(const otherType rhs) const {
            return {
                    x / static_cast<componentType>(rhs),
                    y / static_cast<componentType>(rhs),
                    z / static_cast<componentType>(rhs)
            };
        }

        // Divide by Components In-Place
        template<typename otherType>
        vecType& operator/=(const Vector<3, otherType>& rhs) const {
            x /= static_cast<componentType>(rhs.x);
            y /= static_cast<componentType>(rhs.y);
            z /= static_cast<componentType>(rhs.z);

            return *this;
        }

        // Divide by Scalar In-Place
        template<typename otherType>
        vecType& operator/=(const otherType rhs) const {
            x /= static_cast<componentType>(rhs);
            y /= static_cast<componentType>(rhs);
            z /= static_cast<componentType>(rhs);

            return *this;
        }

        /* -------------------------------------------- */

        /**
         * Get the dot product of this vector and a given vector
         * @tparam otherType The type of the other vector
         * @param otherVec The other vector
         * @return the dot product of this vector and the given vector
         */
        template<typename otherType>
        componentType dotProduct(Vector<3, otherType> otherVec) const {
            return x * static_cast<componentType>(otherVec.x)
                 + y * static_cast<componentType>(otherVec.y)
                 + z * static_cast<componentType>(otherVec.z);
        }

        /* -------------------------------------------- */

        /**
         * Get the dot product of this vector and a given vector
         * @tparam otherType The type of the other vector
         * @param otherVec The other vector
         * @return the dot product of this vector and the given vector
         */
        template<typename otherType>
        vecType crossProduct(Vector<3, otherType> otherVec) const {
            return {
                y * static_cast<componentType>(otherVec.z) - z * static_cast<componentType>(otherVec.y),
                z * static_cast<componentType>(otherVec.x) - x * static_cast<componentType>(otherVec.z),
                x * static_cast<componentType>(otherVec.y) - y * static_cast<componentType>(otherVec.x)
            };
        }

        /* -------------------------------------------- */

        /**
         * Get the magnitude of the vector
         * @return the magnitude of the vector
         */
        componentType length() const {
            return DatMaths::sqrt(lengthSquared());
        }

        /**
         * Get the magnitude squared of the vector
         * <br>
         * This saves an expensive sqrt operation so is preferable for some comparisons
         * @return The magnitude squared of the vector
         */
        componentType lengthSquared() const {
            return x * x
                 + y * y
                 + z * z;
        }

        /* -------------------------------------------- */

        /**
         * Normalise the vector in place
         */
        void normalise() {
            componentType invLength = DatMaths::invSqrt(lengthSquared());
            x *= invLength;
            y *= invLength;
            z *= invLength;
        }

        /**
         * Get the normalised copy of this vector
         * @return a normalised copy of this vector
         */
        vecType normalised() const {
            componentType invLength = DatMaths::invSqrt(lengthSquared());

            return {
                x * invLength,
                y * invLength,
                z * invLength
            };
        }

        /* -------------------------------------------- */
        /*  Comparison                                  */
        /* -------------------------------------------- */

        // Equals
        template<typename otherType>
        bool operator==(const Vector<3, otherType>& rhs) const {
            return x == rhs.x
                && y == rhs.y
                && z == rhs.z;
        }

        /**
         * Check if this vector is equal to another within a small tolerances
         * @tparam otherType The type of the other vector
         * @param rhs The other vector to compare to
         * @param tolerance How close the two vectors needs to be to be regarded as equal
         * @return true if equal within a tolerance
         */
        template<typename otherType>
        bool equal(const Vector<3, otherType>& rhs, componentType tolerance = static_cast<componentType>(numbers::tinyNumber)) const {
            return std::abs(x - static_cast<componentType>(rhs.x)) < tolerance
                && std::abs(y - static_cast<componentType>(rhs.y)) < tolerance
                && std::abs(z - static_cast<componentType>(rhs.z)) < tolerance;
        }

        // Not Equal
        template<typename otherType>
        bool operator!=(const Vector<3, otherType>& rhs) const {
            return !operator==(rhs);
        };

        /* -------------------------------------------- */

        // Less than
        template<typename otherType>
        bool operator<(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() < static_cast<componentType>(rhs.lengthSquared());
        };

        // Greater Than
        template<typename otherType>
        bool operator>(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() > static_cast<componentType>(rhs.lengthSquared());
        };

        // Less than or equal
        template<typename otherType>
        bool operator<=(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() <= static_cast<componentType>(rhs.lengthSquared());
        };

        // Greater than or equal
        template<typename otherType>
        bool operator>=(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() >= static_cast<componentType>(rhs.lengthSquared());
        };

        /* -------------------------------------------- */

        // UFO Operator
        template<typename otherType>
        std::strong_ordering operator<=>(const Vector<3, otherType>& rhs) const {
            return this->lengthSquared() <=> static_cast<componentType>(rhs.lengthSquared());
        }
    };
}