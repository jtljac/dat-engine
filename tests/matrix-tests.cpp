#include <catch2/catch_test_macros.hpp>

#include <maths/matrix.h>

using namespace DatEngine::DatMaths;

TEST_CASE("Mat3 initialisation", "[DatMaths, Matrix, Mat3, Initialisation]") {
    SECTION("Zero") {
        mat3 lh;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                REQUIRE(lh[j][i] == 0);
            }
        }
    }

    SECTION("Scalar") {
        mat3 lh(5);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                REQUIRE(lh[j][i] == 5);
            }
        }
    }

    SECTION("Vector") {
        mat3 lh(vec3(1, 2, 3), vec3(4, 5, 6), vec3(7, 8, 9));

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                REQUIRE(lh[j][i] == 3 * j + i + 1);
            }
        }
    }



    SECTION("Vector Array") {
        mat3 lh(std::array<vec3, 3>({vec3(1, 2, 3), vec3(4, 5, 6), vec3(7, 8, 9)}));

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                REQUIRE(lh[j][i] == 3 * j + i + 1);
            }
        }
    }

    SECTION("Cell") {
        mat3 lh(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                REQUIRE(lh[j][i] == 3 * j + i + 1);
            }
        }
    }

    SECTION("Cell Array") {
        mat3 lh(std::array<float, 3 * 3>({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f}));

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                REQUIRE(lh[j][i] == 3 * j + i + 1);
            }
        }
    }
}

TEST_CASE("Mat4 initialisation", "[DatMaths, Matrix, Mat4, Initialisation]") {
    SECTION("Zero") {
        mat4 lh;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                REQUIRE(lh[j][i] == 0);
            }
        }
    }

    SECTION("Scalar") {
        mat4 lh(5);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                REQUIRE(lh[j][i] == 5);
            }
        }
    }

    SECTION("Vector") {
        mat4 lh(vec4(1, 2, 3, 4), vec4(5, 6, 7, 8), vec4(9, 10, 11, 12), vec4(13, 14, 15, 16));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                REQUIRE(lh[j][i] == 4 * j + i + 1);
            }
        }
    }



    SECTION("Vector Array") {
        mat4 lh(std::array<vec4, 4>({vec4(1, 2, 3, 4), vec4(5, 6, 7, 8), vec4(9, 10, 11, 12), vec4(13, 14, 15, 16)}));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                REQUIRE(lh[j][i] == 4 * j + i + 1);
            }
        }
    }

    SECTION("Cell") {
        mat4 lh(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                REQUIRE(lh[j][i] == 4 * j + i + 1);
            }
        }
    }

    SECTION("Cell Array") {
        mat4 lh(std::array<float, 4 * 4>({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f}));

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                REQUIRE(lh[j][i] == 4 * j + i + 1);
            }
        }
    }
}

TEST_CASE("Identity Matrix", "[DatMaths, Mat, Identity]") {
    SECTION("Mat1") {
        Matrix<1, 1, float> matrix = Matrix<1, 1, float>::identity();

        REQUIRE(matrix[0][0] == 1);
    }

    SECTION("Mat2") {
        Matrix<2, 2, float> matrix = Matrix<2, 2, float>::identity();

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; i < 2; ++i) {
                REQUIRE(matrix[i][j] == (i == j ? 1 : 0));
            }
        }
    }

    SECTION("Mat3") {
        Matrix<3, 3, float> matrix = Matrix<3, 3, float>::identity();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; i < 3; ++i) {
                REQUIRE(matrix[i][j] == (i == j ? 1 : 0));
            }
        }
    }

    SECTION("Mat4") {
        Matrix<4, 4, float> matrix = Matrix<4, 4, float>::identity();

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; i < 4; ++i) {
                REQUIRE(matrix[i][j] == (i == j ? 1 : 0));
            }
        }
    }

    SECTION("Mat5") {
        Matrix<5, 5, float> matrix = Matrix<5, 5, float>::identity();

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i == j) REQUIRE(matrix[i][j] == 1);
                else REQUIRE(matrix[i][j] == 0);
            }
        }
    }
}

TEST_CASE("Get Row", "[DatMaths, Mat]") {
    SECTION("Mat1") {
        constexpr int ROW = 0;
        Matrix<1, 1, float> matrix(1);

        vec1 row = matrix.getRow(ROW);
        REQUIRE(row.x == matrix[0][ROW]);
    }
    SECTION("Mat2") {
        constexpr int ROW = 1;
        Matrix<2, 2, float> matrix(1.f, 2.f, 3.f, 4.f);

        vec2 row = matrix.getRow(ROW);
        for(int i = 0; i < 2; ++i) {
            REQUIRE(row[i] == matrix[i][ROW]);
        }
    }
    SECTION("Mat3") {
        constexpr int ROW = 1;
        Matrix<3, 3, float> matrix(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

        vec3 row = matrix.getRow(ROW);
        for(int i = 0; i < 3; ++i) {
            REQUIRE(row[i] == matrix[i][ROW]);
        }
    }
    SECTION("Mat4") {
        constexpr int ROW = 2;
        Matrix<4, 4, float> matrix(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);

        vec4 row = matrix.getRow(ROW);
        for(int i = 0; i < 4; ++i) {
            REQUIRE(row[i] == matrix[i][ROW]);
        }
    }
    SECTION("Mat5") {
        constexpr int ROW = 3;
        Matrix<5, 5, float> matrix(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f);

        vecn<5> row = matrix.getRow(ROW);
        for(int i = 0; i < 5; ++i) {
            REQUIRE(row[i] == matrix[i][ROW]);
        }
    }
}