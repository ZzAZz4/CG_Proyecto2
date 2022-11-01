

#ifndef OGL_SCENE_H
#define OGL_SCENE_H

#include "World.h"
#include "PauseMenu.h"

struct Scene {
    World world;
    Player player;
    PauseMenu pauseMenu;
    bool isMenuOpen = false;

    Scene();

    void Update ();
    void Render ();

    void OnResize (i32 width, i32 height);

    void OnKeyPressed (i32 key, i32 scancode, i32 action, i32 mods);

    void OnMouseMove (f64 xposd, f64 yposd);

    void OnMouseScroll (f64 xoffset, f64 yoffset);

    void OnMouseClicked (i32 button, i32 action, i32 mods);
};


#endif //OGL_SCENE_H
