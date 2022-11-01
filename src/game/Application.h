

#ifndef OGL_APPLICATION_H
#define OGL_APPLICATION_H

#include "../rendering/GLWindow.h"
#include "Scene.h"

struct Application {
    GLWindow window;
    std::unique_ptr<Scene> scene;

    Application();

    void LoadScene(const std::string& sceneName);
    void RandomScene();

    void Run();

    void Update();
    void Render();

    void OnKeyPressed(int key, int scancode, int action, int mods);
    void OnMouseClicked(int button, int action, int mods);
    void OnMouseMove(double xposd, double yposd);
    void OnMouseScroll(double xoffset, double yoffset);
    void OnResize(int width, int height);

private:
    static void OnKeyPressedCallback(void* self, int key, int scancode, int action, int mods);
    static void OnMouseClickedCallback(void* self, int button, int action, int mods);
    static void OnMouseMoveCallback(void* self, double xposd, double yposd);
    static void OnMouseScrollCallback(void* self, double xoffset, double yoffset);
    static void OnResizeCallback(void* self, int width, int height);
};

#endif // OGL_APPLICATION_H
