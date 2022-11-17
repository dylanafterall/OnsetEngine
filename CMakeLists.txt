# ------------------------------------------------------------------------------
# Onset Engine
# https://github.com/dylanafterall/OnsetEngine
# ------------------------------------------------------------------------------

# SETTINGS ---------------------------------------------------------------------
# ------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24.1)

# EnTT requires at least c++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -O0 -Wall -Werror")

set(CMAKE_TOOLCHAIN_FILE 
    ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake 
    CACHE STRING "vcpkg toolchain file"
)

# PROJECT ----------------------------------------------------------------------
# ------------------------------------------------------------------------------

project(OnsetEngine)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core_game.cpp
    src/core_window.cpp
    src/core_asset_manager.cpp
    src/core_input_invoker.cpp
    src/core_input_commander.cpp
    src/core_log_manager.cpp
    src/system_movement.cpp
    src/system_render.cpp
    src/system_camera.cpp
)

find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")

include_directories(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/src
    PRIVATE ${STB_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE glad::glad
    PRIVATE glfw
    PRIVATE glm::glm
    PRIVATE EnTT::EnTT
    PRIVATE box2d::box2d
    PRIVATE spdlog::spdlog
    PRIVATE spdlog::spdlog_header_only
    PRIVATE imgui::imgui
)

# TOOLS ------------------------------------------------------------------------
# ------------------------------------------------------------------------------

add_executable(MeshFormatter
    tools/formatter/main.cpp
    tools/formatter/mesh_formatter.cpp
)
include_directories(MeshFormatter 
    PUBLIC tools/formatter
)
target_link_libraries(MeshFormatter
    PUBLIC glm::glm
)