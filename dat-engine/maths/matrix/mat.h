//
// Created by jacob on 28/07/23.
//

#pragma once

#include <maths/vector/vec-forward.h>
#include <algorithm>
#include <tuple>
#include <cassert>
#include <cstring>

namespace DatMaths {
    /**
     * A type representing a matrix of variable height and width
     * <br>
     * Matrices are represented in memory as column major.
     * @tparam width The number of columns
     * @tparam height The number of rows
     * @tparam componentType The type of the cells in the matrix
     */
    template<int width, int height, numeric componentType>
    struct Matrix {
        typedef Matrix<width, height, componentType> matType;
        typedef Matrix<height, width, componentType> transposeType;
        typedef Vector<height, componentType> columnType;
        typedef Vector<width, componentType> rowType;

    protected:
        columnType cells[width];

    public:
        /* -------------------------------------------- */
        /*  Initialisation                              */
        /* -------------------------------------------- */

        /**
         * Initialise all cells to 0
         */
        Matrix() : Matrix(0) {}

        /**
         * Initialise all cells to the same value
         * @param scalar The value to initialise the components to
         */
        Matrix(componentType scalar) {
            std::fill_n(reinterpret_cast<componentType*>(&cells), width * height, scalar);
        }

        /**
         * Initialises each column to given vectors
         * @param args The columns of the Matrix
         */
        Matrix(const convertsTo<columnType> auto&... args)
        requires (sizeof...(args) == width) : cells(args...) {};

        /**
         * Initialise each column using an array of columns
         * @param columns A list of columns to populate the matrix with
         */
        Matrix(const std::initializer_list<columnType>& columns) {
            assert(columns.size() == width);
            std::memcpy(cells, columns.begin(), sizeof(columnType) * width);
        }

        /**
         * Initialises each cell to given values
         * @param args The cells of the Matrix
         */
        Matrix(const convertsTo<componentType> auto&... args)
        requires (sizeof...(args) == width * height) {
            std::array<componentType, width * height> elements = std::array<componentType, width * height>({{args...}});

            for (int i = 0; i < width; ++i) {

                for (int j = 0; j < height; ++j) {
                    cells[i][j] = elements[i * width + j];
                }
            }
        };

        /**
         * Initialise cell with a list of cells
         * <br>
         * This will copy the data from the given list in column major order, therefore the data will move from the given
         * array to the matrix in the following way (for a 3x3 matrix:
         * <br>
         * 0, 3, 6 <br>
         * 1, 4, 7 <br>
         * 2, 5, 8
         * @param cells A list of cells to populate the matrix with
         */
        Matrix(const std::initializer_list<componentType>& cells) {
            assert(cells.size() == width * height);
            std::memcpy(this->cells, cells.begin(), sizeof(componentType) * width * height);
        }

        // Constructor
        //   Scalar
        //   Vectors
        //   Array
        //   Raw Numbers

        // Identity Matrix

        // Conversion

        // Assignment

        // Getter
        inline columnType operator[](const size_t pos) {
            return getColumn(pos);
        }

        columnType getColumn(const size_t pos) {
            assert(pos < width);
            return cells[pos];
        }

        rowType getRow(const size_t pos) {
            assert(pos < height);
            rowType row;
            for (int i = 0; i < width; ++i) {
                row[i] = cells[pos][i];
            }

            return row;
        }

        // Maths
        //   Add
        //   Minus
        //   Multiply
        //   Divide

        // Transpose

        // Determinate
        // Inverse

        // Bitwise
        //   And
        //   or
        //   xor
    };
}