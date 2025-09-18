#include "EnemyExtendedBaseClass.h"
#include "raymath.h"
#include <cmath>
#include "CollisionResponse.h"
#include "PlayerBaseClass.h"
#include "PlayerProjectile.h"
#include <memory>

namespace enemy
{
    void EnemyExtendedBaseClass::Take_Damage(int damage_amount)
    {
        enemy_Health -= damage_amount;

        if (enemy_Health > 0) {
            hit_timer = hit_duration; // startet Hit-Feedback
        } else {
            this->Mark_For_Destruction();
        }
    }

    void EnemyExtendedBaseClass::Tick(float delta_time)
    {
        if (attack_Cooldown_Timer > 0)
            attack_Cooldown_Timer -= delta_time;

        if (hit_timer > 0.0f)
            hit_timer -= delta_time;
    }

    void EnemyExtendedBaseClass::Draw()
    {
        if (sprite.id > 0)
        {
            Color draw_color = WHITE;

            if (hit_timer > 0.0f)
            {
                draw_color = hit_color; // kurz die Hit-Farbe anzeigen
            }

            DrawTextureV(sprite, {hitbox.x, hitbox.y}, draw_color);
        }
    }

    void EnemyExtendedBaseClass::Pathfinding(float target_Position_X, float target_Position_Y, float delta_Time)
    {
        float delta_Vector_X = target_Position_X - this->hitbox.x;
        float delta_Vector_Y = target_Position_Y - this->hitbox.y;
        float distance_To_Target = std::sqrt(delta_Vector_X * delta_Vector_X + delta_Vector_Y * delta_Vector_Y);
        float attack_Range = 16.0;

        if (distance_To_Target > attack_Range)
        {
            current_state = EnemyState::CHASING;
            is_Moving = true;
            float normalized_Direction_X = delta_Vector_X / distance_To_Target;
            float normalized_Direction_Y = delta_Vector_Y / distance_To_Target;
            float current_Movement_Speed = this->enemy_Movement_Speed * delta_Time;

            this->hitbox.x += normalized_Direction_X * current_Movement_Speed;
            this->hitbox.y += normalized_Direction_Y * current_Movement_Speed;

            this->is_Moving = true;
        }
        else
        {
            current_state = EnemyState::IDLE;
            is_Moving = false;
        }
    }

    void EnemyExtendedBaseClass::On_Collision(std::shared_ptr<Collidable> other)
    {
        Collision_Type other_Type = other->Get_Collision_Type();

        if (other.get() == this) return;

        switch (other_Type)
        {
            case Collision_Type::ENEMY:
            case Collision_Type::WALL:
            case Collision_Type::BOMB_WALL:
            case Collision_Type::GENERATOR:
            case Collision_Type::DOOR:
                if (is_Moving)
                    CollisionResponse::Resolve_Overlap(shared_from_this(), other);
                break;

            case Collision_Type::PLAYER:
                if (is_Moving)
                    CollisionResponse::Resolve_Overlap(shared_from_this(), other);

                if (attack_Cooldown_Timer <= 0)
                {
                    if (auto player = std::dynamic_pointer_cast<Player_Base_Class>(other))
                    {
                        player->Take_Damage(enemy_Damage);
                        attack_Cooldown_Timer = attack_Cooldown_Duration;
                    }
                }
                break;

            case Collision_Type::PLAYER_PROJECTILE:
                if (auto projectile = std::dynamic_pointer_cast<game::Player_Projectile>(other))
                {
                    Take_Damage(projectile->damage);
                    projectile->Mark_For_Destruction();
                }
                break;

            case Collision_Type::ENEMY_SPAWNER:
            case Collision_Type::CONSUMABLE:
                break;

            default:
                break;
        }
    }
}
