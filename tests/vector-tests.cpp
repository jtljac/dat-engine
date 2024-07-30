//
// Created by jacob on 29/06/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <maths/vector.h>

using namespace DatEngine::DatMaths;

/* -------------------------------------------- */
/*  Statics                                     */
/* -------------------------------------------- */

TEST_CASE("Vec2 Statics", "[DatMaths, Vector, Vec2, Statics]") {
    SECTION("Up") {
        vec2 up = vec2::UP;
        REQUIRE(up.x == 0);
        REQUIRE(up.y == -1);
    }

    SECTION("Right") {
        vec2 right = vec2::RIGHT;
        REQUIRE(right.x == 1);
        REQUIRE(right.y == 0);
    }

    SECTION("Down") {
        vec2 down = vec2::DOWN;
        REQUIRE(down.x == 0);
        REQUIRE(down.y == 1);
    }

    SECTION("Left") {
        vec2 left = vec2::LEFT;
        REQUIRE(left.x == -1);
        REQUIRE(left.y == 0);
    }
}

TEST_CASE("Vec3 Statics", "[DatMaths, Vector, Vec3, Statics]") {
    SECTION("Up") {
        vec3 up = vec3::UP;
        REQUIRE(up.x == 0);
        REQUIRE(up.y == 1);
        REQUIRE(up.z == 0);
    }

    SECTION("Down") {
        vec3 down = vec3::DOWN;
        REQUIRE(down.x == 0);
        REQUIRE(down.y == -1);
        REQUIRE(down.z == 0);
    }

    SECTION("North") {
        vec3 north = vec3::NORTH;
        REQUIRE(north.x == 0);
        REQUIRE(north.y == 0);
        REQUIRE(north.z == 1);
    }

    SECTION("East") {
        vec3 east = vec3::EAST;
        REQUIRE(east.x == 1);
        REQUIRE(east.y == 0);
        REQUIRE(east.z == 0);
    }

    SECTION("South") {
        vec3 south = vec3::SOUTH;
        REQUIRE(south.x == 0);
        REQUIRE(south.y == 0);
        REQUIRE(south.z == -1);
    }

    SECTION("West") {
        vec3 west = vec3::WEST;
        REQUIRE(west.x == -1);
        REQUIRE(west.y == 0);
        REQUIRE(west.z == 0);
    }
}

/* -------------------------------------------- */
/*  Initialisation                              */
/* -------------------------------------------- */

TEST_CASE("Vec1 Initialisation", "[DatMaths, Vector, Vec1, Initialisation]") {
    SECTION("Zero") {
        vec1 vec;
        REQUIRE(vec.x == 0);
    }

    SECTION("Component") {
        vec1 vec(5);
        REQUIRE(vec.x == 5);
    }

    SECTION("Vec1 Copy") {
        vec1 lh(6);
        vec1 rh(lh);

        REQUIRE(&lh != &rh);
        REQUIRE(rh.x == lh.x);
    }

    SECTION("Vec2 Copy") {
        vec2 lh(6, 2);
        vec1 rh(lh);

        REQUIRE(rh.x == lh.x);
    }

    SECTION("Vec3 Copy") {
        vec3 lh(6, 2, 5);
        vec1 rh(lh);

        REQUIRE(rh.x == lh.x);
    }

    SECTION("Vec4 Copy") {
        vec4 lh(6, 2, 5, 7);
        vec1 rh(lh);

        REQUIRE(rh.x == lh.x);
    }

    SECTION("Vecn Copy") {
        vecn<7> lh(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
        vec1 rh(lh);

        REQUIRE(rh.x == lh[0]);
    }
}

TEST_CASE("Vec2 Initialisation", "[DatMaths, Vector, Vec2, Initialisation]") {
    SECTION("Zero") {
        vec2 vec;
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
    }

    SECTION("Scalar") {
        vec2 vec(5);
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == 5);
    }

    SECTION("Component") {
        vec2 vec(5, 6);
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == 6);
    }

    SECTION("Vec1 Copy") {
        vec1 lh(6);
        vec2 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == 0);
    }



    SECTION("Vec1 Copy with component") {
        vec1 lh(6);
        vec2 rh(lh, 1);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == 1);
    }

    SECTION("Vec2 Copy") {
        vec2 lh(6, 2);
        vec2 rh(lh);

        REQUIRE(&lh != &rh);
        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
    }

    SECTION("Vec3 Copy") {
        vec3 lh(6, 2, 5);
        vec2 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
    }

    SECTION("Vec4 Copy") {
        vec4 lh(6, 2, 5, 7);
        vec2 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
    }

    SECTION("Vecn Copy") {
        vecn<7> lh(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
        vec2 rh(lh);

        REQUIRE(rh.x == lh[0]);
        REQUIRE(rh.y == lh[1]);
    }
}

TEST_CASE("Vec3 Initialisation", "[DatMaths, Vector, Vec3, Initialisation]") {
    SECTION("Zero") {
        vec3 vec;
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        REQUIRE(vec.z == 0);
    }

    SECTION("Scalar") {
        vec3 vec(5);
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == 5);
        REQUIRE(vec.z == 5);
    }

    SECTION("Component") {
        vec3 vec(5, 6, 7);
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == 6);
        REQUIRE(vec.z == 7);
    }

    SECTION("Vec1 Copy") {
        vec1 lh(6);
        vec3 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == 0);
        REQUIRE(rh.z == 0);
    }

    SECTION("Vec1 Copy with components") {
        vec1 lh(6);
        vec3 rh(lh, 1, 2);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == 1);
        REQUIRE(rh.z == 2);
    }

    SECTION("Vec2 Copy") {
        vec2 lh(6, 2);
        vec3 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == 0);
    }

    SECTION("Vec2 Copy with component") {
        vec2 lh(6, 2);
        vec3 rh(lh, 1);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == 1);
    }

    SECTION("Vec3 Copy") {
        vec3 lh(6, 2, 5);
        vec3 rh(lh);

        REQUIRE(&lh != &rh);
        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == lh.z);
    }

    SECTION("Vec4 Copy") {
        vec4 lh(6, 2, 5, 7);
        vec3 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == lh.z);
    }

    SECTION("Vecn Copy") {
        vecn<7> lh(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
        vec3 rh(lh);

        REQUIRE(rh.x == lh[0]);
        REQUIRE(rh.y == lh[1]);
        REQUIRE(rh.z == lh[2]);
    }
}

