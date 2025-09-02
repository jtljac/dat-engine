cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
        "Constants.h"
        "CommonMaths.h" "CommonMaths.cpp"
        "Vector.h" "vector/VecForward.h" "vector/Vec1.h" "vector/Vec2.h" "vector/Vec3.h" "vector/Vec4.h" "vector/VecN.h" "vector/VectorString.h"
        "Matrix.h" "matrix/Mat.h"
        "Quaternion.h" "quaternion/Quat.h"
)