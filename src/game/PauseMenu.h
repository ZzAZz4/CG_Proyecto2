#ifndef OGL_PAUSEMENU_H
#define OGL_PAUSEMENU_H

#include "Gui.h"
#include "Player.h"

class PauseMenu : public Gui {
public:
    PauseMenu(const GLWindow& window, Player* player);
    ~PauseMenu() override = default;
    bool showSubMenu = false;
    Player* player;

    void SetupFrame() override;
    void changeHeldBlock();
    void switchInSurvival();
};

#endif // OGL_PAUSEMENU_H
