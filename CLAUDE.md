# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

OpenGL learning project, likely following [LearnOpenGL.com](https://learnopengl.com/) tutorials. The project uses GLFW 3.4 (present as `glfw-3.4.zip`) for window creation and input handling.

## Current State

The repository is in initial setup — no source files or build system exist yet. GLFW has been downloaded but not extracted or integrated.

## Expected Build Setup

When the project is set up, it will likely use CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Key dependencies to expect:
- **GLFW** — windowing and input (`glfw-3.4.zip`)
- **OpenGL** — rendering API (system-provided)
- **GLAD** — OpenGL function loader (typically downloaded separately)
- **GLM** — math library for vectors/matrices
- **stb_image** — image loading (often header-only, included in source)
