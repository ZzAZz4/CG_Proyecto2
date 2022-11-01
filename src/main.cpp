#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLWindow.h"
#include "Texture.h"
#include "Player.h"
#include "ShaderProgram.h"
#include "Time.h"
#include "Chunk.h"
#include <memory>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void Render ();

std::unique_ptr<GLWindow> window;
std::unique_ptr<ShaderProgram> shader;
std::unique_ptr<Texture2D> texture;
std::unique_ptr<World> world;
std::unique_ptr<Player> player;

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
    if (action == GLFW_REPEAT) return;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        isMenuOpen = !isMenuOpen;
        window->SetMouseLock(!isMenuOpen);
    }
    player->OnKeyPress(key, scancode, action, mods);
}

void OnMouseMove (void*, f64 xposd, f64 yposd) {
    player->OnMouseMove(xposd, yposd);
}

void OnMouseScroll (void*, f64 xoffset, f64 yoffset) {
    player->OnMouseScroll(xoffset, yoffset);
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
//    window->EnableCulling(GL_BACK, GL_CW);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->Handle, true);
    ImGui_ImplOpenGL3_Init("#version 450 core");

    while (!window->ShouldClose()) {
        window->PollEvents();
        Update();

        window->ClearDisplay();
        Render();

        window->SwapBuffers();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

void Render () {
    shader->Bind();

    shader->setMat4("projection", player->camera.Projection);
    shader->setMat4("view", player->camera.View);

    world->shader = shader.get();
    world->Render();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (isMenuOpen) {
        ImGui::Begin("Menu");
        ImGui::Text("Hello, world!");
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}




