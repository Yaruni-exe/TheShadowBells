/*#include "CarScene.h"
#include "Level2Scene.h"
#include <Store.h>
#include <iostream>

using namespace std::string_literals;

namespace game::scenes {

    CarScene::CarScene()
        : animation(
            {426.0f, 240.0f}, // Frame-Größe: 21726 / 51 = 426 px pro Frame, Höhe 240 px
            "assets/graphics/backgrounds/Leveltransition-Sheet.png",
            51,    // Anzahl der Frames
            51,    // Frames pro Reihe (alle Frames in einer Reihe)
            6.0f   // FPS, kann angepasst werden
        ),
        timer(0.0f),
        transition_time(5.0f) // Zeit in Sekunden bis Szenenwechsel
    {}

    CarScene::~CarScene() {}

    void CarScene::Update()
    {
        float dt = GetFrameTime();

        // Animation fortsetzen
        animation.Next_Frame(dt);

        // Timer hochzählen und Szenenwechsel prüfen
        timer += dt;
        if (timer >= transition_time) {
            game::core::Store::stage->ReplaceWithNewScene(
                "level2"s,
                "car"s,
                std::make_unique<Level2Scene>()
            );
        }
    }

    void CarScene::Draw()
    {
        // Frame-Größe
        Vector2 frame_size = {426.0f, 240.0f};

        // Basis-Skalierung
        float scaleX = (float)GetScreenWidth() / frame_size.x;
        float scaleY = (float)GetScreenHeight() / frame_size.y;

        // Zoom, um weiße Ränder zu vermeiden
        float zoom = std::max(scaleX, scaleY) ;//* 1.2f; // etwas stärkerer Zoom

        Vector2 draw_size = { frame_size.x * zoom, frame_size.y * zoom };
        Vector2 offset = { (GetScreenWidth() - draw_size.x) / 2.0f,
                           (GetScreenHeight() - draw_size.y) / 2.0f };

        animation.Draw_Current_Frame(offset, draw_size);
    }

}
*/