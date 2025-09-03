#include "MenuScene.h"
#include <string>
#include <raylib.h>
#include <Store.h>
#include "Level1Scene.h"
#include <iostream>

using namespace std::string_literals;

namespace game::scenes {

    // Implementierung der MenuButton-Klasse
    MenuButton::MenuButton(Rectangle r, const std::string& normal_path, const std::string& hover_path, std::function<void()> click_action)
        : rect(r), on_click(click_action) {
        normal_texture = LoadTexture(normal_path.c_str());
        hover_texture = LoadTexture(hover_path.c_str());
    }

    MenuButton::~MenuButton() {
        UnloadTexture(normal_texture);
        UnloadTexture(hover_texture);
    }

    void MenuButton::Draw(Vector2 mouse_pos) {
        Texture2D* current_texture;
        if (CheckCollisionPointRec(mouse_pos, this->rect)) {
            current_texture = &this->hover_texture;
        } else {
            current_texture = &this->normal_texture;
        }
        DrawTextureV(*current_texture, {this->rect.x, this->rect.y}, WHITE);
    }

    bool MenuButton::IsHovered(Vector2 mouse_pos) const {
        return CheckCollisionPointRec(mouse_pos, this->rect);
    }

    // Implementierung der MenuScene-Klasse
    MenuScene::MenuScene()
    {
        background_texture = LoadTexture("assets/graphics/backgrounds/Menu.png");

        int button_width = 256;
        int button_height = 64;
        int x_pos = (GetScreenWidth() / 2) - (button_width / 2);
        int y_start = (GetScreenHeight() / 2) - (button_height * 2);
        int y_spacing = button_height + 20;

        start_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start, (float)button_width, (float)button_height},
            "assets/graphics/menu_button_start_normal.png",
            "assets/graphics/menu_button_start_hover.png",
            []() { game::core::Store::stage->SwitchToNewScene("game"s, std::make_unique<Level1Scene>()); }
        );

        controls_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start + y_spacing, (float)button_width, (float)button_height},
            "assets/graphics/menu_button_controls_normal.png",
            "assets/graphics/menu_button_controls_hover.png",
            []() { std::cout << "Steuerungs-Menü aufgerufen!" << std::endl; }
        );

        credits_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start + 2 * y_spacing, (float)button_width, (float)button_height},
            "assets/graphics/menu_button_credits_normal.png",
            "assets/graphics/menu_button_credits_hover.png",
            []() { std::cout << "Credits-Menü aufgerufen!" << std::endl; }
        );

        exit_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_start + 3 * y_spacing, (float)button_width, (float)button_height},
            "assets/graphics/menu_button_exit_normal.png",
            "assets/graphics/menu_button_exit_hover.png",
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

        // DEBUG: Hitboxen zur Positionsprüfung anzeigen
        DrawRectangleLinesEx(start_button->rect, 2.0f, RED);
        DrawRectangleLinesEx(controls_button->rect, 2.0f, RED);
        DrawRectangleLinesEx(credits_button->rect, 2.0f, RED);
        DrawRectangleLinesEx(exit_button->rect, 2.0f, RED);
    }
}