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
     * A struct representing a 2 component vector
     * @tparam componentType The type of the components of the vector
     */
    struct Vector<2, componentType> {
        typedef Vector<2, componentType> vecType;

        /** The components of the vector */
        componentType x, y;

        /* -------------------------------------------- */
        /*  Statics                                     */
        /* -------------------------------------------- */

        /**
         * A unit vector that faces up (0, -1)
         */
        const static vecType UP;

        /**
         * A unit vector that faces right (1, 0)
         */
        const static vecType RIGHT;

        /**
         * A unit vector that faces down (0, 1)
         */
        const static vecType DOWN;

        /**
         * A unit vector that faces left (-1, 0)
         */
        const static vecType LEFT;

        /* -------------------------------------------- */
        /*  Initialisation                              */
        /* -------------------------------------------- */

        /**
         * Initialises all components to 0
         */
        Vector() : x(0), y(0) {}

        /**
         * Initialises all components to the same value
         * @param scalar The value to initialise the components to
         */
        explicit Vector(componentType scalar) : x(scalar), y(scalar) {}

        /**
         * Initialises each component to their given value
         * @param x The value to initialise the x component to
         * @param y The value to initialise the y component to
         */
        Vector(componentType x, componentType y) : x(x), y(y)  {}

        /* -------------------------------------------- */

        // Copy
        // Vec2
        /**
         * Initialise using another Vec2
         * @tparam otherType The type of the Vec2
         * @param otherVec The other Vec2 to source the values of the X and Y components from
         */
        template<typename otherType>
        explicit Vector(const Vector<2, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                       y(static_cast<componentType>(otherVec.y)) {}

        // Vec3
        /**
         * Initialise using the values from a Vec3
         * @tparam otherType The type of the Vec3
         * @param otherVec The Vec3 to source the values of the X and Y components from (z is discarded)
         */
        template<typename otherType>
        explicit Vector(const Vector<3, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                       y(static_cast<componentType>(otherVec.y)) {}

        // Vec4
        /**
         * Initialise using the values from a Vec4
         * @tparam otherType The type of the Vec4
         * @param otherVec The Vec4 to source the values of the X and Y components from (z and w is discarded)
         */
        template<typename otherType>
        explicit Vector(const Vector<4, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                       y(static_cast<componentType>(otherVec.y)) {}

        /* -------------------------------------------- */

        // Assignment operator
        template<typename otherType>
        vecType& operator=(const Vector<2, otherType>& otherVec);

        /* -------------------------------------------- */
        /*  Maths                                       */
        /* -------------------------------------------- */

        // Add Vector
        template<typename otherType>
        vecType operator+(const Vector<2, otherType>& rhs) const;

        // Add Scalar
        template<typename otherType>
        vecType operator+(otherType rhs) const;

        // Add Vector In-Place
        template<typename otherType>
        vecType& operator+=(const Vector<2, otherType>& rhs) const;

        // Add Scalar In-Place
        template<typename otherType>
        vecType& operator+=(otherType rhs) const;

        /* -------------------------------------------- */

        // Minus Vector
        template<typename otherType>
        vecType operator-(const Vector<2, otherType>& rhs) const;

        // Minus Scalar
        template<typename otherType>
        vecType operator-(otherType rhs) const;

        // Minus Vector In-Place
        template<typename otherType>
        vecType& operator-=(const Vector<2, otherType>& rhs) const;

        // Minus Scalar In-Place
        template<typename otherType>
        vecType& operator-=(otherType rhs) const;

        /* -------------------------------------------- */

        //   Negation
        vecType operator-();

        /* -------------------------------------------- */

        // Multiply by Components
        template<typename otherType>
        vecType operator*(const Vector<2, otherType>& rhs) const;

        // Multiply by Scalar
        template<typename otherType>
        vecType operator*(otherType rhs) const;

        // Multiply by Components In-Place
        template<typename otherType>
        vecType& operator*=(const Vector<2, otherType>& rhs) const;

        // Multiply by Scalar In-Place
        template<typename otherType>
        vecType& operator*=(otherType rhs) const;

        /* -------------------------------------------- */

        // Divide by Components
        template<typename otherType>
        vecType operator/(const Vector<2, otherType>& rhs) const;

        // Divide by Scalar
        template<typename otherType>
        vecType operator/(otherType rhs) const;

        // Divide by Components In-Place
        template<typename otherType>
        vecType& operator/=(const Vector<2, otherType>& rhs) const;

        // Divide by Scalar In-Place
        template<typename otherType>
        vecType& operator/=(otherType rhs) const;

        /* -------------------------------------------- */

        /**
         * Get the dot product of this vector and a given vector
         * @tparam otherType The type of the other vector
         * @param otherVec The other vector
         * @return the dot product of this vector and the given vector
         */
        template<typename otherType>
        componentType dotProduct(Vector<2, otherType> otherVec) const;

        /* -------------------------------------------- */

        /**
         * Get the magnitude of the vector
         * @return the magnitude of the vector
         */
        componentType length() const;

        /**
         * Get the magnitude squared of the vector
         * <br>
         * This saves an expensive sqrt operation so is preferable for some comparisons
         * @return The magnitude squared of the vector
         */
        componentType lengthSquared() const;

        /* -------------------------------------------- */

        /**
         * Normalise the vector in place
         */
        void normalise();

        /**
         * Get the normalised copy of this vector
         * @return a normalised copy of this vector
         */
        vecType normalised() const;

        /* -------------------------------------------- */

        /**
         * Get a Vec2 that is perpendicular to this one
         * <br>
         * There are two possible perpendicular vectors, clockwise and anti-clockwise, which direction is chosen based
         * on the value of the clockwise parameter
         * <br>
         * Clockwise: ┴ -> ├
         * <br>
         * anti-clockwise: ┴ -> ┤
         * @param clockwise Whether to get the clockwise perpendicular, if false then the function will return the
         * anti-clockwise perpendicular
         * @return a Vec2 that is perpendicular to this one
         */
        vecType perpendicular(bool clockwise) const;

        /* -------------------------------------------- */
        /*  Comparison                                  */
        /* -------------------------------------------- */

        // Equals
        template<typename otherType>
        bool operator==(const Vector<2, otherType>& rhs) const;

        /**
         * Check if this vector is equal to another within a small tolerances
         * @tparam otherType The type of the other vector
         * @param rhs The other vector to compare to
         * @param tolerance How close the two vectors needs to be to be regarded as equal
         * @return true if equal within a tolerance
         */
        template<typename otherType>
        bool equal(const Vector<2, otherType>& rhs, componentType tolerance = static_cast<componentType>(numbers::tinyNumber)) const;

        // Not Equal
        template<typename otherType>
        bool operator!=(const Vector<2, otherType>& rhs) const;;

        /* -------------------------------------------- */

        // Less than
        template<typename otherType>
        bool operator<(const Vector<2, otherType>& rhs) const;

        // Greater Than
        template<typename otherType>
        bool operator>(const Vector<2, otherType>& rhs) const;

        // Less than or equal
        template<typename otherType>
        bool operator<=(const Vector<2, otherType>& rhs) const;

        // Greater than or equal
        template<typename otherType>
        bool operator>=(const Vector<2, otherType>& rhs) const;

        /* -------------------------------------------- */

        // UFO Operator
        template<typename otherType>
        std::strong_ordering operator<=>(const Vector<2, otherType>& rhs) const;
    };

#include "source/vec2.inl"
}