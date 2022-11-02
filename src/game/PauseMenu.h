#ifndef OGL_PAUSEMENU_H
#define OGL_PAUSEMENU_H

#include "Gui.h"

enum PauseMenuState {
    PAUSE_MENU_STATE_MAIN,
    PAUSE_MENU_STATE_BLOCK_SELECT,
    PAUSE_MENU_STATE_LOAD_FILE,
    PAUSE_MENU_STATE_SAVE_FILE,
};

class PauseMenu : public Gui {
public:
    PauseMenu(const GLWindow& window, struct Scene* scene);
    ~PauseMenu() override = default;
    PauseMenuState state = PAUSE_MENU_STATE_MAIN;
    struct Scene* scene;


    void SetupFrame() override;

    void ShowSurvivalSwitch();
    void ShowPlayerSettings();
    void ShowSetTimeSlider();
    void ShowChangeBlockSubmenuButton();
    void ShowChangeBlockMenu();
    void ShowFileSelectButtons();
    void ShowLoadFileMenu();
    void ShowSaveFileMenu();
};

#endif // OGL_PAUSEMENU_H
