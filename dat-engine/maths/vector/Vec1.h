#pragma once

#include "VecForward.h"

#include <cassert>
#include <compare>

#include <maths/CommonMaths.h> // Used by inl
#include <maths/Constants.h>

template<typename TComponent>
/**
 * A struct representing a single component vector
 * @tparam TComponent The type of the components of the vector
 */
struct DatEngine::DatMaths::Vector<1, TComponent> {

    /** The components of the vector */
    TComponent x;

    /* -------------------------------------------- */
    /*  Initialisation                              */
    /* -------------------------------------------- */

    /**
     * Initialises all components to 0
     */
    Vector() : x(0) {}

    /**
     * Initialises each component to their given value
     * @param x The value to initialise the x component to
     */
    Vector(TComponent x) : x(x) {}

    /* -------------------------------------------- */

    operator TComponent();

    /* -------------------------------------------- */

    // Copy
    // Vec1
    /**
     * Initialise using another Vec1
     * @tparam TOther The type of the Vec1
     * @param otherVec The other Vec1 to source the values of the X component from
     */
    template<typename TOther>
    explicit Vector(const Vector<1, TOther>& otherVec) : x(static_cast<TComponent>(otherVec.x)) {}

    // Vec2
    /**
     * Initialise using a Vec2
     * @tparam TOther The type of the Vec2
     * @param otherVec The other Vec2 to source the values of the X component from (y is discarded)
     */
    template<typename TOther>
    explicit Vector(const Vector<2, TOther>& otherVec) : x(static_cast<TComponent>(otherVec.x)) {}

    // Vec3
    /**
     * Initialise using the values from a Vec3
     * @tparam TOther The type of the Vec3
     * @param otherVec The Vec3 to source the values of the X component from (y and z are discarded)
     */
    template<typename TOther>
    explicit Vector(const Vector<3, TOther>& otherVec) : x(static_cast<TComponent>(otherVec.x)) {}

    // Vec4
    /**
     * Initialise using the values from a Vec4
     * @tparam TOther The type of the Vec4
     * @param otherVec The Vec4 to source the values of the X component from (y, z and w are discarded)
     */
    template<typename TOther>
    explicit Vector(const Vector<4, TOther>& otherVec) : x(static_cast<TComponent>(otherVec.x)) {}

    // Vecn
    /**
     * Initialise using the values from a Vecn
     * @tparam TOther The type of the Vecn
     * @param otherVec The Vecn to source the values of the X component from
     */
    template<int otherSize, typename TOther>
        requires(otherSize > 4)
    explicit Vector(const Vector<otherSize, TOther>& otherVec) : x(static_cast<TComponent>(otherVec[0])) {}

    /* -------------------------------------------- */

    // Assignment operator
    template<typename TOther>
    Vector& operator=(const Vector<1, TOther>& otherVec);

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
    Vector operator+(const Vector<1, TOther>& rhs) const;

    // Add Scalar
    template<typename TOther>
    Vector operator+(TOther rhs) const;

    // Add Vector In-Place
    template<typename TOther>
    Vector& operator+=(const Vector<1, TOther>& rhs);

    // Add Scalar In-Place
    template<typename TOther>
    Vector& operator+=(TOther rhs);

    /* -------------------------------------------- */

    // Minus Vector
    template<typename TOther>
    Vector operator-(const Vector<1, TOther>& rhs) const;

    // Minus Scalar
    template<typename TOther>
    Vector operator-(TOther rhs) const;

    // Minus Vector In-Place
    template<typename TOther>
    Vector& operator-=(const Vector<1, TOther>& rhs);

    // Minus Scalar In-Place
    template<typename TOther>
    Vector& operator-=(TOther rhs);

    /* -------------------------------------------- */

    //   Negation
    Vector operator-();

    /* -------------------------------------------- */

    // Multiply by Components
    template<typename TOther>
    Vector operator*(const Vector<1, TOther>& rhs) const;

    // Multiply by Scalar
    template<typename TOther>
    Vector operator*(TOther rhs) const;

    // Multiply by Components In-Place
    template<typename TOther>
    Vector& operator*=(const Vector<1, TOther>& rhs);

    // Multiply by Scalar In-Place
    template<typename TOther>
    Vector& operator*=(TOther rhs);

    /* -------------------------------------------- */

    // Divide by Components
    template<typename TOther>
    Vector operator/(const Vector<1, TOther>& rhs) const;

    // Divide by Scalar
    template<typename TOther>
    Vector operator/(TOther rhs) const;

    // Divide by Components In-Place
    template<typename TOther>
    Vector& operator/=(const Vector<1, TOther>& rhs);

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
    TComponent dotProduct(Vector<1, TOther> otherVec) const;

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
    bool operator==(const Vector<1, TOther>& rhs) const;

    /**
     * Check if this vector is equal to another within a small tolerances
     * @tparam TOther The type of the other vector
     * @param rhs The other vector to compare to
     * @param tolerance How close the two vectors needs to be regarded as equal
     * @return true if equal within a tolerance
     */
    template<typename TOther>
    bool
    equal(const Vector<1, TOther>& rhs, TComponent tolerance = static_cast<TComponent>(constants::tinyNumber)) const;

    // Not Equal
    template<typename TOther>
    bool operator!=(const Vector<1, TOther>& rhs) const;
    ;

    /* -------------------------------------------- */

    // Less than
    template<typename TOther>
    bool operator<(const Vector<1, TOther>& rhs) const;

    // Greater Than
    template<typename TOther>
    bool operator>(const Vector<1, TOther>& rhs) const;

    // Less than or equal
    template<typename TOther>
    bool operator<=(const Vector<1, TOther>& rhs) const;

    // Greater than or equal
    template<typename TOther>
    bool operator>=(const Vector<1, TOther>& rhs) const;

    /* -------------------------------------------- */

    // UFO Operator
    template<typename TOther>
    std::strong_ordering operator<=>(const Vector<1, TOther>& rhs) const;
};

#include "Vec1.inl"
