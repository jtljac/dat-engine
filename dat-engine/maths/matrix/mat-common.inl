/*
 * Generic components of matrices that aren't worth writing out multiple times
 */

using matType = Matrix<width, height, componentType>;
using transposeType = Matrix<height, width, componentType>;
using columnType = Vector<height, componentType>;
using rowType = Vector<width, componentType>;
columnType cells[width];

/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */

/**
 * Skip initialising
 * <br>
 * All components will have unspecified values
 */
explicit Matrix(EmptyInit) {}

/**
 * Initialise all cells to 0
 */
Matrix() : Matrix(0) {}

/**
 * Initialise all cells to the same value
 * @param scalar The value to initialise the components to
 */
Matrix(componentType scalar) {
std::fill_n(reinterpret_cast<componentType*>(cells), width * height, scalar);
}

/**
 * Initialises each column to given vectors
 * @param args The columns of the Matrix
 */
Matrix(const convertsTo<columnType> auto&... args)
requires (sizeof...(args) == width && width * height > 1) : cells(args...) {};

/**
 * Initialise each column using an array of columns
 * @param columns A list of columns to populate the matrix with
 */
explicit Matrix(const std::array<columnType, width>& columns) {
    std::memcpy(cells, columns.data(), sizeof(columnType) * width);
}

/**
 * Initialises each cell to given values
 * @param args The cells of the Matrix
 */
Matrix(const convertsTo<componentType> auto&... args)
requires (sizeof...(args) == width * height && width * height > 1) {
    std::array<componentType, width * height> elements = std::array<componentType, width * height>({{args...}});

    for (int i = 0; i < width; ++i) {

        for (int j = 0; j < height; ++j) {
            cells[i][j] = elements[i * width + j];
        }
    }
}

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
explicit Matrix(const std::array<componentType, width * height>& cells) {
    std::memcpy(this->cells, cells.begin(), sizeof(componentType) * width * height);
}

/* -------------------------------------------- */

/**
 * Initialise using values from another Matrix
 * <br>
 * If this Matrix is wider or taller than other Matrix then the extra cells will be initialised to zero
 * @tparam otherWidth The width of the other Matrix
 * @tparam otherHeight The height of the other Matrix
 * @tparam otherComponentType The type of the other Matrix
 * @param otherMat The other Matrix
 */
template <int otherWidth, int otherHeight, numeric otherComponentType>
explicit Matrix(const Matrix<otherWidth, otherHeight, otherComponentType>& otherMat) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cells[i][j] = i < otherWidth && j < otherHeight ? static_cast<componentType>(otherMat[i][j]) : 0;
        }
    }
}

template <numeric otherType>
matType& operator=(Matrix<width, height, otherType> rhs) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cells[i][j] = static_cast<componentType>(rhs[i][j]);
        }
    }
}

/* -------------------------------------------- */
/*  Accessors                                   */
/* -------------------------------------------- */

/**
 * Get a column of the matrix
 * <br>
 * This column will be a reference to the actual memory in the Matrix, therefore changes to the column will
 * reflect in the matrix.
 * @param pos The index of the column to get
 * @return The column at the given position
 */
columnType& getColumn(const size_t pos) {
    assert(pos < width);
    return cells[pos];
}

/**
 * Get a column of the matrix
 * <br>
 * This column will be a reference to the actual memory in the Matrix, therefore changes to the Matrix will
 * reflect on the column.
 * @param pos The index of the column to get
 * @return The column at the given position
 */
columnType& getColumn(const size_t pos) const {
    assert(pos < width);
    return cells[pos];
}

/**
 * Copy a column of the matrix
 * <br>
 * The return value will be a new vector and therefore changes will not affect the matrix.
 * @param pos The index of the column to clone
 * @return A copy of the column at the given position
 */
columnType cloneColumn(const size_t pos) const {
    assert(pos < width);
    return columnType(cells[pos]);
}

/**
 * Get a row of the matrix
 * <br>
 * This operation is more expensive than getColumn() as it needs to create a new vector. Subsequently, the returned
 * row is not a reference and changes to the row will not affect the Matrix.
 * @param pos
 * @return
 */
rowType getRow(const size_t pos) const {
    assert(pos < height);
    rowType row{EmptyInit::EMPTY};
    for (int i = 0; i < width; ++i) {
        row[i] = cells[i][pos];
    }

    return row;
}

inline columnType& operator[](const size_t pos) {
    return getColumn(pos);
}

inline columnType& operator[](const size_t pos) const {
    return getColumn(pos);
}

/* -------------------------------------------- */
/*  Maths                                       */
/* -------------------------------------------- */

template<int otherWidth, numeric otherType>
Matrix<otherWidth, height, componentType> operator*(const Matrix<otherWidth, width, otherType>& rhs) {
    Matrix<otherWidth, height, componentType> newMatrix{EmptyInit::EMPTY};

    for (int i = 0; i < otherWidth; ++i) {
        for (int j = 0; j < height; ++j) {
            newMatrix[j][i] = getRow(j).dotProduct(rhs.getColumn(i));
        }
    }

    return newMatrix;
}


template<int otherWidth, numeric otherType>
Matrix<otherWidth, height, componentType>& operator*=(Matrix<otherWidth, width, otherType> rhs) {
    *this = operator*(rhs);

    return *this;
}
