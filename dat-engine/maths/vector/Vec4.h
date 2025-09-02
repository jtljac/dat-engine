#pragma once

#include "VecForward.h"

#include <compare>

#include <maths/CommonMaths.h> // Used by inl
#include <maths/Constants.h>

template<typename TComponent>
/**
 * A struct representing a 4 component vector
 * @tparam TComponent The type of the components of the vector
 */
struct DatEngine::DatMaths::Vector<4, TComponent> {

    /** The components of the vector */
    TComponent x, y, z, w;

    /* -------------------------------------------- */
    /*  Initialisation                              */
    /* -------------------------------------------- */

    /**
     * Initialises all components to 0
     */
    Vector() : x(0), y(0), z(0), w(0) {}

    /**
     * Initialises all components to the same value
     * @param scalar The value to initialise the components to
     */
    explicit Vector(TComponent scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

    /**
     * Initialises each component to their given value
     * @param x The value to initialise the x component to
     * @param y The value to initialise the y component to
     * @param z The value to initialise the z component to
     * @param w The value to initialise the w component to
     */
    Vector(TComponent x, TComponent y, TComponent z, TComponent w) : x(x), y(y), z(z), w(w) {}

    /* -------------------------------------------- */

    // Copy
    // Vec1
    /**
     * Initialise using just a Vec1, the Y, Z and W components will be initialised to 0
     * @tparam TOther The type of the Vec1
     * @param otherVec The Vec1 to source the values of the X component from
     */
    template<typename TOther>
    explicit Vector(const Vector<1, TOther>& otherVec) : x(static_cast<TComponent>(otherVec.x)), y(0), z(0), w(0) {}

    /**
     * Initialise using a Vec1, a Y component, a Z component and a W component
     * @tparam TOther The type of the Vec1
     * @param otherVec The Vec1 to source the value of the X component from
     * @param y The value of the Y component
     * @param z The value of the Z component
     * @param w The value of the W component
     */
    template<typename TOther>
    Vector(const Vector<1, TOther>& otherVec, TComponent y, TComponent z, TComponent w) :
        x(static_cast<TComponent>(otherVec.x)), y(y), z(z), w(w) {}

    // Vec2
    /**
     * Initialise using just a Vec2, the Z and W components will be initialised to 0
     * @tparam TOther The type of the Vec2
     * @param otherVec The Vec2 to source the values of the X and Y components from
     */
    template<typename TOther>
    explicit Vector(const Vector<2, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)), z(0), w(0) {}

