#pragma once

#include "VecForward.h"

#include <compare>

#include <maths/CommonMaths.h> // Used by inl
#include <maths/Constants.h>

template<typename TComponent>
/**
 * A struct representing a 3 component vector
 * @tparam TComponent The type of the components of the vector
 */
struct DatEngine::DatMaths::Vector<3, TComponent> {

    /** The components of the vector */
    TComponent x, y, z;

    /* -------------------------------------------- */
    /*  Statics                                     */
    /* -------------------------------------------- */

    /**
     * A unit vector that faces north (0, 0, 1)
     */
    const static Vector NORTH;

    /**
     * A unit vector that faces east (1, 0, 0)
     */
    const static Vector EAST;

    /**
     * A unit vector that faces south (0, 0, -1)
     */
    const static Vector SOUTH;

    /**
     * A unit vector that faces west (-1, 0, 0)
     */
    const static Vector WEST;

    /**
     * A unit vector that faces up (0, 1, 0)
     */
    const static Vector UP;

    /**
     * A unit vector that faces down (0, -1, 0)
     */
    const static Vector DOWN;

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
    explicit Vector(TComponent scalar) : x(scalar), y(scalar), z(scalar) {}

    /**
     * Initialises each component to their given value
     * @param x The value to initialise the x component to
     * @param y The value to initialise the y component to
     * @param z The value to initialise the z component to
     */
    Vector(TComponent x, TComponent y, TComponent z) : x(x), y(y), z(z) {}

    /* -------------------------------------------- */

    // Copy
    // Vec1
    /**
     * Initialise using just a Vec1, the Y, Z and W components will be initialised to 0
     * @tparam TOther The type of the Vec1
     * @param otherVec The Vec1 to source the values of the X component from
     */
    template<typename TOther>
    explicit Vector(const Vector<1, TOther>& otherVec) : x(static_cast<TComponent>(otherVec.x)), y(0), z(0) {}

    /**
     * Initialise using a Vec1, a Y component, and a Z component
     * @tparam TOther The type of the Vec1
     * @param otherVec The Vec1 to source the value of the X component from
     * @param y The value of the Y component
     * @param z The value of the Z component
     */
    template<typename TOther>
    Vector(const Vector<1, TOther>& otherVec, TComponent y, TComponent z) :
        x(static_cast<TComponent>(otherVec.x)), y(y), z(z) {}

