#pragma once

namespace DatEngine {
    class Engine;
}

namespace DatEngine::Service {
    class EngineService {
    public:
        virtual ~EngineService() {}

        virtual void preInit() {};
        virtual void init() = 0;
        virtual void postInit() {};
        virtual void tick(float delta){};

        virtual int priority() {
            return 5000;
        }
    };
}