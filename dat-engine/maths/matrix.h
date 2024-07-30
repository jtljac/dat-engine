//
// Created by jacob on 28/07/23.
//

#pragma once

#include <maths/vector.h>
#include "matrix/mat.h"

namespace DatEngine::DatMaths {
    /** A floating point 3x3 Matrix */
    using mat3 = Matrix<3, 3, float>;

    /** A floating point 4x4 Matrix */
    using mat4 = Matrix<4, 4, float>;
}