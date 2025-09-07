#pragma once
#include "service/EngineService.h"

namespace DatEngine::Threading {
    class ThreadManager final : public Service::EngineService {

    public:
        void init() override;
    };
}
