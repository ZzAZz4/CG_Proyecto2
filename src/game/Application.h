

#ifndef OGL_APPLICATION_H
#define OGL_APPLICATION_H


#include "../rendering/GLWindow.h"
#include "Scene.h"

struct Application {
    GLWindow window;
    std::unique_ptr<Scene> scene;

    Application();

    void LoadScene (const std::string &sceneName);

    void Run();

    void Update();
    void Render();

    void OnKeyPressed (i32 key, i32 scancode, i32 action, i32 mods);
    void OnMouseClicked (i32 button, i32 action, i32 mods);
    void OnMouseMove (f64 xposd, f64 yposd);
    void OnMouseScroll (f64 xoffset, f64 yoffset);
    void OnResize (i32 width, i32 height);


private:
    static void OnKeyPressedCallback (void* self, i32 key, i32 scancode, i32 action, i32 mods);
    static void OnMouseClickedCallback (void* self, i32 button, i32 action, i32 mods);
    static void OnMouseMoveCallback (void* self, f64 xposd, f64 yposd);
    static void OnMouseScrollCallback (void* self, f64 xoffset, f64 yoffset);
    static void OnResizeCallback (void* self, i32 width, i32 height);

};


#endif //OGL_APPLICATION_H
