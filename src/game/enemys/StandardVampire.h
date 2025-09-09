#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include <memory>
#include "../EnemyExtendedBaseClass.h"

namespace enemy
{
    class StandardVampire : public EnemyExtendedBaseClass
    {
    private:
        // Statische Texturen, die von allen Vampir-Instanzen geteilt werden
        static std::vector<Texture2D> run_textures;
        static int frames_per_direction[4];
        static float frame_widths[4];
        static bool textures_loaded;

        // Instanzvariablen für die Animation
        int current_direction_index;
        float animation_timer;
        int current_frame;
        float frames_per_second;

    public:
        StandardVampire(Vector2 start_position);
        ~StandardVampire() override;

        void Update_AI(float delta_time, Vector2 player_position) override;
        void Tick(float delta_time) override;

        void Melee_Attack() override;
        void Range_Attack() override;

        void Draw() override;
    };
}