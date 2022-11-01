
#include "Time.h"
#include "Application.h"


Application::Application ()
    : window(
    800, 600, "LearnOpenGL", WindowCallbackInfo{
        .userData = this,
        .keyCallback = OnKeyPressedCallback,
        .mouseButtonCallback = OnMouseClickedCallback,
        .mouseMoveCallback = OnMouseMoveCallback,
        .mouseScrollCallback = OnMouseScrollCallback,
        .resizeCallback = OnResizeCallback,
    }) {
    GLWindow::SetActive(&window);
    window.SetMouseLock(true);
    window.EnableDepthTest();
    // TODO: skybox?
    window.clearColor = { 0.4f, 0.6f, 0.9f, 1.0f };

    Time::Init();
}

void Application::Update () {
    Time::Update();
    scene->Update();
}

void Application::Render () {
    scene->Render();
}

void Application::OnResize (i32 width, i32 height) {
    scene->OnResize(width, height);
}

void Application::OnKeyPressed (i32 key, i32 scancode, i32 action, i32 mods) {
    scene->OnKeyPressed(key, scancode, action, mods);
}

void Application::OnMouseMove (f64 xposd, f64 yposd) {
    scene->OnMouseMove(xposd, yposd);
}

void Application::OnMouseScroll (f64 xoffset, f64 yoffset) {
    scene->OnMouseScroll(xoffset, yoffset);
}

void Application::OnMouseClicked (i32 button, i32 action, i32 mods) {
    scene->OnMouseClicked(button, action, mods);
}


void Application::LoadScene (const std::string& sceneName) {
    // TODO: actually load a new scene
    scene = std::make_unique<Scene>();
    for (int x = 0; x < 2 * Chunk::CHUNK_SIZE; x++) {
        for (int z = 0; z < 2 * Chunk::CHUNK_SIZE; z++) {
            const int y = x / Chunk::CHUNK_SIZE + z / Chunk::CHUNK_SIZE + 1;
            for (int i = 0; i < y; i++) {
                const auto block = i == 0 ? 50 : Block::Grass;
                scene->world.SetBlock(x, i, z, block);
            }
        }
    }
    OnResize(window.Width, window.Height);
}

void Application::OnKeyPressedCallback (void* self, i32 key, i32 scancode, i32 action, i32 mods) {
    static_cast<Application*>(self)->OnKeyPressed(key, scancode, action, mods);
}

void Application::OnMouseClickedCallback (void* self, i32 button, i32 action, i32 mods) {
    static_cast<Application*>(self)->OnMouseClicked(button, action, mods);
}

void Application::OnMouseMoveCallback (void* self, f64 xposd, f64 yposd) {
    static_cast<Application*>(self)->OnMouseMove(xposd, yposd);
}

void Application::OnMouseScrollCallback (void* self, f64 xoffset, f64 yoffset) {
    static_cast<Application*>(self)->OnMouseScroll(xoffset, yoffset);

}

void Application::OnResizeCallback (void* self, i32 width, i32 height) {
    static_cast<Application*>(self)->OnResize(width, height);
}

void Application::Run () {
    while (!window.ShouldClose()) {
        window.PollEvents();
        Update();

        window.ClearDisplay();
        Render();

        window.SwapBuffers();
    }

}
