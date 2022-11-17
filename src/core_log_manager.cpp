// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_log_manager.h
//  implementation of LogManager class, used as wrapper for spdlog library 
// -----------------------------------------------------------------------------

#include "core_log_manager.h"

void LogManager::initialize() {
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %v%$");

    std::vector<spdlog::sink_ptr> sinks {consoleSink};
    auto logger = std::make_shared<spdlog::logger>(ONSET_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());
    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::trace);
    spdlog::register_logger(logger);
}

void LogManager::shutdown() {
    spdlog::shutdown();
}