#include "logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace vkrend {

std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

void Logger::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stdout_color_mt("CORE");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("GAME");
    s_ClientLogger->set_level(spdlog::level::trace);
}

}
