#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLWindow.h"
#include "Texture.h"
#include "Player.h"
#include "ShaderProgram.h"
#include "Time.h"


#include "renderObjects.h"
#include <memory>


void renderScene ();


std::unique_ptr<GLWindow> display;
std::unique_ptr<ShaderProgram> shader;
std::unique_ptr<Texture2D> texture;
Player player;


void Update () {
    Time::Update();
    player.Update();
}

void OnResize (void*, i32 width, i32 height) {
    player.OnResize(width, height);
}

void OnKeyPressed (void*, i32 key, i32 scancode, i32 action, i32 mods) {
    if (action == GLFW_REPEAT) return;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) display->Close();
    player.OnKeyPress(key, scancode, action, mods);
}

void OnMouseMove (void*, f64 xposd, f64 yposd) {
    player.OnMouseMove(xposd, yposd);
}

void OnMouseScroll (void*, f64 xoffset, f64 yoffset) {
    player.OnMouseScroll(xoffset, yoffset);
}

glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

int main () {
    display = std::make_unique<GLWindow>(
        800, 600, "LearnOpenGL", WindowCallbackInfo{
            .userData = nullptr,
            .keyCallback = OnKeyPressed,
            .mouseMoveCallback = OnMouseMove,
            .mouseScrollCallback = OnMouseScroll,
            .resizeCallback = OnResize,
        });

    display->SetMouseLock(true);
    display->EnableDepthTest();
    display->EnableCulling(GL_BACK, GL_CCW);
    display->clearColor = { 0.4f, 0.6f, 0.9f, 1.0f };


    shader = std::make_unique<ShaderProgram>(
        Shader::FromFile(GL_VERTEX_SHADER, "../res/shaders/shadow_mapping_vs.glsl"),
        Shader::FromFile(GL_FRAGMENT_SHADER, "../res/shaders/shadow_mapping_fs.glsl"));

    shader->Bind();

    texture = std::make_unique<Texture2D>(Texture2D::FromFile("../res/textures/missigno.png"));
    shader->setInt("diffuseTexture", 0);

    Time::Init();

    OnResize(display.get(), display->Width, display->Height);

    while (!display->ShouldClose()) {
        display->PollEvents();
        Update();

        display->ClearDisplay();
        renderScene();

        display->SwapBuffers();
    }

    return 0;
}

void renderScene () {
    shader->Bind();
    texture->Bind(0);

    shader->setMat4("projection", player.camera.Projection);
    shader->setMat4("view", player.camera.View);
    shader->setVec3("viewPos", player.camera.Position);
    shader->setVec3("lightPos", lightPos);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(25.0f, 1.f, 25.0f));

    shader->setMat4("model", model);
    renderPlane();

    glm::vec3 positions[12];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            positions[i * 4 + j] = glm::vec3((f32) i * 2.0f - 2.0f, 0.0f, (f32) j * 2.0f - 2.0f);
        }
    }

    for (const auto& position: positions) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, glm::vec3(1.f));
        shader->setMat4("model", model);
        renderCube();
    }
}




