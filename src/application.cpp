#include "logging/logger.hpp"
#include <vulkan/vulkan.hpp>

auto main() -> int
{
    vkrend::Logger::init();
    CORE_INFO("Starting");

    return 0;
}
