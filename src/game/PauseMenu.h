#ifndef OGL_PAUSEMENU_H
#define OGL_PAUSEMENU_H

#include "Gui.h"
#include "Player.h"

class PauseMenu : public Gui {
public:
    PauseMenu(const GLWindow& window, Player* player, World* world);
    ~PauseMenu() override = default;
    bool showSubMenu = false;
    Player* player;
    World* world;

    void SetupFrame() override;

    void changeHeldBlock();
    void switchInSurvival();
    void changePlayerSettings();
    void setTime();
};

#endif // OGL_PAUSEMENU_H
