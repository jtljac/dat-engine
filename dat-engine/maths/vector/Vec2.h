#pragma once

#include "VecForward.h"

#include <cassert>
#include <compare>

#include <maths/CommonMaths.h> // Used by inl
#include <maths/Constants.h>

// TODO: Create unit tests for each function
template<typename TComponent>
/**
 * A struct representing a 2 component vector
 * @tparam TComponent The type of the components of the vector
 */
struct DatEngine::DatMaths::Vector<2, TComponent> {

    /** The components of the vector */
    TComponent x, y;

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
    explicit Vector(TComponent scalar) : x(scalar), y(scalar) {}

    /**
     * Initialises each component to their given value
     * @param x The value to initialise the x component to
     * @param y The value to initialise the y component to
     */
    Vector(TComponent x, TComponent y) : x(x), y(y) {}

    /* -------------------------------------------- */

    // Copy
    // Vec1
    /**
     * Initialise using just a Vec1, the Y, and Z components will be initialised to 0
     * @tparam TOther The type of the Vec1
     * @param otherVec The Vec1 to source the values of the X component from
     */
    template<typename TOther>
    explicit Vector(const Vector<1, TOther>& otherVec) : x(static_cast<TComponent>(otherVec.x)), y(0) {}

    /**
     * Initialise using a Vec1, and a Y component
     * @tparam TOther The type of the Vec1
     * @param otherVec The Vec1 to source the value of the X component from
     * @param y The value of the Y component
     */
    template<typename TOther>
    Vector(const Vector<1, TOther>& otherVec, TComponent y) : x(static_cast<TComponent>(otherVec.x)), y(y) {}

    // Vec2
    /**
     * Initialise using another Vec2
     * @tparam TOther The type of the Vec2
     * @param otherVec The other Vec2 to source the values of the X and Y components from
     */
    template<typename TOther>
    explicit Vector(const Vector<2, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)) {}

    // Vec3
    /**
     * Initialise using the values from a Vec3
     * @tparam TOther The type of the Vec3
     * @param otherVec The Vec3 to source the values of the X and Y components from (z is discarded)
     */
    template<typename TOther>
    explicit Vector(const Vector<3, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)) {}

    // Vec4
    /**
     * Initialise using the values from a Vec4
     * @tparam TOther The type of the Vec4
     * @param otherVec The Vec4 to source the values of the X and Y components from (z and w is discarded)
     */
    template<typename TOther>
    explicit Vector(const Vector<4, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)) {}

    // Vecn
    /**
     * Initialise using the values from a Vecn
     * @tparam TOther The type of the Vecn
     * @param otherVec The Vecn to source the values of the X and Y components from
     */
    template<int otherSize, typename TOther>
        requires(otherSize > 4)
    explicit Vector(const Vector<otherSize, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec[0])), y(static_cast<TComponent>(otherVec[1])) {}

    /* -------------------------------------------- */

    // Assignment operator
    template<typename TOther>
    Vector& operator=(const Vector<2, TOther>& otherVec);

    /* -------------------------------------------- */
    /*  getters                                     */
    /* -------------------------------------------- */

    const TComponent& operator[](size_t pos) const;

    TComponent& operator[](size_t pos);

    /* -------------------------------------------- */
    /*  Maths                                       */
    /* -------------------------------------------- */

    // Add Vector
    template<typename TOther>
    Vector operator+(const Vector<2, TOther>& rhs) const;

    // Add Scalar
    template<typename TOther>
    Vector operator+(TOther rhs) const;

    // Add Vector In-Place
    template<typename TOther>
    Vector& operator+=(const Vector<2, TOther>& rhs);

    // Add Scalar In-Place
    template<typename TOther>
    Vector& operator+=(TOther rhs);

    /* -------------------------------------------- */

    // Minus Vector
    template<typename TOther>
    Vector operator-(const Vector<2, TOther>& rhs) const;

    // Minus Scalar
    template<typename TOther>
    Vector operator-(TOther rhs) const;

    // Minus Vector In-Place
    template<typename TOther>
    Vector& operator-=(const Vector<2, TOther>& rhs);

    // Minus Scalar In-Place
    template<typename TOther>
    Vector& operator-=(TOther rhs);

    /* -------------------------------------------- */

    //   Negation
    Vector operator-();

    /* -------------------------------------------- */

    // Multiply by Components
    template<typename TOther>
    Vector operator*(const Vector<2, TOther>& rhs) const;

    // Multiply by Scalar
    template<typename TOther>
    Vector operator*(TOther rhs) const;

    // Multiply by Components In-Place
    template<typename TOther>
    Vector& operator*=(const Vector<2, TOther>& rhs);

    // Multiply by Scalar In-Place
    template<typename TOther>
    Vector& operator*=(TOther rhs);

    /* -------------------------------------------- */

    // Divide by Components
    template<typename TOther>
    Vector operator/(const Vector<2, TOther>& rhs) const;

    // Divide by Scalar
    template<typename TOther>
    Vector operator/(TOther rhs) const;

    // Divide by Components In-Place
    template<typename TOther>
    Vector& operator/=(const Vector<2, TOther>& rhs);

    // Divide by Scalar In-Place
    template<typename TOther>
    Vector& operator/=(TOther rhs);

    /* -------------------------------------------- */

    /**
     * Get the dot product of this vector and a given vector
     * @tparam TOther The type of the other vector
     * @param otherVec The other vector
     * @return the dot product of this vector and the given vector
     */
    template<typename TOther>
    TComponent dotProduct(Vector<2, TOther> otherVec) const;

    /* -------------------------------------------- */

    /**
     * Get the magnitude of the vector
     * @return the magnitude of the vector
     */
    TComponent length() const;

    /**
     * Get the magnitude squared of the vector
     * <br>
     * This saves an expensive sqrt operation so is preferable for some comparisons
     * @return The magnitude squared of the vector
     */
    TComponent lengthSquared() const;

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
    bool isNormalised(TComponent tolerance = static_cast<TComponent>(constants::normalisedTolerance)) const;

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
    template<typename TOther>
    bool operator==(const Vector<2, TOther>& rhs) const;

    /**
     * Check if this vector is equal to another within a small tolerances
     * @tparam TOther The type of the other vector
     * @param rhs The other vector to compare to
     * @param tolerance How close the two vectors needs to be to be regarded as equal
     * @return true if equal within a tolerance
     */
    template<typename TOther>
    bool
    equal(const Vector<2, TOther>& rhs, TComponent tolerance = static_cast<TComponent>(constants::tinyNumber)) const;

    // Not Equal
    template<typename TOther>
    bool operator!=(const Vector<2, TOther>& rhs) const;
    ;

    /* -------------------------------------------- */

    // Less than
    template<typename TOther>
    bool operator<(const Vector<2, TOther>& rhs) const;

    // Greater Than
    template<typename TOther>
    bool operator>(const Vector<2, TOther>& rhs) const;

    // Less than or equal
    template<typename TOther>
    bool operator<=(const Vector<2, TOther>& rhs) const;

    // Greater than or equal
    template<typename TOther>
    bool operator>=(const Vector<2, TOther>& rhs) const;

    /* -------------------------------------------- */

    // UFO Operator
    template<typename TOther>
    std::strong_ordering operator<=>(const Vector<2, TOther>& rhs) const;
};

#include "Vec2.inl"
