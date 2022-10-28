

#ifndef OGL_GLWINDOW_H
#define OGL_GLWINDOW_H

#include "types.h"

using KeyCallback = void (*) (void*, int key, int scancode, int action, int mods);
using MouseButtonCallback = void (*) (void*, int button, int action, int mods);
using MouseMovedCallback = void (*) (void*, double x, double y);
using MouseScrollCallback = void (*) (void*, double x, double y);
using WindowResizeCallback = void (*) (void*, int width, int height);
using WindowRefreshCallback = void (*) (void*);

struct WindowCallbackInfo {
    void* userData = nullptr;
    KeyCallback keyCallback = nullptr;
    MouseButtonCallback mouseButtonCallback = nullptr;
    MouseMovedCallback mouseMoveCallback = nullptr;
    MouseScrollCallback mouseScrollCallback = nullptr;
    WindowResizeCallback resizeCallback = nullptr;
};

struct GLWindow {
    WindowCallbackInfo callbackInfo;
    struct GLFWwindow* Handle;
    int Width;
    int Height;
    float AspectRatio;
    glm::vec4 clearColor{0.0f, 0.0f, 0.0f, 1.0f};

    GLWindow (int width, int height, const char* title, const WindowCallbackInfo& callbackInfo);
    ~GLWindow ();

    bool ShouldClose () const;
    void Close ();

    void ClearDisplay () const;
    void SwapBuffers () const;
    void PollEvents () const;
    void SetMouseLock (bool lock);

    void EnableDepthTest () const;
    void EnableCulling(int cullFace, int spinDirection) const;

private:
    static void OnKeyEvent (GLFWwindow* window, int key, int scancode, int action, int mode);
    static void OnMouseButton (GLFWwindow* window, int button, int action, int mods);
    static void OnMouseMoved (GLFWwindow* window, double x, double y);
    static void OnMouseScroll (GLFWwindow* window, double x, double y);
    static void OnResized (GLFWwindow* window, int width, int height);
    static void OnError (int errorCode, const char* description);
    static void OnDebug (unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void*);
};


#endif //OGL_GLWINDOW_H
