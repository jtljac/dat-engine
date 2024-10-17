#pragma once

#include "vec-forward.h"

#include <cassert>
#include <compare>

#include <cstring>
#include <maths/common-maths.h>
#include <maths/numbers.h>

namespace DatEngine {
    /**
     * A struct representing a N component vector
     * @tparam size The number of components in the vector
     * @tparam componentType The type of the components of the vector
     */
    template<int size, numeric componentType>
        requires(size > 4)
    struct DatMaths::Vector<size, componentType> {

        componentType components[size];

        /* -------------------------------------------- */
        /*  Initialisation                              */
        /* -------------------------------------------- */

        /**
         * Initialises all components to 0
         */
        Vector() : Vector(0) {}

        /**
         * Initialises all components to the same value
         * @param scalar The value to initialise the components to
         */
        explicit Vector(componentType scalar) : components(size) { std::fill_n(components, size, scalar); }

        /**
         * Initialises each component using values from a list
         * @param components The list to get the components from
         */
        Vector(const std::array<componentType, size>& components) {
            std::memcpy(this->components, components.data(), sizeof(componentType) * size);
        };

        /**
         * Initialises each component to a given value
         * @param args The components of the vector
         */
        Vector(const convertsTo<componentType> auto&... args)
            requires(sizeof...(args) == size)
            : components(args...) {}

        /* -------------------------------------------- */

        // Copy
        /**
         * Initialise using another vector, when the other vector is  will be initialised to 0
         * @tparam otherSize The size of the other vector
         * @tparam otherType The type of the other vector
         * @param otherVec The other vector to source the components from
         */
        template<int otherSize, typename otherType>
        Vector(const Vector<otherSize, otherType>& otherVec) : components(size) {
            for (int i = 0; i < size; ++i) {
                if (i < otherSize)
                    components[i] = otherVec[i];
                else
                    components[i] = 0;
            }
        }

        /* -------------------------------------------- */

        // Assignment operator
        template<typename otherType>
        Vector& operator=(const Vector<size, otherType>& otherVec) {
            for (int i = 0; i < size; ++i) {
                components[i] = otherVec[i];
            }

            return *this;
        }

        /* -------------------------------------------- */
        /*  getters                                     */
        /* -------------------------------------------- */

        const componentType& operator[](const size_t pos) const {
            assert(pos < size);
            return components[pos];
        }

        componentType& operator[](const size_t pos) {
            assert(pos < size);
            return components[pos];
        }

        /* -------------------------------------------- */
        /*  Maths                                       */
        /* -------------------------------------------- */

        // Add Vector
        template<typename otherType>
        Vector operator+(const Vector<size, otherType>& rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] + rhs[i];
            }

