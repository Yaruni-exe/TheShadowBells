#include "CreditsScene.h"
#include "MenuButton.h" // Füge dies hinzu, um die Button-Implementierung zu finden
#include <string>
#include <Store.h>
#include "MenuScene.h" // Inkludieren, um zur MenuScene zurückzuwechseln

using namespace std::string_literals;

namespace game::scenes {
    CreditsScene::CreditsScene() {
        background_texture = LoadTexture("assets/graphics/backgrounds/Creditmenu_screen.png");

        int button_width = 256;
        int button_height = 64;
        int x_pos = 50;
        int y_pos = GetScreenHeight() - button_height - 50;

        back_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_pos, (float)button_width, (float)button_height},
            "assets/graphics/backgrounds/Control_Button_Zurueck_White.png",
            "assets/graphics/backgrounds/Control_Button_Zurueck_Yellow.png",
            []() { game::core::Store::stage->SwitchToNewScene("menu"s, std::make_unique<MenuScene>()); }
        );
    }

    CreditsScene::~CreditsScene() {
        UnloadTexture(background_texture);
    }

    void CreditsScene::Update() {
        Vector2 mouse_pos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (back_button->IsHovered(mouse_pos)) {
                back_button->on_click();
            }
        }
    }

    void CreditsScene::Draw() {
        Rectangle source_rec = {0.0f, 0.0f, (float)background_texture.width, (float)background_texture.height};
        Rectangle dest_rec = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};
        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(background_texture, source_rec, dest_rec, origin, 0.0f, WHITE);

        back_button->Draw(GetMousePosition());
    }
}