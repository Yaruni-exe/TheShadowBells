#include "PauseScene.h"
#include <string>
#include <raylib.h>
#include <Store.h>
#include "MenuScene.h"
#include <iostream>

using namespace std::string_literals;

namespace game::scenes {

PauseScene::PauseScene(const std::string& pausedSceneName)
    : paused_scene_name(pausedSceneName)
{
    // Hintergrundbild laden
    background_texture = LoadTexture("assets/graphics/backgrounds/Pause_Screen.png");

    int button_width = 256;
    int button_height = 64;
    int x_pos = (GetScreenWidth() / 2) - (button_width / 2);
    int y_start = (GetScreenHeight() / 2) - (button_height + 10);
    int y_spacing = button_height + 20;

    continue_button = std::make_unique<MenuButton>(
        (Rectangle){(float)x_pos, (float)y_start, (float)button_width, (float)button_height},
        "assets/graphics/backgrounds/Pause_Fortfahren_Button_White.png",
        "assets/graphics/backgrounds/Pause_Fortfahren_Button_Yellow.png",
        [this]() {
            game::core::Store::stage->SwitchToScene(paused_scene_name);
        }
    );

    menu_button = std::make_unique<MenuButton>(
        (Rectangle){(float)x_pos, (float)y_start + y_spacing, (float)button_width, (float)button_height},
        "assets/graphics/backgrounds/Pause_Hauptmenue_Button_White.png",
        "assets/graphics/backgrounds/Pause_Hauptmenue_Button_Yellow.png",
        []() {
            game::core::Store::stage->ClearAllScenes();
            game::core::Store::stage->SwitchToNewScene("menu"s, std::make_shared<MenuScene>());
        }
    );
}

PauseScene::~PauseScene()
{
    UnloadTexture(background_texture);
}

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
    // Hintergrund zeichnen
    Rectangle source = {0.0f, 0.0f, (float)background_texture.width, (float)background_texture.height};
    Rectangle dest   = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};
    DrawTexturePro(background_texture, source, dest, Vector2{0,0}, 0.0f, WHITE);

    // Buttons zeichnen
    Vector2 mouse_pos = GetMousePosition();
    continue_button->Draw(mouse_pos);
    menu_button->Draw(mouse_pos);
}

} // namespace game::scenes
