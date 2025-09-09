#ifndef SPECIALVAMPIRE_H
#define SPECIALVAMPIRE_H

#pragma once

#include "../EnemyExtendedBaseClass.h"
#include "raymath.h"
#include <string>
#include <vector>
#include <memory>
#include "../config_enemys.h.in"

namespace enemy
{

    class SpecialVampire : public EnemyExtendedBaseClass
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

        SpecialVampire(Vector2 start_position);
        ~SpecialVampire() override;

        // Implementierung der Angriffsfunktionen
        void Melee_Attack() override;
        void Range_Attack() override;


        void Update_AI(float delta_time, Vector2 player_position) override;


        void Tick(float delta_time) override;


        void Draw() override;
    };
}

#endif //SPECIALVAMPIRE_H
