#include "EndScene.h"
#include "MenuScene.h"
#include <Store.h>
#include <iostream>

using namespace std::string_literals;

namespace game::scenes {

    EndScene::EndScene()
        : animation(
                {970.0f, 540.0f}, // Framegröße
                "assets/graphics/backgrounds/Endscreen-Sheet.png",
                9,           // Anzahl der Frames
                9,           // Frames pro Reihe
                6.0f         // FPS
            )
    {
        int button_width  = 256;
        int button_height = 64;
        int x_pos = GetScreenWidth() - button_width - 20;   // unten rechts
        int y_pos = GetScreenHeight() - button_height - 20;

        return_button = std::make_unique<MenuButton>(
            (Rectangle){(float)x_pos, (float)y_pos, (float)button_width, (float)button_height},
            "assets/graphics/backgrounds/Pause_Hauptmenue_Button_White.png",
            "assets/graphics/backgrounds/Pause_Hauptmenue_Button_Yellow.png",
            []() {
                game::core::Store::stage->ReplaceWithNewScene(
                    "menu"s,
                    "end"s,
                    std::make_unique<MenuScene>()
                );
            }
        );
    }

    EndScene::~EndScene()
    {
        // MenuButton kümmert sich selbst um seine Texturen
    }

    void EndScene::Update()
    {
        float dt = GetFrameTime();
        animation.Next_Frame(dt);

        Vector2 mouse_pos = GetMousePosition();

        if (return_button && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (return_button->IsHovered(mouse_pos)) {
                return_button->on_click();  // Aktion ausführen
            }
        }
    }

    void EndScene::Draw()
    {
        // Frame-Größe manuell
        Vector2 frame_size = {970.0f, 540.0f};

        // Basis-Skalierung berechnen
        float scaleX = (float)GetScreenWidth() / frame_size.x;
        float scaleY = (float)GetScreenHeight() / frame_size.y;

        // Den größeren Scale-Faktor wählen und zusätzlichen Zoom draufpacken
        float zoom = std::max(scaleX, scaleY) * 1.05f; // 10% größer

        // Neue Größe nach Zoom
        Vector2 draw_size = { frame_size.x * zoom, frame_size.y * zoom };

        // Offset, um die Animation zu zentrieren
        Vector2 offset = { (GetScreenWidth() - draw_size.x) / 2.0f,
                           (GetScreenHeight() - draw_size.y) / 2.0f };

        animation.Draw_Current_Frame(offset, draw_size);

        if (return_button) {
            return_button->Draw(GetMousePosition());
        }
    }
}