    /**
     * Initialise using a Vec2, a Z component and a W component
     * @tparam TOther The type of the Vec2
     * @param otherVec The Vec2 to source the values of the X and Y components from
     * @param z The value of the Z component
     * @param w The value of the W component
     */
    template<typename TOther>
    Vector(const Vector<2, TOther>& otherVec, TComponent z, TComponent w) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)), z(z), w(w) {}

    /**
     * Initialise using 2 Vec2
     * @tparam TOther The type of the Vec2
     * @param otherVec The Vec2 to source the values of the X and Y components from
     * @param otherVec2 The Vec2 to source the values of the Z and W components from
     */
    template<typename TOther>
    Vector(const Vector<2, TOther>& otherVec, const Vector<2, TOther>& otherVec2) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)),
        z(static_cast<TComponent>(otherVec2.x)), w(static_cast<TComponent>(otherVec2.y)) {}

    // Vec3
    /**
     * Initialise using just a Vec3, The W component will be initialised to 0
     * @tparam TOther The type of the Vec3
     * @param otherVec The Vec3 to source the values of the X, Y, and Z components from
     */
    template<typename TOther>
    explicit Vector(const Vector<3, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)),
        z(static_cast<TComponent>(otherVec.z)), w(0) {}
    /**
     * Initialise using the values from a Vec3
     * @tparam TOther The type of the Vec3
     * @param otherVec The Vec3 to source the values of the X, Y, and Z components from
     * @param w The value of the W component
     */
    template<typename TOther>
    Vector(const Vector<3, TOther>& otherVec, TComponent w) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)),
        z(static_cast<TComponent>(otherVec.z)), w(w) {}

    // Vec4
    /**
     * Initialise using the values from another Vec4
     * @tparam TOther The type of the other Vec4
     * @param otherVec The other Vec4 to source the values of the X, Y, Z and W components from
     */
    template<typename TOther>
    explicit Vector(const Vector<4, TOther>& otherVec) :
        x(static_cast<TComponent>(otherVec.x)), y(static_cast<TComponent>(otherVec.y)),
        z(static_cast<TComponent>(otherVec.z)), w(static_cast<TComponent>(otherVec.w)) {}

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
        z(static_cast<TComponent>(otherVec[2])), w(static_cast<TComponent>(otherVec[3])) {}

    /* -------------------------------------------- */

    // Assignment operator
    template<typename TOther>
    Vector& operator=(const Vector<4, TOther>& otherVec);

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
    Vector operator+(const Vector<4, TOther>& rhs) const;

    // Add Scalar
    template<typename TOther>
    Vector operator+(TOther rhs) const;

    // Add Vector In-Place
    template<typename TOther>
    Vector& operator+=(const Vector<4, TOther>& rhs);

    // Add Scalar In-Place
    template<typename TOther>
    Vector& operator+=(TOther rhs);

    /* -------------------------------------------- */

    // Minus Vector
    template<typename TOther>
    Vector operator-(const Vector<4, TOther>& rhs) const;

    // Minus Scalar
    template<typename TOther>
    Vector operator-(TOther rhs) const;

    // Minus Vector In-Place
    template<typename TOther>
    Vector& operator-=(const Vector<4, TOther>& rhs);

    // Minus Scalar In-Place
    template<typename TOther>
    Vector& operator-=(TOther rhs);

    /* -------------------------------------------- */

    //   Negation
    Vector operator-();

    /* -------------------------------------------- */

    // Multiply by Components
    template<typename TOther>
    Vector operator*(const Vector<4, TOther>& rhs) const;

    // Multiply by Scalar
    template<typename TOther>
    Vector operator*(TOther rhs) const;

    // Multiply by Components In-Place
    template<typename TOther>
    Vector& operator*=(const Vector<4, TOther>& rhs);

    // Multiply by Scalar In-Place
    template<typename TOther>
    Vector& operator*=(TOther rhs);

    /* -------------------------------------------- */

    // Divide by Components
    template<typename TOther>
    Vector operator/(const Vector<4, TOther>& rhs) const;

    // Divide by Scalar
    template<typename TOther>
    Vector operator/(TOther rhs) const;

    // Divide by Components In-Place
    template<typename TOther>
    Vector& operator/=(const Vector<4, TOther>& rhs);

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
    TComponent dotProduct(Vector<4, TOther> otherVec) const;

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
    /*  Comparison                                  */
    /* -------------------------------------------- */

    // Equals
    template<typename TOther>
    bool operator==(const Vector<4, TOther>& rhs) const;

    /**
     * Check if this vector is equal to another within a small tolerances
     * @tparam TOther The type of the other vector
     * @param rhs The other vector to compare to
     * @param tolerance How close the two vectors needs to be to be regarded as equal
     * @return true if equal within a tolerance
     */
    template<typename TOther>
    bool
    equal(const Vector<4, TOther>& rhs, TComponent tolerance = static_cast<TComponent>(constants::tinyNumber)) const;

    // Not Equal
    template<typename TOther>
    bool operator!=(const Vector<4, TOther>& rhs) const;

    /* -------------------------------------------- */

    // Less than
    template<typename TOther>
    bool operator<(const Vector<4, TOther>& rhs) const;

    // Greater Than
    template<typename TOther>
    bool operator>(const Vector<4, TOther>& rhs) const;

    // Less than or equal
    template<typename TOther>
    bool operator<=(const Vector<4, TOther>& rhs) const;

    // Greater than or equal
    template<typename TOther>
    bool operator>=(const Vector<4, TOther>& rhs) const;

    /* -------------------------------------------- */

    // UFO Operator
    template<typename TOther>
    std::strong_ordering operator<=>(const Vector<4, TOther>& rhs) const;
};

#include "Vec4.inl"
