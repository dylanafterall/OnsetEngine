// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_log_manager.h
//  implementation of LogManager class, used as wrapper for spdlog library 
// -----------------------------------------------------------------------------

#include "core_log_manager.h"

void LogManager::initialize() {
    // make a console sink
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %v%$");
    // make a file sink. keep file size to a maximum of 5MB and a maximum of 3 rotated files.
    auto rotatingFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("../logs/logfile.txt", 1048576 * 5, 3);

    // create vector of sinks, add them to a logger
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(consoleSink);
    sinks.push_back(rotatingFileSink);
    auto logger = std::make_shared<spdlog::logger>(ONSET_DEFAULT_LOGGER_NAME, sinks.begin(), sinks.end());

    // logger settings
    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::trace);
    spdlog::register_logger(logger);
}

void LogManager::destroy() {
    spdlog::shutdown();
}