#pragma once

#include <maths/Vector.h>
#include "matrix/Mat.h"

namespace DatEngine::DatMaths {
    /** A floating point 3x3 Matrix */
    using mat3 = Matrix<3, 3, float>;

    /** A floating point 4x4 Matrix */
    using mat4 = Matrix<4, 4, float>;
} // namespace DatEngine::DatMaths