            return newVec;
        }

        // Add Scalar
        template<typename otherType>
        Vector operator+(otherType rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] + rhs;
            }

            return newVec;
        }

        // Add Vector In-Place
        template<typename otherType>
        Vector& operator+=(const Vector<size, otherType>& rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] += rhs[i];
            }

            return *this;
        }

        // Add Scalar In-Place
        template<typename otherType>
        Vector& operator+=(otherType rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] += rhs;
            }

            return *this;
        }

        /* -------------------------------------------- */

        // Minus Vector
        template<typename otherType>
        Vector operator-(const Vector<size, otherType>& rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] - rhs[i];
            }

            return newVec;
        }

        // Minus Scalar
        template<typename otherType>
        Vector operator-(otherType rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] - rhs;
            }

            return newVec;
        }

        // Minus Vector In-Place
        template<typename otherType>
        Vector& operator-=(const Vector<size, otherType>& rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] -= rhs[i];
            }

            return *this;
        }

        // Minus Scalar In-Place
        template<typename otherType>
        Vector& operator-=(otherType rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] -= rhs;
            }

            return *this;
        }

        /* -------------------------------------------- */

        //   Negation
        Vector operator-() {
            for (int i = 0; i < size; ++i) {
                (*this)[i] = -(*this)[i];
            }

            return *this;
        }

        /* -------------------------------------------- */

        // Multiply by Components
        template<typename otherType>
        Vector operator*(const Vector<size, otherType>& rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] * rhs[i];
            }

            return newVec;
        }

        // Multiply by Scalar
        template<typename otherType>
        Vector operator*(otherType rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] * rhs;
            }

            return newVec;
        }

        // Multiply by Components In-Place
        template<typename otherType>
        Vector& operator*=(const Vector<size, otherType>& rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] *= rhs[i];
            }

            return *this;
        }

        // Multiply by Scalar In-Place
        template<typename otherType>
        Vector& operator*=(otherType rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] *= rhs;
            }

            return *this;
        }

        /* -------------------------------------------- */

        // Divide by Components
        template<typename otherType>
        Vector operator/(const Vector<size, otherType>& rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] / rhs[i];
            }

            return newVec;
        }

        // Divide by Scalar
        template<typename otherType>
        Vector operator/(otherType rhs) const {
            Vector newVec;
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] / rhs;
            }

            return newVec;
        }

        // Divide by Components In-Place
        template<typename otherType>
        Vector& operator/=(const Vector<size, otherType>& rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] /= rhs[i];
            }

            return *this;
        }

        // Divide by Scalar In-Place
        template<typename otherType>
        Vector& operator/=(otherType rhs) {
            for (int i = 0; i < size; ++i) {
                (*this)[i] /= rhs;
            }

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
        componentType dotProduct(Vector<size, otherType> otherVec) const {
            componentType total = 0;

            for (int i = 0; i < size; ++i) {
                total += (*this)[i] * otherVec[i];
            }

            return total;
        }

        /* -------------------------------------------- */

        /**
         * Get the magnitude of the vector
         * @return the magnitude of the vector
         */
        componentType length() const { return DatMaths::sqrt(lengthSquared()); }

        /**
         * Get the magnitude squared of the vector
         * <br>
         * This saves an expensive sqrt operation so is preferable for some comparisons
         * @return The magnitude squared of the vector
         */
        componentType lengthSquared() const {
            componentType total = 0;
            for (int i = 0; i < size; ++i) {
                total += (*this)[i] * (*this)[i];
            }

            return total;
        }

        /* -------------------------------------------- */

        /**
         * Normalise the vector in place
         */
        void normalise() {
            componentType invLength = DatMaths::invSqrt(lengthSquared());

            for (int i = 0; i < size; ++i) {
                (*this)[i] *= invLength;
            }
        }

        /**
         * Get the normalised copy of this vector
         * @return a normalised copy of this vector
         */
        Vector normalised() const {
            Vector newVec;

            componentType invLength = DatMaths::invSqrt(lengthSquared());
            for (int i = 0; i < size; ++i) {
                newVec[i] = (*this)[i] * invLength;
            }

            return newVec;
        }

        /**
         * Get if this vector is normalised (has a length of one)
         * @return true if normalised
         */
        bool isNormalised(componentType tolerance = static_cast<componentType>(numbers::normalisedTolerance)) const {
            return lengthSquared() < tolerance;
        }

        /* -------------------------------------------- */
        /*  Comparison                                  */
        /* -------------------------------------------- */

        // Equals
        template<typename otherType>
        bool operator==(const Vector<size, otherType>& rhs) const {
            for (int i = 0; i < size; ++i) {
                if ((*this)[i] != rhs[i])
                    return false;
            }

            return true;
        }

        /**
         * Check if this vector is equal to another within a small tolerances
         * @tparam otherType The type of the other vector
         * @param rhs The other vector to compare to
         * @param tolerance How close the two vectors needs to be to be regarded as equal
         * @return true if equal within a tolerance
         */
        template<typename otherType>
        bool equal(const Vector<size, otherType>& rhs,
                   componentType tolerance = static_cast<componentType>(numbers::tinyNumber)) const {
            for (int i = 0; i < size; ++i) {
                if (std::abs((*this)[i] - static_cast<componentType>(rhs[i])) >= tolerance)
                    return false;
            }

            return true;
        }

        // Not Equal
        template<typename otherType>
        bool operator!=(const Vector<size, otherType>& rhs) const {
            return !operator==(rhs);
        }

        /* -------------------------------------------- */

        // Less than
        template<typename otherType>
        bool operator<(const Vector<size, otherType>& rhs) const {
            return this->lengthSquared() < static_cast<componentType>(rhs.lengthSquared());
        }

        // Greater Than
        template<typename otherType>
        bool operator>(const Vector<size, otherType>& rhs) const {
            return this->lengthSquared() > static_cast<componentType>(rhs.lengthSquared());
        }

        // Less than or equal
        template<typename otherType>
        bool operator<=(const Vector<size, otherType>& rhs) const {
            return this->lengthSquared() <= static_cast<componentType>(rhs.lengthSquared());
        }

        // Greater than or equal
        template<typename otherType>
        bool operator>=(const Vector<size, otherType>& rhs) const {
            return this->lengthSquared() >= static_cast<componentType>(rhs.lengthSquared());
        }

        /* -------------------------------------------- */

        // UFO Operator
        template<typename otherType>
        std::strong_ordering operator<=>(const Vector<size, otherType>& rhs) const {
            return this->lengthSquared() <=> static_cast<componentType>(rhs.lengthSquared());
        }
    };
}