TEST_CASE("Vec4 Initialisation", "[DatMaths, Vector, Vec4, Initialisation]") {
    SECTION("Zero") {
        vec4 vec;
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        REQUIRE(vec.z == 0);
        REQUIRE(vec.w == 0);
    }

    SECTION("Scalar") {
        vec4 vec(5);
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == 5);
        REQUIRE(vec.z == 5);
        REQUIRE(vec.w == 5);
    }

    SECTION("Component") {
        vec4 vec(5, 6, 7, 8);
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == 6);
        REQUIRE(vec.z == 7);
        REQUIRE(vec.w == 8);
    }

    SECTION("Vec1 Copy") {
        vec1 lh(6);
        vec4 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == 0);
        REQUIRE(rh.z == 0);
        REQUIRE(rh.z == 0);
    }

    SECTION("Vec1 Copy with components") {
        vec1 lh(6);
        vec4 rh(lh, 1, 2, 3);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == 1);
        REQUIRE(rh.z == 2);
        REQUIRE(rh.w == 3);
    }

    SECTION("Vec2 Copy") {
        vec2 lh(6, 2);
        vec4 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == 0);
        REQUIRE(rh.w == 0);
    }

    SECTION("Vec2 Copy with components") {
        vec2 lh(6, 2);
        vec4 rh(lh, 1, 3);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == 1);
        REQUIRE(rh.w == 3);
    }

    SECTION("Vec3 Copy") {
        vec3 lh(6, 2, 5);
        vec4 rh(lh);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == lh.z);
        REQUIRE(rh.w == 0);
    }

    SECTION("Vec3 Copy with component") {
        vec3 lh(6, 2, 5);
        vec4 rh(lh, 7);

        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == lh.z);
        REQUIRE(rh.w == 7);
    }

    SECTION("Vec4 Copy") {
        vec4 lh(6, 2, 5, 7);
        vec4 rh(lh);

        REQUIRE(&lh != &rh);
        REQUIRE(rh.x == lh.x);
        REQUIRE(rh.y == lh.y);
        REQUIRE(rh.z == lh.z);
        REQUIRE(rh.w == lh.w);
    }

    SECTION("Vecn Copy") {
        vecn<7> lh(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
        vec4 rh(lh);

        REQUIRE(rh.x == lh[0]);
        REQUIRE(rh.y == lh[1]);
        REQUIRE(rh.z == lh[2]);
        REQUIRE(rh.w == lh[3]);
    }
}

TEST_CASE("Vecn Initialisation", "[DatMaths, Vector, Vecn, Initialisation]") {
    SECTION("Zero") {
        vecn<7> vec;
        REQUIRE(vec[0] == 0);
        REQUIRE(vec[1] == 0);
        REQUIRE(vec[2] == 0);
        REQUIRE(vec[3] == 0);
        REQUIRE(vec[4] == 0);
        REQUIRE(vec[5] == 0);
        REQUIRE(vec[6] == 0);
    }

    SECTION("Scalar") {
        vecn<7> vec(5);
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 5);
        REQUIRE(vec[2] == 5);
        REQUIRE(vec[3] == 5);
        REQUIRE(vec[4] == 5);
        REQUIRE(vec[5] == 5);
        REQUIRE(vec[6] == 5);
    }

    SECTION("Component") {
        vecn<7> vec(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
        REQUIRE(vec[3] == 4);
        REQUIRE(vec[4] == 5);
        REQUIRE(vec[5] == 6);
        REQUIRE(vec[6] == 7);
    }

    SECTION("Component list") {
        vecn<7> vec(std::array<float, 7>({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f}));
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
        REQUIRE(vec[3] == 4);
        REQUIRE(vec[4] == 5);
        REQUIRE(vec[5] == 6);
        REQUIRE(vec[6] == 7);
    }

    SECTION("Vec1 Copy") {
        vec1 lh(6);
        vecn<7> rh(lh);

        REQUIRE(rh[0] == lh.x);
        REQUIRE(rh[1] == 0);
        REQUIRE(rh[2] == 0);
        REQUIRE(rh[3] == 0);
        REQUIRE(rh[4] == 0);
        REQUIRE(rh[5] == 0);
        REQUIRE(rh[6] == 0);
    }

    SECTION("Vec2 Copy") {
        vec2 lh(6, 2);
        vecn<7> rh(lh);


        REQUIRE(rh[0] == lh.x);
        REQUIRE(rh[1] == lh.y);
        REQUIRE(rh[2] == 0);
        REQUIRE(rh[3] == 0);
        REQUIRE(rh[4] == 0);
        REQUIRE(rh[5] == 0);
        REQUIRE(rh[6] == 0);
    }

    SECTION("Vec3 Copy") {
        vec3 lh(6, 2, 5);
        vecn<7> rh(lh);


        REQUIRE(rh[0] == lh.x);
        REQUIRE(rh[1] == lh.y);
        REQUIRE(rh[2] == lh.z);
        REQUIRE(rh[3] == 0);
        REQUIRE(rh[4] == 0);
        REQUIRE(rh[5] == 0);
        REQUIRE(rh[6] == 0);
    }

    SECTION("Vec4 Copy") {
        vec4 lh(6, 2, 5, 7);
        vecn<7> rh(lh);

        REQUIRE(rh[0] == lh.x);
        REQUIRE(rh[1] == lh.y);
        REQUIRE(rh[2] == lh.z);
        REQUIRE(rh[3] == lh.w);
        REQUIRE(rh[4] == 0);
        REQUIRE(rh[5] == 0);
        REQUIRE(rh[6] == 0);
    }

    SECTION("Vecn smaller Copy") {
        vecn<5> lh{1.f, 2.f, 3.f, 4.f, 5.f};
        vecn<7> rh(lh);

        REQUIRE(rh[0] == lh[0]);
        REQUIRE(rh[1] == lh[1]);
        REQUIRE(rh[2] == lh[2]);
        REQUIRE(rh[3] == lh[3]);
        REQUIRE(rh[4] == lh[4]);
        REQUIRE(rh[5] == 0);
        REQUIRE(rh[6] == 0);
    }

    SECTION("Vecn same Copy") {
        vecn<7> lh{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f};
        vecn<7> rh(lh);

        REQUIRE(&lh != &rh);
        REQUIRE(rh[0] == lh[0]);
        REQUIRE(rh[1] == lh[1]);
        REQUIRE(rh[2] == lh[2]);
        REQUIRE(rh[3] == lh[3]);
        REQUIRE(rh[4] == lh[4]);
        REQUIRE(rh[5] == lh[5]);
        REQUIRE(rh[6] == lh[6]);
    }

    SECTION("Vecn bigger Copy") {
        vecn<9> lh{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};
        vecn<7> rh(lh);


        REQUIRE(rh[0] == lh[0]);
        REQUIRE(rh[1] == lh[1]);
        REQUIRE(rh[2] == lh[2]);
        REQUIRE(rh[3] == lh[3]);
        REQUIRE(rh[4] == lh[4]);
        REQUIRE(rh[5] == lh[5]);
        REQUIRE(rh[6] == lh[6]);
    }
}

