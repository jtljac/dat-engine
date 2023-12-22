//
// Created by jacob on 28/07/23.
//

#pragma once

#include <maths/vector.h>
#include <maths/quaternion.h>

struct WorldObject {
    WorldObject* parent;

    DatMaths::vec3 position;
    DatMaths::quat rotation;
    DatMaths::vec3 scale;
};