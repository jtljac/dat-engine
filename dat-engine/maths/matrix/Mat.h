#pragma once

#include <algorithm>
#include <cassert>
#include <cstring>
#include <maths/vector/VecForward.h>

namespace DatEngine::DatMaths {
    /**
     * A type representing a matrix of variable height and width
     * <br>
     * Matrices are represented in memory as column major.
     * @tparam TWidth The number of columns
     * @tparam THeight The number of rows
     * @tparam TComponent The type of the cells in the matrix
     */
    template<int TWidth, int THeight, CNumeric TComponent>
    class Matrix {
        /** The type of Matrix made by transposing this one*/
        using TTranspose = Matrix<THeight, TWidth, TComponent>;
        /** The type of the Matrix column */
        using TColumn = Vector<THeight, TComponent>;
        /** The type of the matrix row */
        using TRow = Vector<TWidth, TComponent>;

        /** The columns of the matrix */
        TColumn cells[TWidth];

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
        Matrix(TComponent scalar) { std::fill_n(reinterpret_cast<TComponent*>(cells), TWidth * THeight, scalar); }

        /**
         * Initialises each column to given vectors
         * @param args The columns of the Matrix
         */
        Matrix(const CConvertsTo<TColumn> auto&... args)
            requires(sizeof...(args) == TWidth && TWidth * THeight > 1)
            : cells(args...) {};

        /**
         * Initialise each column using an array of columns
         * @param columns A list of columns to populate the matrix with
         */
        explicit Matrix(const std::array<TColumn, TWidth>& columns) {
            std::memcpy(cells, columns.data(), sizeof(TColumn) * TWidth);
        }

        /**
         * Initialises each cell to given values
         * @param args The cells of the Matrix
         */
        Matrix(const CConvertsTo<TComponent> auto&... args)
            requires(sizeof...(args) == TWidth * THeight && TWidth * THeight > 1)
        {
            std::array<TComponent, TWidth * THeight> elements = std::array<TComponent, TWidth * THeight>({{args...}});

            for (int i = 0; i < TWidth; ++i) {
                for (int j = 0; j < THeight; ++j) {
                    cells[i][j] = elements[i * TWidth + j];
                }
            }
        };

        /**
         * Initialise cell with a list of cells
         *
         * This will copy the data from the given list in column major order, therefore the data will move from the
         * given array to the matrix in the following way (for a 3x3 matrix):
         *
         * 0, 3, 6 <br>
         * 1, 4, 7 <br>
         * 2, 5, 8
         * @param cells A list of cells to populate the matrix with
         */
        explicit Matrix(const std::array<TComponent, TWidth * THeight>& cells) {
            std::memcpy(this->cells, cells.begin(), sizeof(TComponent) * TWidth * THeight);
        }

        /* -------------------------------------------- */

        /**
         * Initialise using values from another Matrix
         *
         * If this Matrix is wider or taller than other Matrix then the extra cells will be initialised to zero
         * @tparam otherWidth The width of the other Matrix
         * @tparam otherHeight The height of the other Matrix
         * @tparam TOtherComponent The type of the other Matrix
         * @param otherMat The other Matrix
         */
        template<int otherWidth, int otherHeight, CNumeric TOtherComponent>
        explicit Matrix(const Matrix<otherWidth, otherHeight, TOtherComponent>& otherMat) {
            for (int i = 0; i < TWidth; ++i) {
                for (int j = 0; j < THeight; ++j) {
                    cells[i][j] = i < otherWidth && j < otherHeight ? static_cast<TComponent>(otherMat[i][j]) : 0;
                }
            }
        }

        /* -------------------------------------------- */
        /*  Identity                                    */
        /* -------------------------------------------- */

        /**
         * Get an identity matrix
         *
         * @note To ensure this is optimal, there are separate implementations for specific matrix sizes (mat1, mat2,
         *       mat3, mat4) using `if constexpr`. For all other matrix sizes a much slower general approach is used.
         *
         * @return A 1x1 identity matrix
         */
        static Matrix identity()
            requires(TWidth == THeight)
        {
            if constexpr (TWidth == 1) {
                return Matrix(static_cast<TComponent>(1));
            } else if constexpr (TWidth == 2) {
                return Matrix(
                        static_cast<TComponent>(1),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(1)
                );
            } else if constexpr (TWidth == 3) {
                return Matrix(
                        static_cast<TComponent>(1),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(1),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(1)
                );
            } else if constexpr (TWidth == 4) {
                return Matrix(
                        static_cast<TComponent>(1),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(1),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(1),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(0),
                        static_cast<TComponent>(1)
                );
            } else {
                // Slow fallback, has to make a whole array
                std::array<TComponent, TWidth * THeight> init;
                for (int i = 0; i < TWidth; ++i) {
                    for (int j = 0; j < THeight; ++j) {
                        if (i == j)
                            init[i * TWidth + j] = 1;
                        else
                            init[i * TWidth + j] = 0;
                    }
                }

                return Matrix(init);
            }
        }

        // Assignment
        // Getter
        TColumn& operator[](const size_t pos) { return getColumn(pos); }

        TColumn& operator[](const size_t pos) const { return getColumn(pos); }

        /**
         * Get a column of the matrix
         * <br>
         * This column will be a reference to the actual memory in the Matrix, therefore changes to the column will
         * reflect in the matrix.
         *
         * @param pos The index of the column to get
         * @return The column at the given position
         */
        TColumn& getColumn(const size_t pos) {
            assert(pos < TWidth);
            return cells[pos];
        }

        /**
         * Get a column of the matrix
         * <br>
         * This column will be a reference to the actual memory in the Matrix, therefore changes to the Matrix will
         * reflect on the column.
         *
         * @param pos The index of the column to get
         * @return The column at the given position
         */
        TColumn& getColumn(const size_t pos) const {
            assert(pos < TWidth);
            return cells[pos];
        }

        /**
         * Get a row of the matrix
         * <br>
         * This operation is more expensive than getColumn() as it needs to create a new vector. Subsequently, the
         * returned row is not a reference and changes to the row will not affect the Matrix.
         * @param pos The index of the row to get
         * @return The row at the given index
         */
        TRow getRow(const size_t pos) const {
            assert(pos < THeight);
            TRow row;
            for (int i = 0; i < TWidth; ++i) {
                row[i] = cells[i][pos];
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
} // namespace DatEngine::DatMaths