/* -------------------------------------------- */
/*  Assignment                                  */
/* -------------------------------------------- */

TEST_CASE("Vec1 Assignment", "[DatMaths, Vector, Vec1, Assignment]") {
    vec1 lh(6);
    vec1 rh = lh;

    REQUIRE(&lh != &rh);
    REQUIRE(rh.x == lh.x);
}

TEST_CASE("Vec2 Assignment", "[DatMaths, Vector, Vec2, Assignment]") {
    vec2 lh(6, 2);
    vec2 rh = lh;

    REQUIRE(&lh != &rh);
    REQUIRE(rh.x == lh.x);
    REQUIRE(rh.y == lh.y);
}

TEST_CASE("Vec3 Assignment", "[DatMaths, Vector, Vec3, Assignment]") {
    vec3 lh(6, 2, 5);
    vec3 rh = lh;

    REQUIRE(&lh != &rh);
    REQUIRE(rh.x == lh.x);
    REQUIRE(rh.y == lh.y);
    REQUIRE(rh.z == lh.z);
}

TEST_CASE("Vec4 Assignment", "[DatMaths, Vector, Vec4, Assignment]") {
    vec4 lh(6, 2, 5, 7);
    vec4 rh = lh;

    REQUIRE(&lh != &rh);
    REQUIRE(rh.x == lh.x);
    REQUIRE(rh.y == lh.y);
    REQUIRE(rh.z == lh.z);
    REQUIRE(rh.w == lh.w);
}

TEST_CASE("Vecn Assignment", "[DatMaths, Vector, Vecn, Assignment]") {
    vecn<7> lh{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f};
    vecn<7> rh = lh;

    REQUIRE(&lh != &rh);
    REQUIRE(rh[0] == lh[0]);
    REQUIRE(rh[1] == lh[1]);
    REQUIRE(rh[2] == lh[2]);
    REQUIRE(rh[3] == lh[3]);
    REQUIRE(rh[4] == lh[4]);
    REQUIRE(rh[5] == lh[5]);
    REQUIRE(rh[6] == lh[6]);
}

/* -------------------------------------------- */
/*  Square Bracket Access                       */
/* -------------------------------------------- */

TEST_CASE("Vec1 Square Bracket Access", "[DatMaths, Vector, Vec1, Access]") {
    vec2 vec(6, 2);

    REQUIRE(vec.x == vec[0]);
}

TEST_CASE("Vec2 Square Bracket Access", "[DatMaths, Vector, Vec2, Access]") {
    vec2 vec(6, 2);

    REQUIRE(vec.x == vec[0]);
    REQUIRE(vec.y == vec[1]);
}

TEST_CASE("Vec3 Square Bracket Access", "[DatMaths, Vector, Vec3, Access]") {
    vec3 vec(6, 2, 5);

    REQUIRE(vec.x == vec[0]);
    REQUIRE(vec.y == vec[1]);
    REQUIRE(vec.z == vec[2]);
}

TEST_CASE("Vec4 Square Bracket Access", "[DatMaths, Vector, Vec4, Access]") {
    vec4 vec(6, 2, 5, 7);

    REQUIRE(vec.x == vec[0]);
    REQUIRE(vec.y == vec[1]);
    REQUIRE(vec.z == vec[2]);
    REQUIRE(vec.w == vec[3]);
}

/* -------------------------------------------- */
/*  Addition                                    */
/* -------------------------------------------- */

TEST_CASE("Vec1 Add", "[DatMaths, Vector, Vec1, Add]") {
    SECTION("Add Vector") {
        vec1 lh{5};
        vec1 rh{2};

        vec1 newVec = lh + rh;
        REQUIRE(newVec.x == 7);
    }

    SECTION("Add Scalar") {
        vec1 lh{5};

        vec1 newVec = lh + 5;
        REQUIRE(newVec.x == 10);
    }

    SECTION("Add Vector in Place") {
        vec1 lh{5};
        vec1 rh{2};

        lh += rh;
        REQUIRE(lh.x == 7);
    }

    SECTION("Add Scalar In Place") {
        vec1 lh{5};

        lh += 5;
        REQUIRE(lh.x == 10);
    }
}

TEST_CASE("Vec2 Add", "[DatMaths, Vector, Vec2, Add]") {
    SECTION("Add Vector") {
        vec2 lh{5, 6};
        vec2 rh{2, 3};

        vec2 newVec = lh + rh;
        REQUIRE(newVec.x == 7);
        REQUIRE(newVec.y == 9);
    }

    SECTION("Add Scalar") {
        vec2 lh{5, 6};

        vec2 newVec = lh + 5;
        REQUIRE(newVec.x == 10);
        REQUIRE(newVec.y == 11);
    }

    SECTION("Add Vector in Place") {
        vec2 lh{5, 6};
        vec2 rh{2, 3};

        lh += rh;
        REQUIRE(lh.x == 7);
        REQUIRE(lh.y == 9);
    }

    SECTION("Add Scalar In Place") {
        vec2 lh{5, 6};

        lh += 5;
        REQUIRE(lh.x == 10);
        REQUIRE(lh.y == 11);
    }
}

TEST_CASE("Vec3 Add", "[DatMaths, Vector, Vec3, Add]") {
    SECTION("Add Vector") {
        vec3 lh{5, 6, 7};
        vec3 rh{2, 3, 4};

        vec3 newVec = lh + rh;
        REQUIRE(newVec.x == 7);
        REQUIRE(newVec.y == 9);
        REQUIRE(newVec.z == 11);
    }

    SECTION("Add Scalar") {
        vec3 lh{5, 6, 7};

        vec3 newVec = lh + 5;
        REQUIRE(newVec.x == 10);
        REQUIRE(newVec.y == 11);
        REQUIRE(newVec.z == 12);
    }

    SECTION("Add Vector in Place") {
        vec3 lh{5, 6, 7};
        vec3 rh{2, 3, 4};

        lh += rh;
        REQUIRE(lh.x == 7);
        REQUIRE(lh.y == 9);
        REQUIRE(lh.z == 11);
    }

    SECTION("Add Scalar In Place") {
        vec3 lh{5, 6, 7};

        lh += 5;
        REQUIRE(lh.x == 10);
        REQUIRE(lh.y == 11);
        REQUIRE(lh.z == 12);
    }
}

