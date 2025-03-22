#pragma once

#include <spdlog/spdlog.h>

namespace vkrend {

class Logger {
public:
    static void init();

    static std::shared_ptr<spdlog::logger>& get_core()
    {
        return s_CoreLogger;
    }
    static std::shared_ptr<spdlog::logger>& get_client()
    {
        return s_ClientLogger;
    }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}

// Log macros
#define CORE_TRACE(...) vkrend::Logger::get_core()->trace(__VA_ARGS__)
#define CORE_INFO(...) vkrend::Logger::get_core()->info(__VA_ARGS__)
#define CORE_WARN(...) vkrend::Logger::get_core()->warn(__VA_ARGS__)
#define CORE_ERROR(...) vkrend::Logger::get_core()->error(__VA_ARGS__)

/*#define GAME_TRACE(...) vkrend::Logger::get_client()->trace(__VA_ARGS__)*/
/*#define GAME_INFO(...) vkrend::Logger::get_client()->info(__VA_ARGS__)*/
/*#define GAME_WARN(...) vkrend::Logger::get_client()->warn(__VA_ARGS__)*/
/*#define GAME_ERROR(...) vkrend::Logger::get_client()->error(__VA_ARGS__)*/
