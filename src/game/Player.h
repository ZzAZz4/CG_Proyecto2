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
    float speed = 5.f;
    float mouseSensitivity = 0.1f;
};

struct Player {
    Camera camera;
    World* world = nullptr;
    ActionFlags actionFlags;

    float speed = 2.5f; // 0 - 10
    float runSpeed = 4.0f; // 0 - 20
    float gravity = -26.f;
    float impulse = 8.5f;
    float yAddedVelocity = 0.f;
    float mouseSensitivity = 0.1f; // 0 - 1

    bool inSurvival = false;
    bool touchesGround = false;

    uint8_t heldBlock = Block::Grass;

    Player(World* world, PlayerSettings settings = PlayerSettings());

    void Respawn();
    void Update();

    void OnMouseMove(double xpos, double ypos);
    void OnKeyPress(int key, int scancode, int action, int mods);
    void OnResize(int width, int height);
    void OnMouseScroll(double xoffset, double yoffset);
    void OnMouseClick(int button, int action, int mods);
};

#endif // OGL_PLAYER_H
