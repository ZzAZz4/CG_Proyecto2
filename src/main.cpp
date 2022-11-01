#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLWindow.h"
#include "Texture.h"
#include "Player.h"
#include "ShaderProgram.h"
#include "Time.h"
#include "Chunk.h"
#include <memory>

void Render ();

std::unique_ptr<GLWindow> window;
std::unique_ptr<ShaderProgram> shader;
std::unique_ptr<Texture2D> texture;
std::unique_ptr<World> world;
Player player;

void Update () {
    Time::Update();
    world->Update();
    player.Update(world.get());
}

void OnResize (void*, i32 width, i32 height) {
    player.OnResize(width, height);
}

void OnKeyPressed (void*, i32 key, i32 scancode, i32 action, i32 mods) {
    if (action == GLFW_REPEAT) return;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) window->Close();
    player.OnKeyPress(key, scancode, action, mods);
}

void OnMouseMove (void*, f64 xposd, f64 yposd) {
    player.OnMouseMove(xposd, yposd);
}

void OnMouseScroll (void*, f64 xoffset, f64 yoffset) {
    player.OnMouseScroll(xoffset, yoffset);
}


int main () {
    window = std::make_unique<GLWindow>(
        800, 600, "LearnOpenGL", WindowCallbackInfo{
            .userData = nullptr,
            .keyCallback = OnKeyPressed,
            .mouseMoveCallback = OnMouseMove,
            .mouseScrollCallback = OnMouseScroll,
            .resizeCallback = OnResize,
        });

    window->SetMouseLock(true);
    window->EnableDepthTest();
    window->EnableCulling(GL_BACK, GL_CW);
    window->clearColor = { 0.4f, 0.6f, 0.9f, 1.0f };


    shader = std::make_unique<ShaderProgram>(
        Shader::FromFile(GL_VERTEX_SHADER, "../res/shaders/minecube_vs.glsl"),
        Shader::FromFile(GL_FRAGMENT_SHADER, "../res/shaders/minecube_fs.glsl"));
    shader->Bind();

    Time::Init();
    Block::Init(*shader, "../res/textures/terrain.png");

   // player.camera.Position = glm::vec3(100,0,100);
    world = std::make_unique<World>();

    OnResize(nullptr, window->Width, window->Height);
    for (int x = 0; x < 2 * Chunk::CHUNK_SIZE; x++) {
        for (int z = 0; z < 2 * Chunk::CHUNK_SIZE; z++) {
            const int y = x / Chunk::CHUNK_SIZE + z / Chunk::CHUNK_SIZE + 1;
            for (int i = 0; i < y; i++) {
                const auto block = i == 0 ? Block::Wood : Block::Grass;
                world->SetBlock(x, i, z, block);
            }
        }
    }
    while (!window->ShouldClose()) {
        window->PollEvents();
        Update();

        window->ClearDisplay();
        Render();

        window->SwapBuffers();
    }

    return 0;
}

void Render () {
    shader->Bind();
//    printf("Position: %f, %f, %f\n", player.camera.Position.x, player.camera.Position.y, player.camera.Position.z);

    shader->setMat4("projection", player.camera.Projection);
    shader->setMat4("view", player.camera.View);

    // chunk
    world->shader = shader.get();
    world->Render();
}




