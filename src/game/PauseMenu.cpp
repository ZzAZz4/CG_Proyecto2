#include "PauseMenu.h"
#include "Player.h"
#include "Scene.h"
#include "World.h"
#include "imgui.h"

PauseMenu::PauseMenu(const GLWindow& window, Scene* scene) : Gui(window), scene(scene) {}

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

void PauseMenu::ShowChangeBlockMenu() {
    ImGui::BulletText("[ CHANGE HELD BLOCK ]");
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Current available blocks are:");
    std::string currentHeldBlock;
    for (const auto& bm : Block::nameLookup) {
        if (ImGui::Button(bm.first.data()))
            scene->player.heldBlock = Block::nameLookup[bm.first];
        if (bm.second == scene->player.heldBlock)
            currentHeldBlock = bm.first;
    }
    ImGui::Text("The block you are holding is: %s", currentHeldBlock.c_str());
    if (ImGui::Button("Exit"))
        state = PAUSE_MENU_STATE_MAIN;
}
void PauseMenu::ShowChangeBlockSubmenuButton() {
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Change the block you use to build!");
    if (ImGui::Button("Change held block"))
        state = PAUSE_MENU_STATE_BLOCK_SELECT;
}

void PauseMenu::ShowPlayerSettings() {
    ImGui::SliderFloat("Player speed", &scene->player.speed, 0.0f, 10.0f);
    ImGui::SliderFloat("Speed on running", &scene->player.runSpeed, 0.0f, 20.0f);
    ImGui::SliderFloat("Mouse sensitivity", &scene->player.mouseSensitivity, 0.0f, 1.0f);
}

void PauseMenu::ShowSurvivalSwitch() {
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Play in survival (activate gravity and colisions)");
    ToggleButton("Switch to survival mode", &(scene->player.inSurvival));
    if (scene->player.inSurvival) {
        ImGui::Text("You are currently playing on Survival mode");
        ImGui::SliderFloat("Gravity", &scene->player.gravity, -100.0f, 0.0f);
        ImGui::SliderFloat("Impulse", &scene->player.impulse, 0.0f, 20.0f);
    } else {
        ImGui::Text("Touch the toggle button to switch to Survival mode\n");
    }
}

void PauseMenu::ShowSetTimeSlider() {
    ImGui::SliderFloat("Time", &scene->world.time, 0.0f, 24000.0f);
}

void PauseMenu::SetupFrame() {
    ImGui::Begin("[ PAUSE ]");
    switch (state) {
        case PAUSE_MENU_STATE_MAIN: {
            ShowChangeBlockSubmenuButton();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ShowSurvivalSwitch();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ShowPlayerSettings();
            ShowSetTimeSlider();
            ShowFileSelectButtons();
            break;
        }
        case PAUSE_MENU_STATE_BLOCK_SELECT: {
            ShowChangeBlockMenu();
            break;
        }
        case PAUSE_MENU_STATE_LOAD_FILE: {
            ShowLoadFileMenu();
            break;
        }
        case PAUSE_MENU_STATE_SAVE_FILE: {
            ShowSaveFileMenu();
            break;
        }
        default: {
            break;
        }
    }
    ImGui::End();
}
void PauseMenu::ShowFileSelectButtons() {
    if (ImGui::Button("New world")) {
        scene->Randomize();
    }
    if (ImGui::Button("Load world")) {
        state = PAUSE_MENU_STATE_LOAD_FILE;
    }
    if (ImGui::Button("Save world")) {
        state = PAUSE_MENU_STATE_SAVE_FILE;
    }
}
void PauseMenu::ShowLoadFileMenu() {
    static char buf[256]{};
    ImGui::BulletText("[ LOAD WORLD ]");
    // type in the name of the file to load
    ImGui::InputText("File name", buf, 256);
    if (ImGui::Button("Load")) {
        scene->Load(buf);
        state = PAUSE_MENU_STATE_MAIN;
    }
    if (ImGui::Button("Exit")) {
        state = PAUSE_MENU_STATE_MAIN;
    }
}

void PauseMenu::ShowSaveFileMenu() {
    static char buf[256]{};
    ImGui::BulletText("[ SAVE WORLD ]");
    // type in the name of the file to save
    ImGui::InputText("File name", buf, 256);
    if (ImGui::Button("Save")) {
        printf("Saving world to %s\n", buf);
        scene->Save(buf);
        state = PAUSE_MENU_STATE_MAIN;
    }
    if (ImGui::Button("Exit")) {
        state = PAUSE_MENU_STATE_MAIN;
    }
}
