#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "../rendering/GLWindow.h"

Scene::Scene () :
    world(),
    player(&world),
    pauseMenu(*GLWindow::active_window, &player) {
    world.shader = std::make_unique<ShaderProgram>(
        Shader::FromFile(GL_VERTEX_SHADER, "../res/shaders/minecube_vs.glsl"),
        Shader::FromFile(GL_FRAGMENT_SHADER, "../res/shaders/minecube_fs.glsl"));

    Block::Init(*world.shader, "../res/textures/terrain.png");
}

void Scene::Update () {
    world.Update();
    if (!isMenuOpen) {
        player.Update();
    }
}

void Scene::Render () {
    world.Render(&player.camera);
    if (isMenuOpen) {
        pauseMenu.Render();
    }
}

void Scene::OnResize (int width, int height) {
    player.OnResize(width, height);
}

void Scene::OnKeyPressed (int key, int scancode, int action, int mods) {
    if (action == GLFW_REPEAT) {
        return;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        isMenuOpen = !isMenuOpen;
        GLWindow::active_window->SetMouseLock(!isMenuOpen);
    }
    if (!isMenuOpen) {
        player.OnKeyPress(key, scancode, action, mods);
    }
}

void Scene::OnMouseMove (double xposd, double yposd) {
    if (!isMenuOpen) {
        player.OnMouseMove(xposd, yposd);
    }
}

void Scene::OnMouseScroll (double xoffset, double yoffset) {
    if (!isMenuOpen) {
        player.OnMouseScroll(xoffset, yoffset);
    }
}

void Scene::OnMouseClicked (int button, int action, int mods) {
    if (!isMenuOpen) {
        player.OnMouseClick(button, action, mods);
    }
}
