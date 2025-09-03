#include "PauseScene.h"
#include <string>
#include <raylib.h>
#include <Store.h>
#include "MenuScene.h"
#include <iostream>

using namespace std::string_literals;

namespace game::scenes {

    PauseScene::PauseScene()
    {
        int button_width = 256;
        int button_height = 64;
        int x_pos = (GetScreenWidth() / 2) - (button_width / 2);
        int y_start = (GetScreenHeight() / 2) - (button_height + 10);
        int y_spacing = button_height + 20;

        continue_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start, (float)button_width, (float)button_height},
            "assets/graphics/button_continue_normal.png",
            "assets/graphics/button_continue_hover.png",
            []() {
                game::core::Store::stage->ReplaceWithExistingScene("pause"s, "game"s);
            }
        );

        menu_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start + y_spacing, (float)button_width, (float)button_height},
            "assets/graphics/button_menu_normal.png",
            "assets/graphics/button_menu_hover.png",
            []() { game::core::Store::stage->ReplaceWithNewScene("pause"s, "menu"s, std::make_shared<MenuScene>()); }
        );
    }

    PauseScene::~PauseScene() {}

    void PauseScene::Update()
    {
        Vector2 mouse_pos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (continue_button->IsHovered(mouse_pos)) {
                continue_button->on_click();
            } else if (menu_button->IsHovered(mouse_pos)) {
                menu_button->on_click();
            }
        }
    }

    void PauseScene::Draw()
    {
        // Zeichnet nur die Buttons, die über dem Spiel liegen.
        Vector2 mouse_pos = GetMousePosition();
        continue_button->Draw(mouse_pos);
        menu_button->Draw(mouse_pos);
        DrawRectangleLinesEx(continue_button->rect, 2.0f, RED);
        DrawRectangleLinesEx(menu_button->rect, 2.0f, RED);
    }
}