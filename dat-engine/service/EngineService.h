#pragma once

namespace DatEngine {
    class Engine;
}

namespace DatEngine::Service {
    /**
     * Interface for "Engine Services"
     *
     * An engine service is a core component of the engine that has explicit startup, shutdown, and optionally ticking.
     */
    class EngineService {
    public:
        virtual ~EngineService() {}

        /**
         * Called when registering the service.
         *
         * Intended for initial setup, like an explicit constructor.
         *
         * Assume no other services have been registered yet
         */
        virtual void preInit() {};

        /**
         * Called during the service stage of engine initialisation.
         *
         * Assume all services are registered, but no services have initialised yet.
         */
        virtual void init() = 0;

        /**
         * Called at the end of the service stage of engine initialisation.
         *
         * Intended for final setup that depends on other services.
         *
         * Assume all services are set up and ready to access.
         */
        virtual void postInit() {};

        /**
         * Explicitly unload the service before destruction
         *
         * Called during engine teardown.
         */
        virtual void unload() {};

        /**
         * Execute service logic per frame
         *
         * Called every frame at the end of the main loop
         *
         * @param delta The duration of the tick
         */
        virtual void tick(float delta) {};
    };
}