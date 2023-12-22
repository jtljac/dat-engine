//
// Created by jacob on 03/09/23.
//
#pragma once

#include "mat-forward.h"

#include <maths/vector.h>
#include <util/empty-init.h>

#include "mat-platform.h"

namespace DatMaths {
    /**
     * A Matrix composed of 4 columns and height rows
     * <br>
     * Matrices are represented in memory as column major.
     * @tparam height The number of rows
     * @tparam componentType The type of the cells in the matrix
     */
    template<int height, numeric componentType>
    struct Matrix<4, height, componentType> {
        static constexpr int width = 4;

#include "mat-common.inl"
        /* -------------------------------------------- */
        /*  Identity                                    */
        /* -------------------------------------------- */

        /**
         * Get an identity matrix
         * @return A 4x4 identity matrix
         */
        static matType identity()
        requires (height == width) {
            return matType(static_cast<componentType>(1), static_cast<componentType>(0), static_cast<componentType>(0), static_cast<componentType>(0),
                           static_cast<componentType>(0), static_cast<componentType>(1), static_cast<componentType>(0), static_cast<componentType>(0),
                           static_cast<componentType>(0), static_cast<componentType>(0), static_cast<componentType>(1), static_cast<componentType>(0),
                           static_cast<componentType>(0), static_cast<componentType>(0), static_cast<componentType>(0), static_cast<componentType>(1));
        }

        /* -------------------------------------------- */
        /*  Maths                                       */
        /* -------------------------------------------- */

        // Add Matrix
        template<numeric otherType>
        matType operator+(const Matrix<width, height, otherType>& rhs) {
            return {
                    this[0] + rhs[0],
                    this[1] + rhs[1],
                    this[2] + rhs[2],
                    this[3] + rhs[3]
            };
        }

        // Add Scalar
        template<numeric otherType>
        matType operator+(const otherType rhs) {
            return {
                this[0] + rhs,
                this[1] + rhs,
                this[2] + rhs,
                this[3] + rhs
            };
        }

        // Add Matrix In-Place
        template<numeric otherType>
        matType& operator+=(const Matrix<width, height, otherType>& rhs) {
            this[0] += rhs[0];
            this[1] += rhs[1];
            this[2] += rhs[2];
            this[3] += rhs[3];

            return *this;
        }

        // Add Scalar In-Place
        template<numeric otherType>
        matType& operator+=(otherType rhs) {
            this[0] += rhs;
            this[1] += rhs;
            this[2] += rhs;
            this[3] += rhs;

            return *this;
        }

        // Subtract Matrix
        template<numeric otherType>
        matType operator-(const Matrix<width, height, otherType>& rhs) {
            return {
                    this[0] - rhs[0],
                    this[1] - rhs[1],
                    this[2] - rhs[2],
                    this[3] - rhs[3]
            };
        }

        // Subtract Scalar
        template<numeric otherType>
        matType operator-(const otherType rhs) {
            return {
                    this[0] - rhs,
                    this[1] - rhs,
                    this[2] - rhs,
                    this[3] - rhs
            };
        }

        // Subtract Matrix In-Place
        template<numeric otherType>
        matType& operator-=(const Matrix<width, height, otherType>& rhs) {
            this[0] -= rhs[0];
            this[1] -= rhs[1];
            this[2] -= rhs[2];
            this[3] -= rhs[3];

            return *this;
        }

        // Subtract Scalar In-Place
        template<numeric otherType>
        matType& operator-=(otherType rhs) {
            this[0] -= rhs;
            this[1] -= rhs;
            this[2] -= rhs;
            this[3] -= rhs;

            return *this;
        }

        // Multiply Matrix implemented in common
        // Multiply Matrix In-Place implemented in common

        // Multiply Matrix 4x4
        template<numeric otherType>
        Matrix<width, height, componentType> operator*(const Matrix<width, height, otherType>& rhs) {
            return DatPlatform::matrixMultiply(*this, rhs);
        }

        // Multiply scalar
        template<numeric otherType>
        Matrix<width, height, componentType> operator*(const otherType rhs) {
            return {
                    cells[0] * rhs,
                    cells[1] * rhs,
                    cells[2] * rhs,
                    cells[3] * rhs
            };
        }

        // Multiply Matrix 4x4 In-Place
        template<numeric otherType>
        Matrix<width, height, componentType>& operator*=(const Matrix<width, height, otherType>& rhs) {
            DatPlatform::matrixMultiplyInPlace(*this, rhs);

            return *this;
        }

        // Multiply scalar in Place
        template<numeric otherType>
        Matrix<width, height, componentType>& operator*=(const otherType rhs) {
            cells[0] *= rhs;
            cells[1] *= rhs;
            cells[2] *= rhs;
            cells[3] *= rhs;
        }
    };
}