TEST_CASE("Vec4 Add", "[DatMaths, Vector, Vec4, Add]") {
    SECTION("Add Vector") {
        vec4 lh{5, 6, 7, 8};
        vec4 rh{2, 3, 4, 5};

        vec4 newVec = lh + rh;
        REQUIRE(newVec.x == 7);
        REQUIRE(newVec.y == 9);
        REQUIRE(newVec.z == 11);
        REQUIRE(newVec.w == 13);
    }

    SECTION("Add Scalar") {
        vec4 lh{5, 6, 7, 8};

        vec4 newVec = lh + 5;
        REQUIRE(newVec.x == 10);
        REQUIRE(newVec.y == 11);
        REQUIRE(newVec.z == 12);
        REQUIRE(newVec.w == 13);
    }

    SECTION("Add Vector in Place") {
        vec4 lh{5, 6, 7, 8};
        vec4 rh{2, 3, 4, 5};

        lh += rh;
        REQUIRE(lh.x == 7);
        REQUIRE(lh.y == 9);
        REQUIRE(lh.z == 11);
        REQUIRE(lh.w == 13);
    }

    SECTION("Add Scalar In Place") {
        vec4 lh{5, 6, 7, 8};

        lh += 5;
        REQUIRE(lh.x == 10);
        REQUIRE(lh.y == 11);
        REQUIRE(lh.z == 12);
        REQUIRE(lh.w == 13);
    }
}

TEST_CASE("Vecn Add", "[DatMaths, Vector, Vecn, Add]") {
    SECTION("Add Vector") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        vecn<7> newVec = lh + rh;
        REQUIRE(newVec[0] == 7);
        REQUIRE(newVec[1] == 9);
        REQUIRE(newVec[2] == 11);
        REQUIRE(newVec[3] == 13);
        REQUIRE(newVec[4] == 15);
        REQUIRE(newVec[5] == 17);
        REQUIRE(newVec[6] == 19);
    }

    SECTION("Add Scalar") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};

        vecn<7> newVec = lh + 5;
        REQUIRE(newVec[0] == 10);
        REQUIRE(newVec[1] == 11);
        REQUIRE(newVec[2] == 12);
        REQUIRE(newVec[3] == 13);
        REQUIRE(newVec[4] == 14);
        REQUIRE(newVec[5] == 15);
        REQUIRE(newVec[6] == 16);
    }

    SECTION("Add Vector in Place") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        lh += rh;
        REQUIRE(lh[0] == 7);
        REQUIRE(lh[1] == 9);
        REQUIRE(lh[2] == 11);
        REQUIRE(lh[3] == 13);
        REQUIRE(lh[4] == 15);
        REQUIRE(lh[5] == 17);
        REQUIRE(lh[6] == 19);
    }

    SECTION("Add Scalar In Place") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};

        lh += 5;
        REQUIRE(lh[0] == 10);
        REQUIRE(lh[1] == 11);
        REQUIRE(lh[2] == 12);
        REQUIRE(lh[3] == 13);
        REQUIRE(lh[4] == 14);
        REQUIRE(lh[5] == 15);
        REQUIRE(lh[6] == 16);
    }
}

/* -------------------------------------------- */
/*  Subtraction                                 */
/* -------------------------------------------- */

TEST_CASE("Vec2 Minus", "[DatMaths, Vector, Vec2, Minus]") {
    SECTION("Minus Vector") {
        vec2 lh{5, 6};
        vec2 rh{2, 3};

        vec2 newVec = lh - rh;
        REQUIRE(newVec.x == 3);
        REQUIRE(newVec.y == 3);
    }

    SECTION("Minus Scalar") {
        vec2 lh{5, 6};

        vec2 newVec = lh - 5;
        REQUIRE(newVec.x == 0);
        REQUIRE(newVec.y == 1);
    }

    SECTION("Minus Vector in Place") {
        vec2 lh{5, 6};
        vec2 rh{2, 3};

        lh -= rh;
        REQUIRE(lh.x == 3);
        REQUIRE(lh.y == 3);
    }

    SECTION("Minus Scalar In Place") {
        vec2 lh{5, 6};

        lh -= 5;
        REQUIRE(lh.x == 0);
        REQUIRE(lh.y == 1);
    }
}

TEST_CASE("Vec1 Minus", "[DatMaths, Vector, Vec1, Minus]") {
    SECTION("Minus Vector") {
        vec1 lh{5};
        vec1 rh{2};

        vec1 newVec = lh - rh;
        REQUIRE(newVec.x == 3);
    }

    SECTION("Minus Scalar") {
        vec1 lh{5};

        vec1 newVec = lh - 5;
        REQUIRE(newVec.x == 0);
    }

    SECTION("Minus Vector in Place") {
        vec1 lh{5};
        vec1 rh{2};

        lh -= rh;
        REQUIRE(lh.x == 3);
    }

    SECTION("Minus Scalar In Place") {
        vec1 lh{5};

        lh -= 5;
        REQUIRE(lh.x == 0);
    }
}

TEST_CASE("Vec3 Minus", "[DatMaths, Vector, Vec3, Minus]") {
    SECTION("Minus Vector") {
        vec3 lh{5, 6, 7};
        vec3 rh{2, 3, 4};

        vec3 newVec = lh - rh;
        REQUIRE(newVec.x == 3);
        REQUIRE(newVec.y == 3);
        REQUIRE(newVec.z == 3);
    }

    SECTION("Minus Scalar") {
        vec3 lh{5, 6, 7};

        vec3 newVec = lh - 5;
        REQUIRE(newVec.x == 0);
        REQUIRE(newVec.y == 1);
        REQUIRE(newVec.z == 2);
    }

    SECTION("Minus Vector in Place") {
        vec3 lh{5, 6, 7};
        vec3 rh{2, 3, 4};

        lh -= rh;
        REQUIRE(lh.x == 3);
        REQUIRE(lh.y == 3);
        REQUIRE(lh.z == 3);
    }

    SECTION("Minus Scalar In Place") {
        vec3 lh{5, 6, 7};

        lh -= 5;
        REQUIRE(lh.x == 0);
        REQUIRE(lh.y == 1);
        REQUIRE(lh.z == 2);
    }
}

