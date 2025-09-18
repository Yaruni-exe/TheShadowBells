#include "Cutscene.h"
#include <Store.h>
#include "Level2Scene.h"

using namespace std::string_literals;

namespace game::scenes {

    Cutscene::Cutscene()
        : frameWidth(213), frameHeight(120), totalFrames(51), fps(15.0f)  // fps einstellbar
    {
        // Spritesheet laden
        spritesheet = LoadTexture("assets/graphics/backgrounds/Leveltransition-Sheet.png");
        if (spritesheet.id > 0) {
            is_ready = true;
        } else {
            TraceLog(LOG_WARNING, "Spritesheet konnte nicht geladen werden.");
            is_ready = false;
        }

        // Timer starten
        playTime = 0.0f;
        duration = 3.0f; // Sekunden bis zum Szenenwechsel (einstellbar)
    }

    Cutscene::~Cutscene() {
        if (is_ready) {
            UnloadTexture(spritesheet);
        }
    }

    void Cutscene::Update() {
        if (!is_ready) {
            game::core::Store::stage->SwitchToNewScene("level2"s, std::make_unique<Level2Scene>());
            return;
        }

        float dt = GetFrameTime();
        playTime += dt;

        // aktuellen Frame berechnen
        currentFrame = (int)(playTime * fps) % totalFrames;

        // Wenn die Dauer abgelaufen ist, zur nächsten Szene wechseln
        if (playTime >= duration) {
            game::core::Store::stage->SwitchToNewScene("level2"s, std::make_unique<Level2Scene>());
        }

        // Optional: Skip mit Taste
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            game::core::Store::stage->SwitchToNewScene("level2"s, std::make_unique<Level2Scene>());
        }
    }

    void Cutscene::Draw() {
        ClearBackground(BLACK);

        if (is_ready) {
            Rectangle source {
                (float)(currentFrame * frameWidth),
                0.0f,
                (float)frameWidth,
                (float)frameHeight
            };

            Rectangle dest {
                0.0f, 0.0f,
                (float)GetScreenWidth(),
                (float)GetScreenHeight()
            };

            DrawTexturePro(spritesheet, source, dest, {0,0}, 0.0f, WHITE);
        }
    }
}
