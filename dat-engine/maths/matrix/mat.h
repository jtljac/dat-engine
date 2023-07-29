//
// Created by jacob on 28/07/23.
//

#pragma once

#include <maths/vector/vec-forward.h>

namespace DatMaths {
    /**
     * A type representing a matrix of variable height and width
     * <br>
     * Matrices are represented in memory as column major.
     * @tparam width The number of columns
     * @tparam height The number of rows
     * @tparam componentType The type of the cells in the matrix
     */
    template<int width, int height, typename componentType>
    struct Matrix {
        typedef Matrix<width, height, componentType> matType;
        typedef Vector<height, componentType> columnType;
        typedef Vector<width, componentType> rowType;

        columnType cells[width];
    };
}