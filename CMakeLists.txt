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


# ------------------------------------------------------------------------------
# Onset Engine CPP AND H FILES

# create a sources variable with link to cpp files to compile
set(SOURCES
    src/main.cpp
)

# add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# ------------------------------------------------------------------------------
# Automate Git Submodules

# Update submodules as needed
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
        endif()
    endif()
endif()


# ------------------------------------------------------------------------------
# sub-directories (points CMake to these CMakeLists.txt)

add_subdirectory(external/box2d)
add_subdirectory(external/entt)
add_subdirectory(external/glm)
add_subdirectory(external/googletest)
add_subdirectory(external/lua)
add_subdirectory(external/sol2)
add_subdirectory(external/spdlog)
add_subdirectory(external/stb)

# set the directories to INCLUDE in build command (not external libs)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/box2d/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/box2d/extern
    PUBLIC ${PROJECT_SOURCE_DIR}/external/box2d/extern/glad/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/box2d/extern/glfw/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/entt/src
    PUBLIC ${PROJECT_SOURCE_DIR}/external/glm
    PUBLIC ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/lua/lua/lua-5.4.4/src
    PUBLIC ${PROJECT_SOURCE_DIR}/external/sol2/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/spdlog/include
    PUBLIC ${PROJECT_SOURCE_DIR}/external/stb
)


# ------------------------------------------------------------------------------
# OpenGL - 'REQUIRED' stops CMake if OpenGL is not found 
# 	 - OpenGL is dependency, but not in external directory

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})


# ------------------------------------------------------------------------------
# link external libraries

target_link_libraries(${PROJECT_NAME}
    box2d
    EnTT
    glad
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