#include "Systems/Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace CylinderBank
{
    std::shared_ptr<spdlog::logger> Log::core_logger;
    std::shared_ptr<spdlog::logger> Log::client_logger;

    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        core_logger = spdlog::stdout_color_st("ENGINE");
        core_logger->set_level(spdlog::level::trace);
        core_logger->trace("Logger initialized");

        client_logger = spdlog::stdout_color_st("CLIENT");
        client_logger->set_level(spdlog::level::trace);
        client_logger->trace("Logger initialized");
    }
}