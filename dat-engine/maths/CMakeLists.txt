cmake_minimum_required(VERSION 3.22)



target_sources(dat-engine PRIVATE
        "numbers.h"
        "common-maths.h" "source/common-maths.cpp"
        "vector.h" "vector/vec-forward.h" "vector/vec3.h"
)