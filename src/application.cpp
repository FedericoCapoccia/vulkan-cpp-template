#include "logging/logger.hpp"
#include <vulkan/vulkan.hpp>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

auto main() -> int
{
    vkrend::Logger::init();
    CORE_INFO("Starting");

    return 0;
}
