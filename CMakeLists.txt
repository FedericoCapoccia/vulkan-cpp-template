cmake_minimum_required(VERSION 3.10)
project(vk-renderer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_executable(${CMAKE_PROJECT_NAME}
    src/application.cpp
    src/logging/logger.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE "src")
target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.hpp")

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    glfw
    fmt::fmt
    spdlog::spdlog
    Vulkan::Vulkan
    GPUOpen::VulkanMemoryAllocator
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    VULKAN_HPP_NO_CONSTRUCTORS
    VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_NO_SPACESHIP_OPERATOR
    VULKAN_HPP_NO_SMART_HANDLE
    VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
    VULKAN_HPP_ASSERT_ON_RESULT=
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "${CMAKE_CXX_FLAGS} /Wall /WX")
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic)
endif ()

#-------------------------------------------------------------------------
# Automatic shaders compiling
# ------------------------------------------------------------------------
find_program(GLSL_VALIDATOR glslangValidator HINTS
    /usr/bin
    /usr/local/bin
    $ENV{VULKAN_SDK}/Bin/
    $ENV{VULKAN_SDK}/Bin32/
)

file(GLOB_RECURSE GLSL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/resources/shaders/*.frag"
        "${PROJECT_SOURCE_DIR}/resources/shaders/*.vert"
        "${PROJECT_SOURCE_DIR}/resources/shaders/*.comp"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
    message(STATUS "BUILDING SHADER")
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_SOURCE_DIR}/resources/shaders/${FILE_NAME}.spv")
    message(STATUS ${GLSL})
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
            DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach()

add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})
add_dependencies(${CMAKE_PROJECT_NAME} Shaders)
