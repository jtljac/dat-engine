#pragma once
#include "util/Exception/DatException.h"

#include <stdexcept>

namespace DatEngine::DatGpu {
    class GpuException : public DatException {
        using DatException::DatException;
    };
} // namespace DatEngine::DatGpu
