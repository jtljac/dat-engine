/**
 * Not just inspired by, but basically stolen from The Cherno's Hazel Engine
 * https://github.com/TheCherno/Hazel
 * https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Log.h
 * https://www.youtube.com/@TheCherno
 */

#pragma once

#include <string>
#include <spdlog/spdlog.h>

namespace DatEngine {
    /**
     * A utility class that encapsulates logging behaviour
     */
    class DatLog {
        /** The logger used for engine logs */
        static std::shared_ptr<spdlog::logger> core;
        /** The logger used for game logs */
        static std::shared_ptr<spdlog::logger> game;
    public:
        static void init();

        /** Get the core logger */
        static std::shared_ptr<spdlog::logger>& getCoreLogger();
        /** Get the game logger */
        static std::shared_ptr<spdlog::logger>& getGameLogger();
    };
}

// Core log macros
// Don't ship debug and trace logs
#ifndef ndebug
#define CORE_TRACE(...)    DatEngine::DatLog::getCoreLogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...)    DatEngine::DatLog::getCoreLogger()->debug(__VA_ARGS__)
#else
#define CORE_TRACE(...)
#define CORE_DEBUG(...)
#endif
#define CORE_INFO(...)     DatEngine::DatLog::getCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     DatEngine::DatLog::getCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    DatEngine::DatLog::getCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) DatEngine::DatLog::getCoreLogger()->critical(__VA_ARGS__)

// Game log macros
// Don't ship debug and trace logs
#ifndef ndebug
#define LOG_TRACE(...)     DatEngine::DatLog::GetGameLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)     DatEngine::DatLog::GetGameLogger()->debug(__VA_ARGS__)
#else
#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#endif
#define LOG_INFO(...)      DatEngine::DatLog::GetGameLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)      DatEngine::DatLog::GetGameLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)     DatEngine::DatLog::GetGameLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)  DatEngine::DatLog::GetGameLogger()->critical(__VA_ARGS__)