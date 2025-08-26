//
// Created by Kruse on 23/05/2025.
//

#include <valarray>
#include "EnemyBaseClass.h"
#include "CollisionManager.h"
#include "CollisionResponse.h"
#include "PlayerBaseClass.h"
#include "PlayerProjectile.h"

namespace enemy
{
Enemy_Base_Class::Enemy_Base_Class(std::string name, int health, float movement_speed, int damage, int value,
    const char* sprite_path, const char* projectile_sprite_path,Vector2 start_position, int width, int height, float cooldown_Duration)
    : enemy_Name(name), enemy_Health(health), enemy_Movement_Speed(movement_speed), enemy_Damage(damage),
      enemy_Value(value),attack_Cooldown_Duration(cooldown_Duration), attack_Cooldown_Timer(0.0f), is_Moving(false)
    {
    hitbox = {start_position.x, start_position.y, (float)width, (float)height};
    sprite = LoadTexture(sprite_path);
    }

Enemy_Base_Class::~Enemy_Base_Class()
{
    UnloadTexture(sprite);
}

    void Enemy_Base_Class::Take_Damage(int damage_amount)
{
    this->enemy_Health -= damage_amount;

    // Prüft, ob der Gegner gestorben ist
    if (this->enemy_Health <= 0)
    {
        // Markiert das Objekt zur Zerstörung
        this->Mark_For_Destruction();
    }
}

void Enemy_Base_Class::Pathfinding(float target_Position_X, float target_Position_Y, float delta_Time)
{
    // Berechnet den Richtungs-Vektor vom Gegner zum Ziel.
    float delta_Vector_X = target_Position_X - this->hitbox.x;
    float delta_Vector_Y = target_Position_Y - this->hitbox.y;

    // Berechnet die exakte Distanz zum Ziel.
    float distance_To_Target = std::sqrt(delta_Vector_X * delta_Vector_X + delta_Vector_Y * delta_Vector_Y);

    // Sicherheitscheck, um eine Division durch Null (Fehler den ich bei meinem Test oft hatte) zu verhindern.
    // Die Bewegung wird nur ausgeführt, wenn der Gegner sein Ziel noch nicht erreicht hat.
    if (distance_To_Target > 0.01f)
    {
        // Normalisiert den Vektor: Macht den Pfeil zur reinen Richtung, indem seine Länge auf 1 gekürzt wird.
        // Dies ist der entscheidende Schritt für eine konstante Geschwindigkeit.
        float normalized_Direction_X = delta_Vector_X / distance_To_Target;
        float normalized_Direction_Y = delta_Vector_Y / distance_To_Target;

        // Holt die individuelle Geschwindigkeit dieses Gegners.
        float current_Movement_Speed = this->Get_Movement_Speed();

        // Berechnet die "Schrittgröße" für diesen einzelnen Frame.
        float movement_Step_Size = current_Movement_Speed * delta_Time;

        // Bewegt die Hitbox des Gegners um den kleinen Schritt in die korrekte Richtung.
        this->hitbox.x += normalized_Direction_X * movement_Step_Size;
        this->hitbox.y += normalized_Direction_Y * movement_Step_Size;

    }
    is_Moving= true;
}

//Core Methoden
void Enemy_Base_Class::Tick(float delta_time)
{
    if (attack_Cooldown_Timer > 0)
    {
        attack_Cooldown_Timer -= delta_time;
    }
    // Wenn der Pathfinding die Position veränder dann this->is_Moving = true;
}
    void Enemy_Base_Class::On_Collision(std::shared_ptr<Collidable> other)
{
    Collision_Type other_Type = other->Get_Collision_Type();

    switch(other_Type)
    {
        case Collision_Type::WALL:
        {
            if (this->is_Moving)
            {
                CollisionResponse::Resolve_Overlap(shared_from_this(), other);
            }
            break;
        }

        case Collision_Type::ENEMY_SPAWNER:
        {
            // Ein Spawner sollte keine Kollisionen mit Feinden auslösen, die sie selbst zum Löschen markieren.
            // der Spawner verwaltet sich selbst .
            // Wenn der Spawner verschwinden soll, muss die Logik dafür im Spawner selbst liegen.
            break;
        }

        case Collision_Type::PLAYER:
        {
            if (this->is_Moving)
            {
                CollisionResponse::Resolve_Overlap(shared_from_this(), other);
            }

            if (attack_Cooldown_Timer <= 0)
            {
                if (auto player = std::dynamic_pointer_cast<Player_Base_Class>(other))
                {
                    player->Take_Damage(this->enemy_Damage);
                    this->attack_Cooldown_Timer = this->attack_Cooldown_Duration;
                }
            }
            break;
        }

        case Collision_Type::PLAYER_PROJECTILE:
        {
            // Füge dem Gegner Schaden zu
            if(auto projectile = std::dynamic_pointer_cast<game::Player_Projectile>(other))
            {
                this->Take_Damage(projectile->damage);

                // Markiere das Projektil für die Zerstörung
                projectile->Mark_For_Destruction();
            }
            break;
        }

        case Collision_Type::CONSUMABLE:
        {
            // Ihre geplante Logik
            break;
        }

        default:
            break;
    }
}

void Enemy_Base_Class::Draw()
{

}
    void Enemy_Base_Class::Range_Attack() {
    // Diese Methode hat noch keine Logik
}

    void Enemy_Base_Class::Melee_Attack() {
}

}