#ifndef OGL_SCENE_H
#define OGL_SCENE_H

#include "PauseMenu.h"
#include "Player.h"
#include "World.h"

struct Scene {
    World world;
    Player player;
    PauseMenu pauseMenu;
    bool isMenuOpen = false;

    Scene();

    void Randomize();

    void Update();
    void Render();

    void OnResize(int width, int height);
    void OnKeyPressed(int key, int scancode, int action, int mods);
    void OnMouseMove(double xposd, double yposd);
    void OnMouseScroll(double xoffset, double yoffset);
    void OnMouseClicked(int button, int action, int mods);
};

#endif // OGL_SCENE_H
