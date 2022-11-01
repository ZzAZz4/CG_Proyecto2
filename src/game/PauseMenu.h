#ifndef OGL_PAUSEMENU_H
#define OGL_PAUSEMENU_H

#include "Gui.h"
#include "Player.h"

class PauseMenu : public Gui {
public:
    PauseMenu(const GLWindow& window, Player* player);
    ~PauseMenu() override = default;
    Player* player;

    void SetupFrame() override;
    void changeHeldBlock();
    bool showSubMenu = false;
};


#endif //OGL_PAUSEMENU_H
