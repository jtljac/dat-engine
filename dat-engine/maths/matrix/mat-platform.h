//
// Created by jacob on 03/09/23.
//

#pragma once
#include <maths/matrix/mat-forward.h>

namespace DatPlatform {
    /**
     * Get the Matrix multiplication of two 4x4 matrices using SSE Intrinsics
     * @param lhs The left hand Matrix
     * @param rhs The right hand Matrix
     * @return A new Matrix
     */
    DatMaths::Matrix<4, 4, float> matrixMultiply(const DatMaths::Matrix<4, 4, float>& lhs, const DatMaths::Matrix<4, 4, float>& rhs);

    /**
     * Get the Matrix multiplication of two 4x4 matrices using SSE Intrinsics, storing the result in the lhs matrix
     * @param lhs The left hand Matrix, also where the result is stored
     * @param rhs The right hand Matrix
     */
    void matrixMultiplyInPlace(DatMaths::Matrix<4, 4, float>& lhs, const DatMaths::Matrix<4, 4, float>& rhs);
}