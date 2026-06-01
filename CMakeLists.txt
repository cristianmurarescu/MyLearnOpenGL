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
    src/vertex_shader.glsl
    src/fragment_shader.glsl)

set_target_properties(LearnOpenGL PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(LearnOpenGL PRIVATE glad glfw OpenGL::GL)
