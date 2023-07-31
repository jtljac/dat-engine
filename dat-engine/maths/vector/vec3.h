//
// Created by jacob on 04/07/23.
//

#pragma once

#include "vec-forward.h"

#include <compare>

#include <util/type-traits.h>
#include <maths/numbers.h>
#include <maths/common-maths.h>

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
         * A unit vector that faces north (0, 0, 1)
         */
        const static vecType NORTH;

        /**
         * A unit vector that faces east
         */
        const static vecType EAST;

        /**
         * A unit vector that faces south
         */
        const static vecType SOUTH;

        /**
         * A unit vector that faces west
         */
        const static vecType WEST;

        /**
         * A unit vector that faces up
         */
        const static vecType UP;

        /**
         * A unit vector that faces down
         */
        const static vecType DOWN;

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
        explicit Vector(componentType scalar) : x(scalar), y(scalar), z(scalar) {}

        /**
         * Initialises each component to their given value
         * @param x The value to initialise the x component to
         * @param y The value to initialise the y component to
         * @param z The value to initialise the z component to
         */
        Vector(componentType x, componentType y, componentType z) : x(x), y(y), z(z)  {}

        /* -------------------------------------------- */

        // Copy
        // Vec1
        /**
         * Initialise using just a Vec1, the Y, Z and W components will be initialised to 0
         * @tparam otherType The type of the Vec1
         * @param otherVec The Vec1 to source the values of the X component from
         */
        template<typename otherType>
        explicit Vector(const Vector<1, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                                y(0),
                                                                z(0) {}

        /**
          * Initialise using a Vec1, a Y component, and a Z component
          * @tparam otherType The type of the Vec1
          * @param otherVec The Vec1 to source the value of the X component from
          * @param y The value of the Y component
          * @param z The value of the Z component
          */
        template<typename otherType>
        Vector(const Vector<1, otherType>& otherVec, componentType y, componentType z) : x(static_cast<componentType>(otherVec.x)),
                                                                                                          y(y),
                                                                                                          z(z) {}

        // Vec2
        /**
         * Initialise using just a Vec2, Z will be initialised to 0
         * @tparam otherType The type of the Vec2
         * @param otherVec The Vec2 to source the values of the X and Y components from
         */
        template<typename otherType>
        explicit Vector(const Vector<2, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                                y(static_cast<componentType>(otherVec.y)),
                                                                z(0) {}

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
        explicit Vector(const Vector<3, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                                y(static_cast<componentType>(otherVec.y)),
                                                                z(static_cast<componentType>(otherVec.z)) {}

        // Vec4
        /**
         * Initialise using the values from a Vec4
         * @tparam otherType The type of the Vec4
         * @param otherVec The Vec4 to source the values of the X,Y, and Z components from (w is discarded)
         */
        template<typename otherType>
        explicit Vector(const Vector<4, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)),
                                                                y(static_cast<componentType>(otherVec.y)),
                                                                z(static_cast<componentType>(otherVec.z)) {}

        // Vecn
        /**
         * Initialise using the values from a Vecn
         * @tparam otherType The type of the Vecn
         * @param otherVec The Vecn to source the values of the X and Y components from
         */
        template<int otherSize, typename otherType>
        requires (otherSize > 4)
        explicit Vector(const Vector<otherSize, otherType>& otherVec) : x(static_cast<componentType>(otherVec[0])),
                                                                        y(static_cast<componentType>(otherVec[1])),
                                                                        z(static_cast<componentType>(otherVec[2])) {}

        /* -------------------------------------------- */

        // Assignment operator
        template<typename otherType>
        vecType& operator=(const Vector<3, otherType>& otherVec);

        /* -------------------------------------------- */
        /*  getters                                     */
        /* -------------------------------------------- */

        const componentType& operator[](size_t pos) const;

        componentType& operator[](size_t pos);

        /* -------------------------------------------- */
        /*  Maths                                       */
        /* -------------------------------------------- */

        // Add Vector
        template<typename otherType>
        vecType operator+(const Vector<3, otherType>& rhs) const;

        // Add Scalar
        template<typename otherType>
        vecType operator+(otherType rhs) const;

        // Add Vector In-Place
        template<typename otherType>
        vecType& operator+=(const Vector<3, otherType>& rhs);

        // Add Scalar In-Place
        template<typename otherType>
        vecType& operator+=(otherType rhs);

        /* -------------------------------------------- */

        // Minus Vector
        template<typename otherType>
        vecType operator-(const Vector<3, otherType>& rhs) const;

        // Minus Scalar
        template<typename otherType>
        vecType operator-(otherType rhs) const;

        // Minus Vector In-Place
        template<typename otherType>
        vecType& operator-=(const Vector<3, otherType>& rhs);

        // Minus Scalar In-Place
        template<typename otherType>
        vecType& operator-=(otherType rhs);

        /* -------------------------------------------- */

        //   Negation
        vecType operator-();

        /* -------------------------------------------- */

        // Multiply by Components
        template<typename otherType>
        vecType operator*(const Vector<3, otherType>& rhs) const;

        // Multiply by Scalar
        template<typename otherType>
        vecType operator*(otherType rhs) const;

        // Multiply by Components In-Place
        template<typename otherType>
        vecType& operator*=(const Vector<3, otherType>& rhs);

        // Multiply by Scalar In-Place
        template<typename otherType>
        vecType& operator*=(otherType rhs);

        /* -------------------------------------------- */

        // Divide by Components
        template<typename otherType>
        vecType operator/(const Vector<3, otherType>& rhs) const;

        // Divide by Scalar
        template<typename otherType>
        vecType operator/(otherType rhs) const;

        // Divide by Components In-Place
        template<typename otherType>
        vecType& operator/=(const Vector<3, otherType>& rhs);

        // Divide by Scalar In-Place
        template<typename otherType>
        vecType& operator/=(otherType rhs);

        /* -------------------------------------------- */

        /**
         * Get the dot product of this vector and a given vector
         * @tparam otherType The type of the other vector
         * @param otherVec The other vector
         * @return the dot product of this vector and the given vector
         */
        template<typename otherType>
        componentType dotProduct(Vector<3, otherType> otherVec) const;

        /* -------------------------------------------- */

        /**
         * Get the dot product of this vector and a given vector
         * @tparam otherType The type of the other vector
         * @param otherVec The other vector
         * @return the dot product of this vector and the given vector
         */
        template<typename otherType>
        vecType crossProduct(Vector<3, otherType> otherVec) const;

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

        /**
         * Get if this vector is normalised (has a length of one)
         * @return true if normalised
         */
        bool isNormalised(componentType tolerance = static_cast<componentType>(numbers::normalisedTolerance)) const;

        /* -------------------------------------------- */

        /**
         * Get a Vec3 that is perpendicular to this one and the given axis
         *
         * @param axis The axis to use to determine the direction of the perpendicular vector
         * @return a Vec3 that is perpendicular to this one
         */
        vecType perpendicular(vecType axis) const;

        /* -------------------------------------------- */
        /*  Comparison                                  */
        /* -------------------------------------------- */

        // Equals
        template<typename otherType>
        bool operator==(const Vector<3, otherType>& rhs) const;

        /**
         * Check if this vector is equal to another within a small tolerances
         * @tparam otherType The type of the other vector
         * @param rhs The other vector to compare to
         * @param tolerance How close the two vectors needs to be to be regarded as equal
         * @return true if equal within a tolerance
         */
        template<typename otherType>
        bool equal(const Vector<3, otherType>& rhs, componentType tolerance = static_cast<componentType>(numbers::tinyNumber)) const;

        // Not Equal
        template<typename otherType>
        bool operator!=(const Vector<3, otherType>& rhs) const;

        /* -------------------------------------------- */

        // Less than
        template<typename otherType>
        bool operator<(const Vector<3, otherType>& rhs) const;

        // Greater Than
        template<typename otherType>
        bool operator>(const Vector<3, otherType>& rhs) const;

        // Less than or equal
        template<typename otherType>
        bool operator<=(const Vector<3, otherType>& rhs) const;

        // Greater than or equal
        template<typename otherType>
        bool operator>=(const Vector<3, otherType>& rhs) const;

        /* -------------------------------------------- */

        // UFO Operator
        template<typename otherType>
        std::strong_ordering operator<=>(const Vector<3, otherType>& rhs) const;
    };

#include "source/vec3.inl"
}