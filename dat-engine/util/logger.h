/**
 * Not just inspired by, but basically stolen from The Cherno's Hazel Engine
 * https://github.com/TheCherno/Hazel
 * https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Log.h
 * https://www.youtube.com/@TheCherno
 */

#pragma once

#include <string>
#include <spdlog/spdlog.h>

#include <maths/vector/vector-string.h>

class DatLog {
    static std::shared_ptr<spdlog::logger> core;
    static std::shared_ptr<spdlog::logger> game;
public:
    static void init();

    static std::shared_ptr<spdlog::logger>& getCoreLogger();
    static std::shared_ptr<spdlog::logger>& getGameLogger();
};


// Core log macros
// Don't ship debug and trace logs
#ifndef ndebug
    #define CORE_TRACE(...)    ::DatLog::getCoreLogger()->trace(__VA_ARGS__)
    #define CORE_DEBUG(...)    ::DatLog::getCoreLogger()->debug(__VA_ARGS__)
#else
    #define CORE_TRACE(...)
    #define CORE_DEBUG(...)
#endif
#define CORE_INFO(...)     ::DatLog::getCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     ::DatLog::getCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    ::DatLog::getCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::DatLog::getCoreLogger()->critical(__VA_ARGS__)

// Game log macros
// Don't ship debug and trace logs
#ifndef ndebug
    #define LOG_TRACE(...)         ::DatLog::GetGameLogger()->trace(__VA_ARGS__)
    #define LOG_DEBUG(...)         ::DatLog::GetGameLogger()->debug(__VA_ARGS__)
#else
    #define LOG_TRACE(...)
    #define LOG_DEBUG(...)
#endif
#define LOG_INFO(...)          ::DatLog::GetGameLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::DatLog::GetGameLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::DatLog::GetGameLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::DatLog::GetGameLogger()->critical(__VA_ARGS__)