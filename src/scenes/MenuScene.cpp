#include "MenuScene.h"
#include <string>
#include <Store.h>
#include "Level1Scene.h"
#include <iostream>
#include "MenuButton.h"
#include "ControlsScene.h"
#include "CreditsScene.h"

using namespace std::string_literals;

namespace game::scenes {

    MenuScene::MenuScene()
    {
        background_texture = LoadTexture("assets/graphics/backgrounds/Menu_Menu_Screen.png");

        int button_width = 350;
        int button_height = 90;
        int x_pos = 50;
        int y_offset = 150;
        int y_start = (GetScreenHeight() / 2) - (button_height * 2) + y_offset;
        int y_spacing = button_height + 20;

        start_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start, (float)button_width, (float)button_height},
            "assets/graphics/backgrounds/Menu_Neues_Spiel_Button_White.png",
            "assets/graphics/backgrounds/Menu_Neues_Spiel_Button_Yellow.png",
            []() { game::core::Store::stage->ReplaceWithNewScene("menu"s, "game"s, std::make_unique<Level1Scene>()); }
        );

        controls_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start + y_spacing, (float)button_width, (float)button_height},
            "assets/graphics/backgrounds/Menu_Steuerung_Button_White.png",
            "assets/graphics/backgrounds/Menu_Steuerung_Button_Yellow.png",
            []() { game::core::Store::stage->SwitchToNewScene("controls"s, std::make_unique<ControlsScene>()); } // Korrekter Aufruf
        );

        credits_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start + 2 * y_spacing, (float)button_width, (float)button_height},
            "assets/graphics/backgrounds/Menu_Credits_Button_White.png",
            "assets/graphics/backgrounds/Menu_Credits_Button_Yellow.png",
            []() { game::core::Store::stage->SwitchToNewScene("credits"s, std::make_unique<CreditsScene>()); } // Korrekter Aufruf
        );

        exit_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start + 3 * y_spacing, (float)button_width, (float)button_height},
            "assets/graphics/backgrounds/Menu_Spiel_Verlassen_Button_White.png",
            "assets/graphics/backgrounds/Menu_Spiel_Verlassen_Button_Yellow.png",
            []() { CloseWindow(); }
        );
    }

    MenuScene::~MenuScene()
    {
        UnloadTexture(background_texture);
    }

    void MenuScene::Update()
    {
        Vector2 mouse_pos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (start_button->IsHovered(mouse_pos)) {
                start_button->on_click();
            } else if (controls_button->IsHovered(mouse_pos)) {
                controls_button->on_click();
            } else if (credits_button->IsHovered(mouse_pos)) {
                credits_button->on_click();
            } else if (exit_button->IsHovered(mouse_pos)) {
                exit_button->on_click();
            }
        }
    }

    void MenuScene::Draw()
    {
        Rectangle source_rec = {0.0f, 0.0f, (float)background_texture.width, (float)background_texture.height};
        Rectangle dest_rec = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};
        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(background_texture, source_rec, dest_rec, origin, 0.0f, WHITE);

        Vector2 mouse_pos = GetMousePosition();
        start_button->Draw(mouse_pos);
        controls_button->Draw(mouse_pos);
        credits_button->Draw(mouse_pos);
        exit_button->Draw(mouse_pos);

        DrawRectangleLinesEx(start_button->rect, 2.0f, RED);
        DrawRectangleLinesEx(controls_button->rect, 2.0f, RED);
        DrawRectangleLinesEx(credits_button->rect, 2.0f, RED);
        DrawRectangleLinesEx(exit_button->rect, 2.0f, RED);
    }
}