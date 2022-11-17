// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_log_manager.h
//  header of LogManager class, used as wrapper for spdlog library 
// -----------------------------------------------------------------------------
#ifndef CORE_LOG_MANAGER_H
#define CORE_LOG_MANAGER_H

#include "core_log_macros.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <memory>

class LogManager {
public:
    LogManager() = default;
    ~LogManager() = default;

    void initialize();
    void shutdown();
};

#endif // CORE_LOG_MANAGER_H