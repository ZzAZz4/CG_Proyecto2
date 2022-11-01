cmake_minimum_required(VERSION 3.21)
project(ogl)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
add_subdirectory(external)

add_executable(ogl src/main.cpp src/rendering/GLWindow.h src/rendering/GLWindow.cpp src/rendering/Texture.cpp src/rendering/Texture.h src/game/Player.cpp src/game/Player.h src/game/Time.h src/game/Time.cpp src/rendering/ShaderProgram.cpp src/rendering/ShaderProgram.h src/rendering/Shader.cpp src/rendering/Shader.h src/game/Chunk.cpp src/game/Chunk.h src/game/World.cpp src/game/World.h src/game/Block.cpp src/game/Block.h src/math/ShortRayCast.cpp src/math/ShortRayCast.h src/game/Gui.cpp src/game/Gui.h src/game/PauseMenu.cpp src/game/PauseMenu.h src/game/Scene.cpp src/game/Scene.h src/game/Application.cpp src/game/Application.h src/game/PlayerPhysics.cpp src/game/PlayerPhysics.h)

target_compile_definitions(ogl PRIVATE GLFW_INCLUDE_NONE)
target_compile_options(ogl PRIVATE $<$<CXX_COMPILER_ID:MSVC>: /W4 /WX> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic>)
target_link_libraries(ogl PRIVATE OpenGL::GL OpenGL::GLU glfw glad assimp stb_image imgui
    $<$<PLATFORM_ID:Windows>:glm> $<$<PLATFORM_ID:Linux>:glm::glm>)