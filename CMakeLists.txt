cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL CXX)

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
# GLM (header-only, vendored under glm/include/glm)
# Declared as STATIC with a stub .cpp so the headers show up as their own
# project in the Visual Studio Solution Explorer.
# ---------------------------------------------------------------------------
file(GLOB_RECURSE GLM_HEADERS CONFIGURE_DEPENDS
    "glm/include/glm/*.hpp"
    "glm/include/glm/*.h"
    "glm/include/glm/*.inl")

add_library(glm STATIC glm/src/glm.cpp ${GLM_HEADERS})
target_include_directories(glm PUBLIC glm/include)

# Preserve the on-disk folder layout inside the VS project tree.
source_group(TREE "${CMAKE_SOURCE_DIR}/glm/include" PREFIX "glm" FILES ${GLM_HEADERS})

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
    src/Camera.h
    src/stb_image.cpp
    src/stb_image.h
    src/lighting_vs.glsl
    src/lighting_fs.glsl
    src/light_vs.glsl
    src/light_fs.glsl)

set_target_properties(LearnOpenGL PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(LearnOpenGL PRIVATE glad glfw glm OpenGL::GL)