TEST_CASE("Vec4 Minus", "[DatMaths, Vector, Vec4, Minus]") {
    SECTION("Minus Vector") {
        vec4 lh{5, 6, 7, 8};
        vec4 rh{2, 3, 4, 5};

        vec4 newVec = lh - rh;
        REQUIRE(newVec.x == 3);
        REQUIRE(newVec.y == 3);
        REQUIRE(newVec.z == 3);
        REQUIRE(newVec.w == 3);
    }

    SECTION("Minus Scalar") {
        vec4 lh{5, 6, 7, 8};

        vec4 newVec = lh - 5;
        REQUIRE(newVec.x == 0);
        REQUIRE(newVec.y == 1);
        REQUIRE(newVec.z == 2);
        REQUIRE(newVec.w == 3);
    }

    SECTION("Minus Vector in Place") {
        vec4 lh{5, 6, 7, 8};
        vec4 rh{2, 3, 4, 5};

        lh -= rh;
        REQUIRE(lh.x == 3);
        REQUIRE(lh.y == 3);
        REQUIRE(lh.z == 3);
        REQUIRE(lh.w == 3);
    }

    SECTION("Minus Scalar In Place") {
        vec4 lh{5, 6, 7, 8};

        lh -= 5;
        REQUIRE(lh.x == 0);
        REQUIRE(lh.y == 1);
        REQUIRE(lh.z == 2);
        REQUIRE(lh.w == 3);
    }
}

TEST_CASE("Vecn Minus", "[DatMaths, Vector, Vecn, Minus]") {
    SECTION("Minus Vector") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        vecn<7> newVec = lh - rh;
        REQUIRE(newVec[0] == 3);
        REQUIRE(newVec[1] == 3);
        REQUIRE(newVec[2] == 3);
        REQUIRE(newVec[3] == 3);
        REQUIRE(newVec[4] == 3);
        REQUIRE(newVec[5] == 3);
        REQUIRE(newVec[6] == 3);
    }

    SECTION("Minus Scalar") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};

        vecn<7> newVec = lh - 5;
        REQUIRE(newVec[0] == 0);
        REQUIRE(newVec[1] == 1);
        REQUIRE(newVec[2] == 2);
        REQUIRE(newVec[3] == 3);
        REQUIRE(newVec[4] == 4);
        REQUIRE(newVec[5] == 5);
        REQUIRE(newVec[6] == 6);
    }

    SECTION("Minus Vector in Place") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        lh -= rh;
        REQUIRE(lh[0] == 3);
        REQUIRE(lh[1] == 3);
        REQUIRE(lh[2] == 3);
        REQUIRE(lh[3] == 3);
        REQUIRE(lh[4] == 3);
        REQUIRE(lh[5] == 3);
        REQUIRE(lh[6] == 3);
    }

    SECTION("Minus Scalar In Place") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};

        lh -= 5;
        REQUIRE(lh[0] == 0);
        REQUIRE(lh[1] == 1);
        REQUIRE(lh[2] == 2);
        REQUIRE(lh[3] == 3);
        REQUIRE(lh[4] == 4);
        REQUIRE(lh[5] == 5);
        REQUIRE(lh[6] == 6);
    }
}

/* -------------------------------------------- */
/*  Negation                                    */
/* -------------------------------------------- */

TEST_CASE("Vec2 Negate", "[DatMaths, Vector, Vec2, Negate]") {
    SECTION("Minus Vector") {
        vec2 lh{5, -6};

        vec2 newVec = -lh;
        REQUIRE(newVec.x == -5);
        REQUIRE(newVec.y == 6);
    }
}

TEST_CASE("Vec1 Negate", "[DatMaths, Vector, Vec1, Negate]") {
    SECTION("Minus Vector") {
        vec1 lh{5};

        vec1 newVec = -lh;
        REQUIRE(newVec.x == -5);
    }
}

TEST_CASE("Vec3 Negate", "[DatMaths, Vector, Vec3, Negate]") {
    vec3 lh{5, -6, 7};

    vec3 newVec = -lh;
    REQUIRE(newVec.x == -5);
    REQUIRE(newVec.y == 6);
    REQUIRE(newVec.z == -7);

}

TEST_CASE("Vec4 Negate", "[DatMaths, Vector, Vec4, Negate]") {
    vec4 lh{5, -6, 7, -8};

    vec4 newVec = -lh;
    REQUIRE(newVec.x == -5);
    REQUIRE(newVec.y == 6);
    REQUIRE(newVec.z == -7);
    REQUIRE(newVec.w == 8);
}

TEST_CASE("Vecn Negate", "[DatMaths, Vector, Vecn, Negate]") {
    vecn<7> lh{5.f, -6.f, 7.f, -8.f, 9.f, -10.f, 11.f};

    vecn<7> newVec = -lh;
    REQUIRE(newVec[0] == -5);
    REQUIRE(newVec[1] == 6);
    REQUIRE(newVec[2] == -7);
    REQUIRE(newVec[3] == 8);
    REQUIRE(newVec[4] == -9);
    REQUIRE(newVec[5] == 10);
    REQUIRE(newVec[6] == -11);
}

/* -------------------------------------------- */
/*  Multiplication                              */
/* -------------------------------------------- */

TEST_CASE("Vec1 Multiply", "[DatMaths, Vector, Vec1, Multiply]") {
    SECTION("Multiply Vector") {
        vec1 lh{5};
        vec1 rh{2};

        vec1 newVec = lh * rh;
        REQUIRE(newVec.x == 10);
    }

    SECTION("Multiply Scalar") {
        vec1 lh{5};

        vec1 newVec = lh * 5;
        REQUIRE(newVec.x == 25);
    }

    SECTION("Multiply Vector in Place") {
        vec1 lh{5};
        vec1 rh{2};

        lh *= rh;
        REQUIRE(lh.x == 10);
    }

    SECTION("Multiply Scalar In Place") {
        vec1 lh{5};

        lh *= 5;
        REQUIRE(lh.x == 25);
    }
}

TEST_CASE("Vec2 Multiply", "[DatMaths, Vector, Vec2, Multiply]") {
    SECTION("Multiply Vector") {
        vec2 lh{5, 6};
        vec2 rh{2, 3};

        vec2 newVec = lh * rh;
        REQUIRE(newVec.x == 10);
        REQUIRE(newVec.y == 18);
    }

    SECTION("Multiply Scalar") {
        vec2 lh{5, 6};

        vec2 newVec = lh * 5;
        REQUIRE(newVec.x == 25);
        REQUIRE(newVec.y == 30);
    }

    SECTION("Multiply Vector in Place") {
        vec2 lh{5, 6};
        vec2 rh{2, 3};

        lh *= rh;
        REQUIRE(lh.x == 10);
        REQUIRE(lh.y == 18);
    }

    SECTION("Multiply Scalar In Place") {
        vec2 lh{5, 6};

        lh *= 5;
        REQUIRE(lh.x == 25);
        REQUIRE(lh.y == 30);
    }
}

