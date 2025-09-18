#include "StoryScene.h"
#include "Level1Scene.h"
#include "../core/Store.h"  // Anpassung je nach Projektstruktur

namespace game::scenes {

    StoryScene::StoryScene()
        : current_index(0)
    {
        // Story-Bilder laden
        story_images.push_back(LoadTexture("assets/graphics/backgrounds/Gamestart_scene_1.png")); // 4 Sekunden
        story_images.push_back(LoadTexture("assets/graphics/backgrounds/Gamestart_scene_2.png")); // 2 Sekunden

        durations.push_back(4.0f);
        durations.push_back(2.0f);

        // Timer für das erste Bild setzen
        timer = durations[0];
    }

    StoryScene::~StoryScene()
    {
        for (auto& tex : story_images) {
            UnloadTexture(tex);
        }
    }

    void StoryScene::Update()
    {
        // Wenn du delta_time brauchst, hole es aus deinem Timer-System,
        // z.B. mit GetFrameTime() von raylib:
        float delta_time = GetFrameTime();

        // Hier deine Story-Logik, z.B. Timer runterzählen
        timer -= delta_time;
        if (timer <= 0.0f)
        {
            current_index++;
            if (current_index >= story_images.size())
            {
                // Story zu Ende → Level1Scene starten
                game::core::Store::stage->ReplaceWithNewScene("story", "level1", std::make_unique<Level1Scene>());
            }
            else
            {
                timer = durations[current_index];
            }
        }

        // Enter-Taste direkt weiter
        if (IsKeyPressed(KEY_ENTER))
        {
            game::core::Store::stage->ReplaceWithNewScene("story", "level1", std::make_unique<Level1Scene>());
        }
    }

    void StoryScene::Draw()
    {
        if (!story_images.empty() && current_index < story_images.size()) {
            DrawTexture(story_images[current_index], 0, 0, WHITE);
        }
    }

}
