

#ifndef OGL_PLAYER_H
#define OGL_PLAYER_H

#include "types.h"
#include "Camera.h"

struct ActionFlags {
    bool forward: 1 = false;
    bool backward: 1 = false;
    bool left: 1 = false;
    bool right: 1 = false;
    bool up: 1 = false;
    bool down: 1 = false;
    bool run: 1 = false;
};

struct Player {
    Camera camera {glm::vec3(0.0f, 0.0f, 3.0f), -90.f, 0.f};
    ActionFlags action_flags;
    float speed = 2.5f;
    float mouseSensitivity = 0.1f;

    void Update();

    void OnMouseMove(double xpos, double ypos);
    void OnKeyPress(int key, int scancode, int action, int mods);
    void OnResize(int width, int height);
    void OnMouseScroll(double xoffset, double yoffset);
};

#endif //OGL_PLAYER_H