TEST_CASE("Vec3 Multiply", "[DatMaths, Vector, Vec3, Multiply]") {
    SECTION("Multiply Vector") {
        vec3 lh{5, 6, 7};
        vec3 rh{2, 3, 4};

        vec3 newVec = lh * rh;
        REQUIRE(newVec.x == 10);
        REQUIRE(newVec.y == 18);
        REQUIRE(newVec.z == 28);
    }

    SECTION("Multiply Scalar") {
        vec3 lh{5, 6, 7};

        vec3 newVec = lh * 5;
        REQUIRE(newVec.x == 25);
        REQUIRE(newVec.y == 30);
        REQUIRE(newVec.z == 35);
    }

    SECTION("Multiply Vector in Place") {
        vec3 lh{5, 6, 7};
        vec3 rh{2, 3, 4};

        lh *= rh;
        REQUIRE(lh.x == 10);
        REQUIRE(lh.y == 18);
        REQUIRE(lh.z == 28);
    }

    SECTION("Multiply Scalar In Place") {
        vec3 lh{5, 6, 7};

        lh *= 5;
        REQUIRE(lh.x == 25);
        REQUIRE(lh.y == 30);
        REQUIRE(lh.z == 35);
    }
}

TEST_CASE("Vec4 Multiply", "[DatMaths, Vector, Vec4, Multiply]") {
    SECTION("Multiply Vector") {
        vec4 lh{5, 6, 7, 8};
        vec4 rh{2, 3, 4, 5};

        vec4 newVec = lh * rh;
        REQUIRE(newVec.x == 10);
        REQUIRE(newVec.y == 18);
        REQUIRE(newVec.z == 28);
        REQUIRE(newVec.w == 40);
    }

    SECTION("Multiply Scalar") {
        vec4 lh{5, 6, 7, 8};

        vec4 newVec = lh * 5;
        REQUIRE(newVec.x == 25);
        REQUIRE(newVec.y == 30);
        REQUIRE(newVec.z == 35);
        REQUIRE(newVec.w == 40);
    }

    SECTION("Multiply Vector in Place") {
        vec4 lh{5, 6, 7, 8};
        vec4 rh{2, 3, 4, 5};

        lh *= rh;
        REQUIRE(lh.x == 10);
        REQUIRE(lh.y == 18);
        REQUIRE(lh.z == 28);
        REQUIRE(lh.w == 40);
    }

    SECTION("Multiply Scalar In Place") {
        vec4 lh{5, 6, 7, 8};

        lh *= 5;
        REQUIRE(lh.x == 25);
        REQUIRE(lh.y == 30);
        REQUIRE(lh.z == 35);
        REQUIRE(lh.w == 40);
    }
}

TEST_CASE("Vecn Multiply", "[DatMaths, Vector, Vecn, Multiply]") {
    SECTION("Multiply Vector") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        vecn<7> newVec = lh * rh;
        REQUIRE(newVec[0] == 10);
        REQUIRE(newVec[1] == 18);
        REQUIRE(newVec[2] == 28);
        REQUIRE(newVec[3] == 40);
        REQUIRE(newVec[4] == 54);
        REQUIRE(newVec[5] == 70);
        REQUIRE(newVec[6] == 88);
    }

    SECTION("Multiply Scalar") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};

        vecn<7> newVec = lh * 5;
        REQUIRE(newVec[0] == 25);
        REQUIRE(newVec[1] == 30);
        REQUIRE(newVec[2] == 35);
        REQUIRE(newVec[3] == 40);
        REQUIRE(newVec[4] == 45);
        REQUIRE(newVec[5] == 50);
        REQUIRE(newVec[6] == 55);
    }

    SECTION("Multiply Vector in Place") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        lh *= rh;
        REQUIRE(lh[0] == 10);
        REQUIRE(lh[1] == 18);
        REQUIRE(lh[2] == 28);
        REQUIRE(lh[3] == 40);
        REQUIRE(lh[4] == 54);
        REQUIRE(lh[5] == 70);
        REQUIRE(lh[6] == 88);
    }

    SECTION("Multiply Scalar In Place") {
        vecn<7> lh{5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f};

        lh *= 5;
        REQUIRE(lh[0] == 25);
        REQUIRE(lh[1] == 30);
        REQUIRE(lh[2] == 35);
        REQUIRE(lh[3] == 40);
        REQUIRE(lh[4] == 45);
        REQUIRE(lh[5] == 50);
        REQUIRE(lh[6] == 55);
    }
}

/* -------------------------------------------- */
/*  Division                                    */
/* -------------------------------------------- */

TEST_CASE("Vec1 Divide", "[DatMaths, Vector, Vec1, Divide]") {
    SECTION("Divide Vector") {
        vec1 lh{4};
        vec1 rh{2};

        vec1 newVec = lh / rh;
        REQUIRE(newVec.x == 2);
    }

    SECTION("Divide Scalar") {
        vec1 lh{25};

        vec1 newVec = lh / 5;
        REQUIRE(newVec.x == 5);
    }

    SECTION("Divide Vector in Place") {
        vec1 lh{4};
        vec1 rh{2};

        lh /= rh;
        REQUIRE(lh.x == 2);
    }

    SECTION("Divide Scalar In Place") {
        vec1 lh{25};

        lh /= 5;
        REQUIRE(lh.x == 5);
    }
}

TEST_CASE("Vec2 Divide", "[DatMaths, Vector, Vec2, Divide]") {
    SECTION("Divide Vector") {
        vec2 lh{4, 30};
        vec2 rh{2, 5};

        vec2 newVec = lh / rh;
        REQUIRE(newVec.x == 2);
        REQUIRE(newVec.y == 6);
    }

    SECTION("Divide Scalar") {
        vec2 lh{25, 30};

        vec2 newVec = lh / 5;
        REQUIRE(newVec.x == 5);
        REQUIRE(newVec.y == 6);
    }

    SECTION("Divide Vector in Place") {
        vec2 lh{4, 30};
        vec2 rh{2, 5};

        lh /= rh;
        REQUIRE(lh.x == 2);
        REQUIRE(lh.y == 6);
    }

    SECTION("Divide Scalar In Place") {
        vec2 lh{25, 30};

        lh /= 5;
        REQUIRE(lh.x == 5);
        REQUIRE(lh.y == 6);
    }
}

