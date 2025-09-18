#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include <memory>
#include "Scene.h"

namespace game::scenes {

    class StoryScene : public game::core::Scene {
    private:
        std::vector<Texture2D> story_images;
        std::vector<float> durations; // Dauer jedes Bildes in Sekunden
        size_t current_index;
        float timer;

    public:
        StoryScene();
        ~StoryScene();

        void Update() override;
        void Draw() override;
    };

}
