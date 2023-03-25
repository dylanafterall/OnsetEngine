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

option(BUILD_DOC "Build documentation" ON)

# PROJECT ----------------------------------------------------------------------
# ------------------------------------------------------------------------------

project(OnsetEngine
    VERSION 0.1.0
    DESCRIPTION "ECS game engine with 2D physics and 3D rendering"
    HOMEPAGE_URL "https://github.com/dylanafterall/OnsetEngine"
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core_game.cpp
    src/core_asset_manager.cpp
    src/core_input_commander.cpp
    src/core_input_invoker.cpp
    src/core_log_manager.cpp
    src/core_window_manager.cpp
    src/core_text_manager.cpp
    src/system_camera.cpp
    src/system_collision.cpp
    src/system_render.cpp
    src/system_player_movement.cpp
    src/system_select_mode.cpp
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
find_package(freetype CONFIG REQUIRED)

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
    PRIVATE freetype
)

# DOCUMENTATION ----------------------------------------------------------------
# ------------------------------------------------------------------------------
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

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