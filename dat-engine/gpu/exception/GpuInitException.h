#pragma once
#include "GpuException.h"

namespace DatEngine::DatGpu {
    class GpuInitException : public GpuException {
        using GpuException::GpuException;
    };
} // namespace DatEngine::DatGpu
