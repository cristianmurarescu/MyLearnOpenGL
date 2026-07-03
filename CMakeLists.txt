cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# GLAD
# ---------------------------------------------------------------------------
add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

# ---------------------------------------------------------------------------
# GLFW
# ---------------------------------------------------------------------------
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.4/glfw-3.4)

# ---------------------------------------------------------------------------
# GLM (header-only, vendored under glm-0.9.8.5/glm)
# Declared as STATIC (compiling glm's aggregate detail/glm.cpp) so the headers
# show up as their own project in the Visual Studio Solution Explorer.
# ---------------------------------------------------------------------------
set(GLM_DIR "${CMAKE_SOURCE_DIR}/glm-0.9.8.5/glm")

file(GLOB_RECURSE GLM_HEADERS CONFIGURE_DEPENDS
    "${GLM_DIR}/glm/*.hpp"
    "${GLM_DIR}/glm/*.h"
    "${GLM_DIR}/glm/*.inl")

add_library(glm STATIC "${GLM_DIR}/glm/detail/glm.cpp" ${GLM_HEADERS})
target_include_directories(glm PUBLIC "${GLM_DIR}")

# Preserve the on-disk folder layout inside the VS project tree.
source_group(TREE "${GLM_DIR}" PREFIX "glm" FILES ${GLM_HEADERS})

# ---------------------------------------------------------------------------
# OpenGL
# ---------------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------
add_executable(LearnOpenGL
    src/main.cpp
    src/Shader.cpp
    src/Shader.h
    src/stb_image.cpp
    src/stb_image.h
    src/lighting_vs.glsl
    src/lighting_fs.glsl
    src/light_vs.glsl
    src/light_fs.glsl)

set_target_properties(LearnOpenGL PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(LearnOpenGL PRIVATE glad glfw glm OpenGL::GL)
