#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "../rendering/GLWindow.h"

Scene::Scene () :
    world(),
    player(&world),
    pauseMenu(*GLWindow::active_window) {
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

void Scene::OnResize (i32 width, i32 height) {
    player.OnResize(width, height);
}

void Scene::OnKeyPressed (i32 key, i32 scancode, i32 action, i32 mods) {
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

void Scene::OnMouseMove (f64 xposd, f64 yposd) {
    if (!isMenuOpen) {
        player.OnMouseMove(xposd, yposd);
    }
}

void Scene::OnMouseScroll (f64 xoffset, f64 yoffset) {
    if (!isMenuOpen) {
        player.OnMouseScroll(xoffset, yoffset);
    }
}

void Scene::OnMouseClicked (i32 button, i32 action, i32 mods) {
    if (!isMenuOpen) {
        player.OnMouseClick(button, action, mods);
    }
}
