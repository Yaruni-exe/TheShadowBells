#include "EnemyExtendedBaseClass.h"
#include "raymath.h"
#include <cmath>
#include "CollisionResponse.h"
#include "PlayerBaseClass.h"

namespace enemy
{
    // Die Take_Damage-Methode aus der neuen Version
    void EnemyExtendedBaseClass::Take_Damage(int damage_amount)
    {
        enemy_Health -= damage_amount;
        if (this->enemy_Health <= 0)
        {
            this->Mark_For_Destruction();
        }
    }

    // Die Pathfinding-Methode aus der neuen Version
    void EnemyExtendedBaseClass::Pathfinding(float target_Position_X, float target_Position_Y, float delta_Time)
    {
        float delta_Vector_X = target_Position_X - this->hitbox.x;
        float delta_Vector_Y = target_Position_Y - this->hitbox.y;
        float distance_To_Target = std::sqrt(delta_Vector_X * delta_Vector_X + delta_Vector_Y * delta_Vector_Y);
        float attack_Range = 16.0;

        if (distance_To_Target > attack_Range)
        {
            is_Moving = true;
            float normalized_Direction_X = delta_Vector_X / distance_To_Target;
            float normalized_Direction_Y = delta_Vector_Y / distance_To_Target;
            float current_Movement_Speed = this->enemy_Movement_Speed;
            float movement_Step_Size = current_Movement_Speed * delta_Time;

            this->hitbox.x += normalized_Direction_X * movement_Step_Size;
            this->hitbox.y += normalized_Direction_Y * movement_Step_Size;
        }
        else
        {
            is_Moving = false;
        }
    }

    // Die On_Collision-Methode aus der neuen Version
    void EnemyExtendedBaseClass::On_Collision(std::shared_ptr<Collidable> other)
    {
        Collision_Type other_Type = other->Get_Collision_Type();

        switch(other_Type)
        {
            case Collision_Type::WALL:
            case Collision_Type::PLAYER:
            {
                if (this->is_Moving)
                {
                    CollisionResponse::Resolve_Overlap(shared_from_this(), other);
                }

                if (other_Type == Collision_Type::PLAYER)
                {
                    if (attack_Cooldown_Timer <= 0)
                    {
                        if (auto player = std::dynamic_pointer_cast<Player_Base_Class>(other))
                        {
                            player->Take_Damage(this->enemy_Damage);
                            this->attack_Cooldown_Timer = this->attack_Cooldown_Duration;
                        }
                    }
                }
                break;
            }
            case Collision_Type::PLAYER_PROJECTILE:
            {
                // Die Logik für Projektile wird hier behandelt
                break;
            }
            case Collision_Type::ENEMY_SPAWNER:
            case Collision_Type::CONSUMABLE:
            {
                // Die Logik für Spawner und Consumables
                break;
            }
            default:
                break;
        }
    }

    // Die Draw-Methode, die die Textur zeichnet
    void EnemyExtendedBaseClass::Draw()
    {
        if (sprite.id > 0)
        {
            DrawTextureV(this->sprite, {this->hitbox.x, this->hitbox.y}, WHITE);
        }
    }
}