

#ifndef OGL_PAUSEMENU_H
#define OGL_PAUSEMENU_H

#include "Gui.h"

class PauseMenu : public Gui {
public:
    PauseMenu(const GLWindow& window);
    ~PauseMenu() override = default;

    void SetupFrame() override;
};

#endif // OGL_PAUSEMENU_H
