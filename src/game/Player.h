

#ifndef OGL_PLAYER_H
#define OGL_PLAYER_H

#include "Block.h"
#include "Camera.h"
#include "World.h"

struct ActionFlags {
    bool forward : 1 = false;
    bool backward : 1 = false;
    bool left : 1 = false;
    bool right : 1 = false;
    bool up : 1 = false;
    bool down : 1 = false;
    bool run : 1 = false;
};

struct PlayerSettings {
    float speed = 2.5f;
    float mouseSensitivity = 0.1f;
};

struct Player {
    Camera camera{glm::vec3(0.0f, 2.0f, 0.0f), 90.f, 0.f};
    World* world = nullptr;
    ActionFlags action_flags;

    float speed = 2.5f;
    float mouseSensitivity = 0.1f;

    uint8_t heldBlock = Block::Grass;

    Player(World* world, PlayerSettings settings = PlayerSettings());

    void Update();

    void OnMouseMove(double xpos, double ypos);
    void OnKeyPress(int key, int scancode, int action, int mods);
    void OnResize(int width, int height);
    void OnMouseScroll(double xoffset, double yoffset);
    void OnMouseClick(int button, int action, int mods);
};

#endif // OGL_PLAYER_H