    // Vec2
    /**
     * Initialise using just a Vec2, Z will be initialised to 0
     * @tparam TOther The type of the Vec2
     * @param otherVec The Vec2 to source the values of the X and Y components from
     */
    template<typename TOther>
    explicit Vector(const Vector<2, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)), z(0) {}

    /**
     * Initialise using a Vec2 and a z component
     * @tparam TOther The type of the Vec2
     * @param otherVec The Vec2 to source the values of the X and Y components from
     * @param z The value of the z component
     */
    template<typename TOther>
    Vector(const Vector<2, TOther>& otherVec, TComponent z) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)), z(z) {}

    // Vec3
    /**
     * Initialise using the values from another Vec3
     * @tparam TOther The type of the other Vec3
     * @param otherVec The other Vec3 to source the values of the X, Y, and Z components from
     */
    template<typename TOther>
    explicit Vector(const Vector<3, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)),
        z(static_cast<TComponent>(otherVec.z)) {}

    // Vec4
    /**
     * Initialise using the values from a Vec4
     * @tparam TOther The type of the Vec4
     * @param otherVec The Vec4 to source the values of the X,Y, and Z components from (w is discarded)
     */
    template<typename TOther>
    explicit Vector(const Vector<4, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)),
        z(static_cast<TComponent>(otherVec.z)) {}

    // Vecn
    /**
     * Initialise using the values from a Vecn
     * @tparam TOther The type of the Vecn
     * @param otherVec The Vecn to source the values of the X and Y components from
     */
    template<int otherSize, typename TOther>
        requires(otherSize > 4)
    explicit Vector(const Vector<otherSize, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec[0])), y(static_cast<TComponent>(otherVec[1])),
        z(static_cast<TComponent>(otherVec[2])) {}

    /* -------------------------------------------- */

    // Assignment operator
    template<typename TOther>
    Vector& operator=(const Vector<3, TOther>& otherVec);

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
    Vector operator+(const Vector<3, TOther>& rhs) const;

    // Add Scalar
    template<typename TOther>
    Vector operator+(TOther rhs) const;

    // Add Vector In-Place
    template<typename TOther>
    Vector& operator+=(const Vector<3, TOther>& rhs);

    // Add Scalar In-Place
    template<typename TOther>
    Vector& operator+=(TOther rhs);

    /* -------------------------------------------- */

    // Minus Vector
    template<typename TOther>
    Vector operator-(const Vector<3, TOther>& rhs) const;

    // Minus Scalar
    template<typename TOther>
    Vector operator-(TOther rhs) const;

    // Minus Vector In-Place
    template<typename TOther>
    Vector& operator-=(const Vector<3, TOther>& rhs);

    // Minus Scalar In-Place
    template<typename TOther>
    Vector& operator-=(TOther rhs);

    /* -------------------------------------------- */

    //   Negation
    Vector operator-();

    /* -------------------------------------------- */

    // Multiply by Components
    template<typename TOther>
    Vector operator*(const Vector<3, TOther>& rhs) const;

    // Multiply by Scalar
    template<typename TOther>
    Vector operator*(TOther rhs) const;

    // Multiply by Components In-Place
    template<typename TOther>
    Vector& operator*=(const Vector<3, TOther>& rhs);

    // Multiply by Scalar In-Place
    template<typename TOther>
    Vector& operator*=(TOther rhs);

    /* -------------------------------------------- */

    // Divide by Components
    template<typename TOther>
    Vector operator/(const Vector<3, TOther>& rhs) const;

    // Divide by Scalar
    template<typename TOther>
    Vector operator/(TOther rhs) const;

    // Divide by Components In-Place
    template<typename TOther>
    Vector& operator/=(const Vector<3, TOther>& rhs);

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
    TComponent dotProduct(Vector<3, TOther> otherVec) const;

    /* -------------------------------------------- */

    /**
     * Get the dot product of this vector and a given vector
     * @tparam TOther The type of the other vector
     * @param otherVec The other vector
     * @return the dot product of this vector and the given vector
     */
    template<typename TOther>
    Vector crossProduct(Vector<3, TOther> otherVec) const;

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
     * Get a Vec3 that is perpendicular to this one and the given axis
     *
     * @param axis The axis to use to determine the direction of the perpendicular vector
     * @return a Vec3 that is perpendicular to this one
     */
    Vector perpendicular(Vector axis) const;

    /* -------------------------------------------- */
    /*  Comparison                                  */
    /* -------------------------------------------- */

    // Equals
    template<typename TOther>
    bool operator==(const Vector<3, TOther>& rhs) const;

    /**
     * Check if this vector is equal to another within a small tolerances
     * @tparam TOther The type of the other vector
     * @param rhs The other vector to compare to
     * @param tolerance How close the two vectors needs to be to be regarded as equal
     * @return true if equal within a tolerance
     */
    template<typename TOther>
    bool
    equal(const Vector<3, TOther>& rhs, TComponent tolerance = static_cast<TComponent>(constants::tinyNumber)) const;

    // Not Equal
    template<typename TOther>
    bool operator!=(const Vector<3, TOther>& rhs) const;

    /* -------------------------------------------- */

    // Less than
    template<typename TOther>
    bool operator<(const Vector<3, TOther>& rhs) const;

    // Greater Than
    template<typename TOther>
    bool operator>(const Vector<3, TOther>& rhs) const;

    // Less than or equal
    template<typename TOther>
    bool operator<=(const Vector<3, TOther>& rhs) const;

    // Greater than or equal
    template<typename TOther>
    bool operator>=(const Vector<3, TOther>& rhs) const;

    /* -------------------------------------------- */

    // UFO Operator
    template<typename TOther>
    std::strong_ordering operator<=>(const Vector<3, TOther>& rhs) const;
};

#include "Vec3.inl"
