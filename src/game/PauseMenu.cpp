

#include "PauseMenu.h"
#include "imgui.h"

PauseMenu::PauseMenu(const GLWindow& window) : Gui(window) {}

void PauseMenu::SetupFrame() {
    ImGui::Begin("Pause Menu");
    ImGui::Text("Hello World");
    ImGui::End();
}
