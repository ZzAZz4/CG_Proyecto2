cmake_minimum_required(VERSION 3.23)
project(ogl)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
add_subdirectory(external)

add_executable(ogl src/main.cpp src/GLWindow.h src/types.h src/GLWindow.cpp src/renderObjects.h src/Texture.cpp src/Texture.h src/Player.cpp src/Player.h src/Time.h src/Time.cpp src/ShaderProgram.cpp src/ShaderProgram.h src/Shader.cpp src/Shader.h src/Chunk.cpp src/Chunk.h src/World.cpp src/World.h src/Block.cpp src/Block.h)

target_compile_options(ogl PRIVATE $<$<CXX_COMPILER_ID:MSVC>: /W4 /WX> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic>)
target_link_libraries(ogl PRIVATE OpenGL::GL OpenGL::GLU glfw glad glm assimp stb_image imgui)