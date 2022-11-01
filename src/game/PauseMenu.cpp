#include "PauseMenu.h"
#include "imgui.h"

PauseMenu::PauseMenu(const GLWindow& window, Player* player) : Gui(window), player(player) {}

void ToggleButton(const char* str_id, bool* v) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;

    if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
        *v = !*v;
    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = *v ? IM_COL32(145 + 20, 211, 68 + 20, 255)
                    : IM_COL32(218 - 20, 218 - 20, 218 - 20, 255);
    else
        col_bg = *v ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius),
                               radius - 1.5f, IM_COL32(255, 255, 255, 255));
}

void PauseMenu::changeHeldBlock() {
    if (!showSubMenu) {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Change the block you use to build!");
        if (ImGui::Button("Change held block"))
            showSubMenu = true;
    } else {
        ImGui::BulletText("[ CHANGE HELD BLOCK ]");
        char newBlock[64];
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Current available blocks are:");
        for (const auto& bm : blockMap) {
            ImGui::Text("%s\n", bm.first.c_str());
        }
        ImGui::InputText("Which Block do you want to use?", newBlock, sizeof(newBlock));
        auto it = blockMap.find(newBlock);
        if (it != blockMap.end()) {
            this->player->heldBlock = blockMap[newBlock];
            ImGui::Text("Your held block is now: %s", newBlock);
        }
        if (ImGui::Button("Exit"))
            showSubMenu = false;
    }
}

void PauseMenu::switchInSurvival() {
    if (!showSubMenu) {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Play in survival (activate gravity and colisions)");
        ToggleButton("Switch to survival mode", &(player->inSurvival));
        if (player->inSurvival) {
            ImGui::Text("You are currently playing on Survival mode");
            ImGui::SliderFloat("Gravity", &player->gravity, -100.0f, 0.0f);
            ImGui::SliderFloat("Impulse", &player->impulse, 0.0f, 20.0f);
        } else
            ImGui::Text("Touch the toggle button to switch to Survival mode");
    }
}

void PauseMenu::SetupFrame() {
    ImGui::Begin("[ PAUSE ]");
    changeHeldBlock();
    switchInSurvival();

    ImGui::End();
}