TEST_CASE("Vec3 Divide", "[DatMaths, Vector, Vec3, Divide]") {
    SECTION("Divide Vector") {
        vec3 lh{10, 18, 28};
        vec3 rh{2, 3, 4};

        vec3 newVec = lh / rh;
        REQUIRE(newVec.x == 5);
        REQUIRE(newVec.y == 6);
        REQUIRE(newVec.z == 7);
    }

    SECTION("Divide Scalar") {
        vec3 lh{25, 30, 35};

        vec3 newVec = lh / 5;
        REQUIRE(newVec.x == 5);
        REQUIRE(newVec.y == 6);
        REQUIRE(newVec.z == 7);
    }

    SECTION("Divide Vector in Place") {
        vec3 lh{10, 18, 28};
        vec3 rh{2, 3, 4};

        lh /= rh;
        REQUIRE(lh.x == 5);
        REQUIRE(lh.y == 6);
        REQUIRE(lh.z == 7);
    }

    SECTION("Divide Scalar In Place") {
        vec3 lh{25, 30, 35};

        lh /= 5;
        REQUIRE(lh.x == 5);
        REQUIRE(lh.y == 6);
        REQUIRE(lh.z == 7);
    }
}

TEST_CASE("Vec4 Divide", "[DatMaths, Vector, Vec4, Divide]") {
    SECTION("Divide Vector") {
        vec4 lh{10, 18, 28, 40};
        vec4 rh{2, 3, 4, 5};

        vec4 newVec = lh / rh;
        REQUIRE(newVec.x == 5);
        REQUIRE(newVec.y == 6);
        REQUIRE(newVec.z == 7);
        REQUIRE(newVec.w == 8);
    }

    SECTION("Divide Scalar") {
        vec4 lh{25, 30, 35, 40};

        vec4 newVec = lh / 5;
        REQUIRE(newVec.x == 5);
        REQUIRE(newVec.y == 6);
        REQUIRE(newVec.z == 7);
        REQUIRE(newVec.w == 8);
    }

    SECTION("Divide Vector in Place") {
        vec4 lh{10, 18, 28, 40};
        vec4 rh{2, 3, 4, 5};

        lh /= rh;
        REQUIRE(lh.x == 5);
        REQUIRE(lh.y == 6);
        REQUIRE(lh.z == 7);
        REQUIRE(lh.w == 8);
    }

    SECTION("Divide Scalar In Place") {
        vec4 lh{25, 30, 35, 40};

        lh /= 5;
        REQUIRE(lh.x == 5);
        REQUIRE(lh.y == 6);
        REQUIRE(lh.z == 7);
        REQUIRE(lh.w == 8);
    }
}

