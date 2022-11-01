#include "PauseMenu.h"
#include "imgui.h"

PauseMenu::PauseMenu(const GLWindow& window, Player* player): Gui(window), player(player) {
}

void PauseMenu::changeHeldBlock(){
    if (!showSubMenu) {
        if (ImGui::Button("Change held block")) showSubMenu = true;
    }
    else {
        ImGui::BulletText("[ CHANGE HELD BLOCK ]");
        char newBlock [64];
        ImGui::TextColored(ImVec4(1,1,0,1), "Current blocks are:");
        for(auto bm: blockMap) ImGui::Text("%s\n", bm.first.c_str());
        ImGui::InputText("Which Block do you want to use?", newBlock, sizeof(newBlock));
        auto it = blockMap.find(newBlock);
        if(it != blockMap.end()) {
            this->player->heldBlock = blockMap[newBlock];
            ImGui::Text("Your held block is now: %s", newBlock);
        }
        if(ImGui::Button("Exit")) showSubMenu = false;
    }
}

void PauseMenu::SetupFrame () {
    ImGui::Begin("[ PAUSE ]");
    changeHeldBlock();
    ImGui::End();
}


