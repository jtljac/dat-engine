#pragma once

#include "vec-forward.h"

#include <compare>
#include <cassert>

#include <util/type-traits.h>
#include <maths/numbers.h>
#include <maths/common-maths.h>

template<typename componentType>
/**
 * A struct representing a single component vector
 * @tparam componentType The type of the components of the vector
 */
struct DatEngine::DatMaths::Vector<1, componentType> {
    typedef Vector<1, componentType> vecType;

    /** The components of the vector */
    componentType x;

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
    Vector(componentType x) : x(x) {}

    /* -------------------------------------------- */

    operator componentType();

    /* -------------------------------------------- */

    // Copy
    // Vec1
    /**
     * Initialise using another Vec1
     * @tparam otherType The type of the Vec1
     * @param otherVec The other Vec1 to source the values of the X component from
     */
    template<typename otherType>
    explicit Vector(const Vector<1, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)) {}

    // Vec2
    /**
     * Initialise using a Vec2
     * @tparam otherType The type of the Vec2
     * @param otherVec The other Vec2 to source the values of the X component from (y is discarded)
     */
    template<typename otherType>
    explicit Vector(const Vector<2, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)) {}

    // Vec3
    /**
     * Initialise using the values from a Vec3
     * @tparam otherType The type of the Vec3
     * @param otherVec The Vec3 to source the values of the X component from (y and z are discarded)
     */
    template<typename otherType>
    explicit Vector(const Vector<3, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)) {}

    // Vec4
    /**
     * Initialise using the values from a Vec4
     * @tparam otherType The type of the Vec4
     * @param otherVec The Vec4 to source the values of the X component from (y, z and w are discarded)
     */
    template<typename otherType>
    explicit Vector(const Vector<4, otherType>& otherVec) : x(static_cast<componentType>(otherVec.x)) {}

    // Vecn
    /**
     * Initialise using the values from a Vecn
     * @tparam otherType The type of the Vecn
     * @param otherVec The Vecn to source the values of the X component from
     */
    template<int otherSize, typename otherType>
        requires(otherSize > 4)
    explicit Vector(const Vector<otherSize, otherType>& otherVec) : x(static_cast<componentType>(otherVec[0])) {}

    /* -------------------------------------------- */

    // Assignment operator
    template<typename otherType>
    vecType& operator=(const Vector<1, otherType>& otherVec);

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
    vecType operator+(const Vector<1, otherType>& rhs) const;

    // Add Scalar
    template<typename otherType>
    vecType operator+(otherType rhs) const;

    // Add Vector In-Place
    template<typename otherType>
    vecType& operator+=(const Vector<1, otherType>& rhs);

    // Add Scalar In-Place
    template<typename otherType>
    vecType& operator+=(otherType rhs);

    /* -------------------------------------------- */

    // Minus Vector
    template<typename otherType>
    vecType operator-(const Vector<1, otherType>& rhs) const;

    // Minus Scalar
    template<typename otherType>
    vecType operator-(otherType rhs) const;

    // Minus Vector In-Place
    template<typename otherType>
    vecType& operator-=(const Vector<1, otherType>& rhs);

    // Minus Scalar In-Place
    template<typename otherType>
    vecType& operator-=(otherType rhs);

    /* -------------------------------------------- */

    //   Negation
    vecType operator-();

    /* -------------------------------------------- */

    // Multiply by Components
    template<typename otherType>
    vecType operator*(const Vector<1, otherType>& rhs) const;

    // Multiply by Scalar
    template<typename otherType>
    vecType operator*(otherType rhs) const;

    // Multiply by Components In-Place
    template<typename otherType>
    vecType& operator*=(const Vector<1, otherType>& rhs);

    // Multiply by Scalar In-Place
    template<typename otherType>
    vecType& operator*=(otherType rhs);

    /* -------------------------------------------- */

    // Divide by Components
    template<typename otherType>
    vecType operator/(const Vector<1, otherType>& rhs) const;

    // Divide by Scalar
    template<typename otherType>
    vecType operator/(otherType rhs) const;

    // Divide by Components In-Place
    template<typename otherType>
    vecType& operator/=(const Vector<1, otherType>& rhs);

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
    componentType dotProduct(Vector<1, otherType> otherVec) const;

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
    /*  Comparison                                  */
    /* -------------------------------------------- */

    // Equals
    template<typename otherType>
    bool operator==(const Vector<1, otherType>& rhs) const;

    /**
     * Check if this vector is equal to another within a small tolerances
     * @tparam otherType The type of the other vector
     * @param rhs The other vector to compare to
     * @param tolerance How close the two vectors needs to be to be regarded as equal
     * @return true if equal within a tolerance
     */
    template<typename otherType>
    bool equal(const Vector<1, otherType>& rhs,
               componentType tolerance = static_cast<componentType>(numbers::tinyNumber)) const;

    // Not Equal
    template<typename otherType>
    bool operator!=(const Vector<1, otherType>& rhs) const;
    ;

    /* -------------------------------------------- */

    // Less than
    template<typename otherType>
    bool operator<(const Vector<1, otherType>& rhs) const;

    // Greater Than
    template<typename otherType>
    bool operator>(const Vector<1, otherType>& rhs) const;

    // Less than or equal
    template<typename otherType>
    bool operator<=(const Vector<1, otherType>& rhs) const;

    // Greater than or equal
    template<typename otherType>
    bool operator>=(const Vector<1, otherType>& rhs) const;

    /* -------------------------------------------- */

    // UFO Operator
    template<typename otherType>
    std::strong_ordering operator<=>(const Vector<1, otherType>& rhs) const;
};

#include "source/vec1.inl"