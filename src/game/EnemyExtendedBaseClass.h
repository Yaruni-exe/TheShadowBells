#pragma once

#include "EnemyBaseClass.h"
#include <memory>
#include "raylib.h"

namespace enemy
{
    enum class EnemyState { IDLE, CHASING, ATTACKING, DYING };

    class EnemyExtendedBaseClass : public Enemy_Base_Class
    {
    protected:
        EnemyState current_state;
        float attack_animation_timer;

        // --- Hit Feedback ---
        float hit_timer = 0.0f;          // Zeit, die Gegner "getroffen" ist
        float hit_duration = 1.0f;       // Dauer des Hit-Feedbacks in Sekunden
        Color hit_color = {108, 76, 68, 255}; // #6c4c44

    public:
        EnemyExtendedBaseClass(std::string name, int health, float movement_speed, int damage, int value,
                               const char* sprite_path, const char* projectile_sprite_path, Vector2 start_position, int width, int height,
                               float cooldown_duration)
            : Enemy_Base_Class(name, health, movement_speed, damage, value, sprite_path, projectile_sprite_path,
                               start_position, width, height, cooldown_duration),
              current_state(EnemyState::IDLE),
              attack_animation_timer(0.0f) {}

        virtual ~EnemyExtendedBaseClass() = default;

        virtual void Update_AI(float delta_time, Vector2 player_position) = 0;
        virtual void Melee_Attack() = 0;
        virtual void Range_Attack() = 0;

        // --- Überschreibungen ---
        void Take_Damage(int damage_amount) ;
        void Pathfinding(float target_Position_X, float target_Position_Y, float delta_Time) override;
        void On_Collision(std::shared_ptr<Collidable> other) override;
        void Draw() override;
        virtual void Tick(float delta_time) override;
    };
}
