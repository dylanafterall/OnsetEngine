# ------------------------------------------------------------------------------
# Onset Engine
# https://github.com/dylanafterall/OnsetEngine
# ------------------------------------------------------------------------------

# cmake --version
cmake_minimum_required(VERSION 3.24.1)

# set project name
project(OnsetEngine)

# set c++ language standard (for gcc and clang)
# EnTT requires at least C++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Create the executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core_game.cpp
    src/core_window.cpp
    src/core_assetmanager.cpp
)

find_package(OpenGL REQUIRED)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIRS}
)

add_subdirectory(external/box2d)
add_subdirectory(external/glad)
add_subdirectory(external/entt)
add_subdirectory(external/glm)
add_subdirectory(external/googletest)
add_subdirectory(external/lua)
add_subdirectory(external/sol2)
add_subdirectory(external/spdlog)
add_subdirectory(external/stb)

# set the directories to INCLUDE in build command
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/external/box2d/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/box2d/extern
    PUBLIC ${PROJECT_SOURCE_DIR}/external/box2d/extern/glfw/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/glad/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/entt/src
    PUBLIC ${PROJECT_SOURCE_DIR}/external/glm
    PUBLIC ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/lua/lua/lua-5.4.4/src
    PUBLIC ${PROJECT_SOURCE_DIR}/external/sol2/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/spdlog/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/stb
)

target_link_libraries(${PROJECT_NAME}
    box2d
    EnTT
    sub_glad
    glfw
    glm
    gtest
    imgui
    lua
    sol2
    spdlog
    stb
    OpenGL::GL
)