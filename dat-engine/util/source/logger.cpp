//
// Created by jacob on 10/07/23.
//
#include "util/logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include <maths/vector/vector-string.h>

using namespace DatEngine;

// Initialise to nullptr for our asserts
std::shared_ptr<spdlog::logger> DatLog::core = nullptr;
std::shared_ptr<spdlog::logger> DatLog::game = nullptr;

void DatLog::init() {
    std::vector<spdlog::sink_ptr> sinks {
        std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>()
    };

    sinks[0]->set_pattern("%^[%T][%n][%l]: %v%$");


    core = std::make_shared<spdlog::logger>("Core", sinks.begin(), sinks.end());
    register_logger(core);
    core->set_level(spdlog::level::trace);
    core->flush_on(spdlog::level::trace);

    game = std::make_shared<spdlog::logger>("Game", sinks.begin(), sinks.end());
    register_logger(game);
    game->set_level(spdlog::level::trace);
    game->flush_on(spdlog::level::trace);

    CORE_INFO("Logger Initialised");
}

std::shared_ptr<spdlog::logger>& DatLog::getCoreLogger() {
    assert(DatLog::core != nullptr);
    return core;
}

std::shared_ptr<spdlog::logger>& DatLog::getGameLogger() {
    assert(DatLog::game != nullptr);
    return game;
}
