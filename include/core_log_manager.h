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
#include "spdlog/sinks/rotating_file_sink.h"

#include <memory>

/** 
 * \brief   The LogManager class.
 * \details Provides abstraction between the spdlog external logging library,
 *          and Onset Engine logging commands. Sets up spdlog sinks and 
 *          loggers.
 */
class LogManager {
public:
    /**
     * \brief   The default constructor. 
     */
    LogManager() = default;
    /**
     * \brief   The default destructor. 
     */
    ~LogManager() = default;

    /**
     * \brief   The function initialize. 
     * \details This function creates 2 spdlog sinks: a console sink and a 
     *          rotating file sink. Both of these sinks are bundled into a 
     *          single spdlog logger, which is then used (via macros in
     *          the core_log_macros.h file) by the Onset Engine.
     * \return  void, none.
     */
    void initialize();
    /**
     * \brief   The function destroy. 
     * \details This function calls on spdlog's shutdown function to delete
     *          the spdlog sinks and logger created by the initialize function.
     * \return  void, none.
     */
    void destroy();
};

#endif // CORE_LOG_MANAGER_H