TEST_CASE("Vecn Divide", "[DatMaths, Vector, Vecn, Divide]") {
    SECTION("Divide Vector") {
        vecn<7> lh{10.f, 18.f, 28.f, 40.f, 54.f, 70.f, 88.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        vecn<7> newVec = lh / rh;
        REQUIRE(newVec[0] == 5);
        REQUIRE(newVec[1] == 6);
        REQUIRE(newVec[2] == 7);
        REQUIRE(newVec[3] == 8);
        REQUIRE(newVec[4] == 9);
        REQUIRE(newVec[5] == 10);
        REQUIRE(newVec[6] == 11);
    }

    SECTION("Divide Scalar") {
        vecn<7> lh{25.f, 30.f, 35.f, 40.f, 45.f, 50.f, 55.f};

        vecn<7> newVec = lh / 5;
        REQUIRE(newVec[0] == 5);
        REQUIRE(newVec[1] == 6);
        REQUIRE(newVec[2] == 7);
        REQUIRE(newVec[3] == 8);
        REQUIRE(newVec[4] == 9);
        REQUIRE(newVec[5] == 10);
        REQUIRE(newVec[6] == 11);
    }

    SECTION("Divide Vector in Place") {
        vecn<7> lh{10.f, 18.f, 28.f, 40.f, 54.f, 70.f, 88.f};
        vecn<7> rh{2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

        lh /= rh;
        REQUIRE(lh[0] == 5);
        REQUIRE(lh[1] == 6);
        REQUIRE(lh[2] == 7);
        REQUIRE(lh[3] == 8);
        REQUIRE(lh[4] == 9);
        REQUIRE(lh[5] == 10);
        REQUIRE(lh[6] == 11);
    }

    SECTION("Divide Scalar In Place") {
        vecn<7> lh{25.f, 30.f, 35.f, 40.f, 45.f, 50.f, 55.f};

        lh /= 5;
        REQUIRE(lh[0] == 5);
        REQUIRE(lh[1] == 6);
        REQUIRE(lh[2] == 7);
        REQUIRE(lh[3] == 8);
        REQUIRE(lh[4] == 9);
        REQUIRE(lh[5] == 10);
        REQUIRE(lh[6] == 11);
    }
}

/* -------------------------------------------- */
/*  Dot Product                                 */
/* -------------------------------------------- */

TEST_CASE("Vec1 Dot Product", "[DatMaths, Vector, Vec1, Dot Product]") {
    SECTION("Basic") {
        vec1 lh(1);
        vec1 rh(3);
        REQUIRE(lh.dotProduct(rh) == 3);
    }

    SECTION("Negative") {
        vec1 lh(-2);
        vec1 rh(1);
        REQUIRE(lh.dotProduct(rh) == -2);
    }

    SECTION("Zero Vector") {
        vec1 lh(0);
        vec1 rh(6);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Large Difference") {
        vec1 lh(1000);
        vec1 rh(.5f);
        REQUIRE(lh.dotProduct(rh) == 500);
    }
}

TEST_CASE("Vec2 Dot Product", "[DatMaths, Vector, Vec2, Dot Product]") {
    SECTION("Basic") {
        vec2 lh(1, 2);
        vec2 rh(3, 4);
        REQUIRE(lh.dotProduct(rh) == 11);
    }

    SECTION("Orthogonal") {
        vec2 lh(1, 0);
        vec2 rh(0, 1);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Parallel") {
        vec2 lh(2, 3);
        vec2 rh(4, 6);
        REQUIRE(lh.dotProduct(rh) == 26);
    }

    SECTION("Negative") {
        vec2 lh(-2, -3);
        vec2 rh(1, 1);
        REQUIRE(lh.dotProduct(rh) == -5);
    }

    SECTION("Zero Vector") {
        vec2 lh(0, 0);
        vec2 rh(6, 5);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Large Difference") {
        vec2 lh(1000, 2000);
        vec2 rh(.5f, .25f);
        REQUIRE(lh.dotProduct(rh) == 1000);
    }
}

TEST_CASE("Vec3 Dot Product", "[DatMaths, Vector, Vec3, Dot Product]") {
    SECTION("Basic") {
        vec3 lh(1, 2, 3);
        vec3 rh(4, 5, 6);
        REQUIRE(lh.dotProduct(rh) == 32);
    }

    SECTION("Orthogonal") {
        vec3 lh(1, 0, 0);
        vec3 rh(0, 1, 0);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Parallel") {
        vec3 lh(3, 2, 1);
        vec3 rh(6, 4, 2);
        REQUIRE(lh.dotProduct(rh) == 28);
    }

    SECTION("Negative") {
        vec3 lh(-2, -3, -4);
        vec3 rh(1, 1, 1);
        REQUIRE(lh.dotProduct(rh) == -9);
    }

    SECTION("Zero Vector") {
        vec3 lh(0, 0, 0);
        vec3 rh(6, 5, 7);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Large Difference") {
        vec3 lh(1000, 2000, 3000);
        vec3 rh(.5f, .25f, .1f);
        REQUIRE(lh.dotProduct(rh) == 1300);
    }
}

TEST_CASE("Vec4 Dot Product", "[DatMaths, Vector, Vec4, Dot Product]") {
    SECTION("Basic") {
        vec4 lh(1, 2, 3, 4);
        vec4 rh(5, 6, 7, 8);
        REQUIRE(lh.dotProduct(rh) == 70);
    }

    SECTION("Orthogonal") {
        vec4 lh(1, 0, 0, 0);
        vec4 rh(0, 1, 0, 0);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Parallel") {
        vec4 lh(2, 3, 4, 5);
        vec4 rh(4, 6, 8, 10);
        REQUIRE(lh.dotProduct(rh) == 108);
    }

    SECTION("Negative") {
        vec4 lh(-2, -3, -4, -5);
        vec4 rh(1, 1, 1, 1);
        REQUIRE(lh.dotProduct(rh) == -14);
    }

    SECTION("Zero Vector") {
        vec4 lh(0, 0, 0, 0);
        vec4 rh(5, 6, 7, 8);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Large Difference") {
        vec4 lh(1000, 2000, 3000, 4000);
        vec4 rh(.5f, .25f, .1f, 0.05f);
        REQUIRE(lh.dotProduct(rh) == 1500);
    }
}

TEST_CASE("Vecn Dot Product", "[DatMaths, Vector, Vecn, Dot Product]") {
    SECTION("Basic") {
        vecn<7> lh(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
        vecn<7> rh(8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f);
        REQUIRE(lh.dotProduct(rh) == 336);
    }

    SECTION("Orthogonal") {
        vecn<7> lh(1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
        vecn<7> rh(0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Parallel") {
        vecn<7> lh(2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
        vecn<7> rh(4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f);
        REQUIRE(lh.dotProduct(rh) == 406);
    }

    SECTION("Negative") {
        vecn<7> lh(-2.f, -3.f, -4.f, -5.f, -6.f, -7.f, -8.f);
        vecn<7> rh(1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f);
        REQUIRE(lh.dotProduct(rh) == -35);
    }

    SECTION("Zero Vector") {
        vecn<7> lh(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
        vecn<7> rh(5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f);
        REQUIRE(lh.dotProduct(rh) == 0);
    }

    SECTION("Large Difference") {
        vecn<7> lh(1000.f, 2000.f, 3000.f, 4000.f, 5000.f, 6000.f, 7000.f);
        vecn<7> rh(0.5f, 0.25f, 0.1f, 0.05f, 0.01f, 0.001f, 0.0001f);
        REQUIRE(lh.dotProduct(rh) == Catch::Approx(1556.7));
    }
}

/* -------------------------------------------- */
/*  Cross Product                               */
/* -------------------------------------------- */

TEST_CASE("Vec3 Cross Product", "[DatMaths, Vector, Vec3, Cross Product]") {
    SECTION("Basic") {
        vec3 lh(1, 0, 0);
        vec3 rh(0, 1, 0);

        vec3 result = lh.crossProduct(rh);
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 0);
        REQUIRE(result.z == 1);

        result = rh.crossProduct(lh);
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 0);
        REQUIRE(result.z == -1);
    }

    SECTION("Non-Parallel") {
        vec3 lh(2, 3, 4);
        vec3 rh(5, 6, 7);

        vec3 result = lh.crossProduct(rh);
        REQUIRE(result.x == -3);
        REQUIRE(result.y == 6);
        REQUIRE(result.z == -3);

        result = rh.crossProduct(lh);
        REQUIRE(result.x == 3);
        REQUIRE(result.y == -6);
        REQUIRE(result.z == 3);
    }

    SECTION("Negative") {
        vec3 lh(-2, -3, -4);
        vec3 rh(1, 1, 1);

        vec3 result = lh.crossProduct(rh);
        REQUIRE(result.x == 1);
        REQUIRE(result.y == -2);
        REQUIRE(result.z == 1);

        result = rh.crossProduct(lh);
        REQUIRE(result.x == -1);
        REQUIRE(result.y == 2);
        REQUIRE(result.z == -1);
    }

    SECTION("Parallel") {
        vec3 lh(2, 0, 0);
        vec3 rh(4, 0, 0);

        vec3 result = lh.crossProduct(rh);
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 0);
        REQUIRE(result.z == 0);
    }

    SECTION("Orthogonal") {
        vec3 lh(1, 0, 0);
        vec3 rh(0, 0, 1);

        vec3 result = lh.crossProduct(rh);
        REQUIRE(result.x == 0);
        REQUIRE(result.y == -1);
        REQUIRE(result.z == 0);

        result = rh.crossProduct(lh);
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 1);
        REQUIRE(result.z == 0);
    }

    SECTION("Large Difference") {
        vec3 lh(1000, 2000, 3000);
        vec3 rh(.5f, .25f, .1f);

        vec3 result = lh.crossProduct(rh);
        REQUIRE(result.x == -550);
        REQUIRE(result.y == 1400);
        REQUIRE(result.z == -750);

        result = rh.crossProduct(lh);
        REQUIRE(result.x == 550);
        REQUIRE(result.y == -1400);
        REQUIRE(result.z == 750);
    }

    SECTION("Zero Vector") {
        vec3 lh(0, 0, 0);
        vec3 rh(5, 6, 7);

        vec3 result = lh.crossProduct(rh);
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 0);
        REQUIRE(result.z == 0);
    }
}

/* -------------------------------------------- */
/*  Length                                      */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Length Squared                              */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Normalise                                   */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Normalised                                  */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Perpendicular                               */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Equal Operator                              */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Equal tolerance                             */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Not Equal                                   */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Greater than                                */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Greater or equal                            */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Less than                                   */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  Less or equal                               */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  UFO                                         */
/* -------------------------------------------- */

/* -------------------------------------------- */
/*  To String                                   */
/* -------------------------------------------- */