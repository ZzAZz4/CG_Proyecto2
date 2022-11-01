<<<<<<< HEAD


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
=======


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

    void Update();
    void Render();

    void OnResize(int width, int height);
    void OnKeyPressed(int key, int scancode, int action, int mods);
    void OnMouseMove(double xposd, double yposd);
    void OnMouseScroll(double xoffset, double yoffset);
    void OnMouseClicked(int button, int action, int mods);
};

#endif // OGL_SCENE_H
>>>>>>> 252be8cf1e429372afd42ddf68df21b71a67cc83
