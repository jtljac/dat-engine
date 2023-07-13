//
// Created by jacob on 10/07/23.
//

#include "util/logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

// Initialise to nullptr for our asserts
std::shared_ptr<spdlog::logger> DatLog::core = nullptr;
std::shared_ptr<spdlog::logger> DatLog::game = nullptr;

void DatLog::init() {
    std::vector<spdlog::sink_ptr> sinks {
        std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>()
    };

    sinks[0]->set_pattern("%^[%T][%n][%l]: %v%$");


    DatLog::core = std::make_shared<spdlog::logger>("Core", sinks.begin(), sinks.end());
    spdlog::register_logger(DatLog::core);
    DatLog::core->set_level(spdlog::level::trace);
    DatLog::core->flush_on(spdlog::level::trace);

    DatLog::game = std::make_shared<spdlog::logger>("Game", sinks.begin(), sinks.end());
    spdlog::register_logger(DatLog::game);
    DatLog::game->set_level(spdlog::level::trace);
    DatLog::game->flush_on(spdlog::level::trace);

    CORE_INFO("Logger Initialised");
}

std::shared_ptr<spdlog::logger> DatLog::getCoreLogger() {
    assert(DatLog::core != nullptr);
    return DatLog::core;
}

std::shared_ptr<spdlog::logger> DatLog::getGameLogger() {
    assert(DatLog::game != nullptr);
    return DatLog::game;
}
