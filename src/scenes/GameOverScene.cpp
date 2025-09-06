#include "GameOverScene.h"
#include "MenuScene.h"
#include <Store.h>
#include <iostream>

using namespace std::string_literals;

namespace game::scenes {
    GameOverScene::GameOverScene(std::shared_ptr<game::core::Game> game) : game_(game) {
        background_texture = LoadTexture("assets/graphics/backgrounds/Menu.png");

        return_button_texture_normal = LoadTexture("assets/graphics/menu_button_start_normal.png");
        return_button_texture_hover = LoadTexture("assets/graphics/menu_button_start_hover.png");

        int button_width = 256;
        int button_height = 64;
        int x_pos = (GetScreenWidth() / 2) - (button_width / 2);
        int y_pos = (GetScreenHeight() / 2) + 50;

        return_button_rect = (Rectangle){(float)x_pos, (float)y_pos, (float)button_width, (float)button_height};
    }

    GameOverScene::~GameOverScene()
    {
        UnloadTexture(background_texture);
        UnloadTexture(return_button_texture_normal);
        UnloadTexture(return_button_texture_hover);
    }

    void GameOverScene::Update()
    {
        Vector2 mouse_pos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse_pos, return_button_rect)) {
                // Die MenuScene wird jetzt ohne Argumente erstellt,
                // um den Fehler zu beheben.
                game::core::Store::stage->SwitchToNewScene("menu"s, std::make_unique<MenuScene>());
            }
        }
    }

    void GameOverScene::Draw()
    {
        Rectangle source_rec = {0.0f, 0.0f, (float)background_texture.width, (float)background_texture.height};
        Rectangle dest_rec = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};
        Vector2 origin = {0.0f, 0.0f};
        DrawTexturePro(background_texture, source_rec, dest_rec, origin, 0.0f, WHITE);

        const char* game_over_text = "GAME OVER";
        int text_width = MeasureText(game_over_text, 80);
        DrawText(game_over_text, (GetScreenWidth() - text_width) / 2, GetScreenHeight() / 2 - 100, 80, RED);

        Vector2 mouse_pos = GetMousePosition();
        if (CheckCollisionPointRec(mouse_pos, return_button_rect)) {
            DrawTextureV(return_button_texture_hover, {return_button_rect.x, return_button_rect.y}, WHITE);
        } else {
            DrawTextureV(return_button_texture_normal, {return_button_rect.x, return_button_rect.y}, WHITE);
        }
    }
}
