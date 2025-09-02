cmake_minimum_required(VERSION 3.22)

configure_file(EngineConstants.h.in EngineConstants.h @ONLY)

target_sources(dat-engine PRIVATE
        "TypeTraits.h"
        "Logger.h" "Logger.cpp"
        "CVar.h" "CVar.cpp"
        "StringUtils.h"
)