#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include <container/sparse-map.h>
#include <maths/vector.h>

using namespace DatEngine;

TEST_CASE("SparseMap Insert", "[Container, SparseMap, Insertion]") {
    SparseMap<DatMaths::vec3> map;

    SECTION("Insert") {
        DatMaths::vec3 inVec{0, 2, 3};
        map.insert(4, inVec);

        REQUIRE(map.contains(4));

        DatMaths::vec3* outVec = map.get(4);

        REQUIRE(&inVec != outVec);
        REQUIRE(inVec == *outVec);
    }

    SECTION("Emplace") {
        DatMaths::vec3 inVec{1, 2, 3};
        map.emplace(5, 1, 2, 3);

        REQUIRE(map.contains(5));

        DatMaths::vec3* outVec = map.get(5);

        REQUIRE(&inVec != outVec);
        REQUIRE(inVec == *outVec);
    }
}