// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_log_macros.h
//  macros to be used by core_log's Log class
// -----------------------------------------------------------------------------
#ifndef CORE_LOG_MACROS_H
#define CORE_LOG_MACROS_H

#include "spdlog/spdlog.h"

#define ONSET_DEFAULT_LOGGER_NAME "OnsetLogger"

// enable logging for debug builds
#ifndef ONSET_CONFIG_RELEASE
#define ONSET_TRACE(...) if(spdlog::get(ONSET_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(ONSET_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#define ONSET_DEBUG(...) if(spdlog::get(ONSET_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(ONSET_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
#define ONSET_INFO(...) if(spdlog::get(ONSET_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(ONSET_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
#define ONSET_WARN(...) if(spdlog::get(ONSET_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(ONSET_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
#define ONSET_ERROR(...) if(spdlog::get(ONSET_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(ONSET_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
#define ONSET_FATAL(...) if(spdlog::get(ONSET_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(ONSET_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}
#else
// disable logging for release builds
#define ONSET_TRACE(...) (void)0
#define ONSET_DEBUG(...) (void)0
#define ONSET_INFO(...) (void)0
#define ONSET_WARN(...) (void)0
#define ONSET_ERROR(...) (void)0
#define ONSET_FATAL(...) (void)0
#endif // ONSET_CONFIG_RELEASE

#endif // CORE_LOG_MACROS_H