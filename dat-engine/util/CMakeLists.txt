cmake_minimum_required(VERSION 3.22)

configure_file(engine-constants.h.in engine-constants.h @ONLY)

target_sources(dat-engine PRIVATE
        "type-traits.h"
        "logger.h" "source/logger.cpp"
        "cvar.h" "source/cvar.cpp"
        "string-utils.h"
)