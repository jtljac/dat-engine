//
// Created by jacob on 04/07/23.
//

#pragma once

#include "vec-forward.h"

#include <compare>
#include <cassert>

#include <maths/common-maths.h>
#include <maths/numbers.h>

// TODO: Create unit tests for each function
template<typename componentType>
/**
 * A struct representing a 2 component vector
 * @tparam componentType The type of the components of the vector
 */
struct DatEngine::DatMaths::Vector<2, componentType> {

    /** The components of the vector */
    componentType x, y;

    /* -------------------------------------------- */
    /*  Statics                                     */
    /* -------------------------------------------- */

    /**
     * A unit vector that faces up (0, -1)
     */
    const static Vector UP;

    /**
     * A unit vector that faces right (1, 0)
     */
    const static Vector RIGHT;

    /**
     * A unit vector that faces down (0, 1)
     */
    const static Vector DOWN;

    /**
     * A unit vector that faces left (-1, 0)
     */
    const static Vector LEFT;

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
    Vector(componentType x, componentType y) : x(x), y(y) {}

    /* -------------------------------------------- */

    // Copy
    // Vec1
    /**
     * Initialise using just a Vec1, the Y, and Z components will be initialised to 0
     * @tparam otherType The type of the Vec1
     * @param otherVec The Vec1 to source the values of the X component from
     */
    template<typename otherType>
    explicit Vector(const Vector<1, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)), y(0) {}

    /**
     * Initialise using a Vec1, and a Y component
     * @tparam otherType The type of the Vec1
     * @param otherVec The Vec1 to source the value of the X component from
     * @param y The value of the Y component
     */
    template<typename otherType>
    Vector(const Vector<1, otherType>& otherVec, componentType y) : x(static_cast<componentType>(otherVec.x)), y(y) {}

    // Vec2
    /**
     * Initialise using another Vec2
     * @tparam otherType The type of the Vec2
     * @param otherVec The other Vec2 to source the values of the X and Y components from
     */
    template<typename otherType>
    explicit Vector(const Vector<2, otherType>& otherVec) :
        x(static_cast<componentType>(otherVec.x)), y(static_cast<componentType>(otherVec.y)) {}

    // Vec3
    /**
     * Initialise using the values from a Vec3
     * @tparam otherType The type of the Vec3
     * @param otherVec The Vec3 to source the values of the X and Y components from (z is discarded)
     */
    template<typename otherType>
    explicit Vector(const Vector<3, otherType>& otherVec) :
        x(static_cast<componentType>(otherVec.x)), y(static_cast<componentType>(otherVec.y)) {}

    // Vec4
    /**
     * Initialise using the values from a Vec4
     * @tparam otherType The type of the Vec4
     * @param otherVec The Vec4 to source the values of the X and Y components from (z and w is discarded)
     */
    template<typename otherType>
    explicit Vector(const Vector<4, otherType>& otherVec) :
        x(static_cast<componentType>(otherVec.x)), y(static_cast<componentType>(otherVec.y)) {}

    // Vecn
    /**
     * Initialise using the values from a Vecn
     * @tparam otherType The type of the Vecn
     * @param otherVec The Vecn to source the values of the X and Y components from
     */
    template<int otherSize, typename otherType>
        requires(otherSize > 4)
    explicit Vector(const Vector<otherSize, otherType>& otherVec) :
        x(static_cast<componentType>(otherVec[0])), y(static_cast<componentType>(otherVec[1])) {}

    /* -------------------------------------------- */

    // Assignment operator
    template<typename otherType>
    Vector& operator=(const Vector<2, otherType>& otherVec);

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
    Vector operator+(const Vector<2, otherType>& rhs) const;

    // Add Scalar
    template<typename otherType>
    Vector operator+(otherType rhs) const;

    // Add Vector In-Place
    template<typename otherType>
    Vector& operator+=(const Vector<2, otherType>& rhs);

    // Add Scalar In-Place
    template<typename otherType>
    Vector& operator+=(otherType rhs);

    /* -------------------------------------------- */

    // Minus Vector
    template<typename otherType>
    Vector operator-(const Vector<2, otherType>& rhs) const;

    // Minus Scalar
    template<typename otherType>
    Vector operator-(otherType rhs) const;

    // Minus Vector In-Place
    template<typename otherType>
    Vector& operator-=(const Vector<2, otherType>& rhs);

    // Minus Scalar In-Place
    template<typename otherType>
    Vector& operator-=(otherType rhs);

    /* -------------------------------------------- */

    //   Negation
    Vector operator-();

    /* -------------------------------------------- */

    // Multiply by Components
    template<typename otherType>
    Vector operator*(const Vector<2, otherType>& rhs) const;

    // Multiply by Scalar
    template<typename otherType>
    Vector operator*(otherType rhs) const;

    // Multiply by Components In-Place
    template<typename otherType>
    Vector& operator*=(const Vector<2, otherType>& rhs);

    // Multiply by Scalar In-Place
    template<typename otherType>
    Vector& operator*=(otherType rhs);

    /* -------------------------------------------- */

    // Divide by Components
    template<typename otherType>
    Vector operator/(const Vector<2, otherType>& rhs) const;

    // Divide by Scalar
    template<typename otherType>
    Vector operator/(otherType rhs) const;

    // Divide by Components In-Place
    template<typename otherType>
    Vector& operator/=(const Vector<2, otherType>& rhs);

    // Divide by Scalar In-Place
    template<typename otherType>
    Vector& operator/=(otherType rhs);

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
    Vector normalised() const;

    /**
     * Get if this vector is normalised (has a length of one)
     * @return true if normalised
     */
    bool isNormalised(componentType tolerance = static_cast<componentType>(numbers::normalisedTolerance)) const;

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
    Vector perpendicular(bool clockwise) const;

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
    bool equal(const Vector<2, otherType>& rhs,
               componentType tolerance = static_cast<componentType>(numbers::tinyNumber)) const;

    // Not Equal
    template<typename otherType>
    bool operator!=(const Vector<2, otherType>& rhs) const;
    ;

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