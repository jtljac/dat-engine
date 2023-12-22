//
// Created by jacob on 03/09/23.
//

#include <util/type-traits.h>

#pragma once
namespace DatMaths {
    /**
     * A type representing a matrix
     * <br>
     * Matrices are represented in memory as column major.
     * @tparam width The number of columns
     * @tparam height The number of rows
     * @tparam componentType The type of the cells in the matrix
     */
    template<int width, int height, numeric componentType>
    struct Matrix;
}