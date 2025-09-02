#include "IGpu.h"

#include <util/CVar.h>

using namespace DatEngine;

CVarInt bufferedFramesCVar(
        "IBufferedFrames",
        "The number of frames to buffer in the swap chain",
        CVarCategory::Graphics,
        2,
        CVarFlags::Persistent
);
CVarBool enableVSyncCVar(
        "BEnableVsync",
        "Enable syncing frame dispatch to display refresh",
        CVarCategory::Graphics,
        false,
        CVarFlags::Persistent
);

// Would you believe this is necessary for the above to compile into the program?
void DatGpu::IGpu::initialise() {}
