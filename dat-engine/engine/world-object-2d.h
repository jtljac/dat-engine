//
// Created by jacob on 28/07/23.
//

#pragma once

#include <maths/vector.h>

struct WorldObject2d {
    WorldObject2d* parent;

    DatMaths::vec2 position;
    float rotation;
    DatMaths::vec2 scale;
};