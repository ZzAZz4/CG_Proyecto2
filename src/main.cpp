#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLWindow.h"
#include "PauseMenu.h"
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
std::unique_ptr<Player> player;
std::unique_ptr<PauseMenu> pauseMenu;

bool isMenuOpen = false;

void Update () {
    Time::Update();
    world->Update();
    if (!isMenuOpen) {
        player->Update();
    }
}

void OnResize (void*, i32 width, i32 height) {
    player->OnResize(width, height);
}

void OnKeyPressed (void*, i32 key, i32 scancode, i32 action, i32 mods) {
    if (action == GLFW_REPEAT) {
        return;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        isMenuOpen = !isMenuOpen;
        window->SetMouseLock(!isMenuOpen);
    }
    if (!isMenuOpen) {
        player->OnKeyPress(key, scancode, action, mods);
    }
}

void OnMouseMove (void*, f64 xposd, f64 yposd) {
    if (!isMenuOpen) {
        player->OnMouseMove(xposd, yposd);
    }
}

void OnMouseScroll (void*, f64 xoffset, f64 yoffset) {
    if (!isMenuOpen) {
        player->OnMouseScroll(xoffset, yoffset);
    }
}

void OnMouseClicked (void*, i32 button, i32 action, i32 mods) {
    if (!isMenuOpen) {
        player->OnMouseClick(button, action, mods);
    }
}


int main () {
    window = std::make_unique<GLWindow>(
        800, 600, "LearnOpenGL", WindowCallbackInfo{
            .userData = nullptr,
            .keyCallback = OnKeyPressed,
            .mouseButtonCallback = OnMouseClicked,
            .mouseMoveCallback = OnMouseMove,
            .mouseScrollCallback = OnMouseScroll,
            .resizeCallback = OnResize,
        });

    window->SetMouseLock(true);
    window->EnableDepthTest();
    window->clearColor = { 0.4f, 0.6f, 0.9f, 1.0f };


    shader = std::make_unique<ShaderProgram>(
        Shader::FromFile(GL_VERTEX_SHADER, "../res/shaders/minecube_vs.glsl"),
        Shader::FromFile(GL_FRAGMENT_SHADER, "../res/shaders/minecube_fs.glsl"));
    shader->Bind();

    Time::Init();
    Block::Init(*shader, "../res/textures/terrain.png");

    world = std::make_unique<World>();
    player = std::make_unique<Player>(world.get());

    for (int x = 0; x < 2 * Chunk::CHUNK_SIZE; x++) {
        for (int z = 0; z < 2 * Chunk::CHUNK_SIZE; z++) {
            const int y = x / Chunk::CHUNK_SIZE + z / Chunk::CHUNK_SIZE + 1;
            for (int i = 0; i < y; i++) {
                const auto block = i == 0 ? 50 : Block::Grass;
                world->SetBlock(x, i, z, block);
            }
        }
    }

    OnResize(nullptr, window->Width, window->Height);

    pauseMenu = std::make_unique<PauseMenu>(*window);

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

    shader->setMat4("projection", player->camera.Projection);
    shader->setMat4("view", player->camera.View);

    world->shader = shader.get();
    world->Render();

    if (isMenuOpen) {
        pauseMenu->Render();
    }

}




