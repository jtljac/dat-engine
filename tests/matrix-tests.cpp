//
// Created by jacob on 31/07/23.
//
#include <catch2/catch.hpp>

#include <maths/matrix.h>

using namespace DatMaths;

TEST_CASE("Mat4 initialisation", "[DatMaths, Mat4, Initialisation]") {
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
        mat4 lh({vec4(1, 2, 3, 4), vec4(5, 6, 7, 8), vec4(9, 10, 11, 12), vec4(13, 14, 15, 16)});

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
        mat4 lh({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f});

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                REQUIRE(lh[j][i] == 4 * j + i + 1);
            }
        }
    }
}