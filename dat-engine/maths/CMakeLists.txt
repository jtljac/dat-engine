cmake_minimum_required(VERSION 3.22)



target_sources(dat-engine PRIVATE
        "numbers.h"
        "common-maths.h" "source/common-maths.cpp"
        "vector.h" "vector/vec-forward.h" "vector/vec1.h" "vector/vec2.h" "vector/vec3.h" "vector/vec4.h" "vector/vecn.h" "vector/vector-string.h"
        "matrix.h" "matrix/mat.h"
        "quaternion.h" "quaternion/quat.h"
)