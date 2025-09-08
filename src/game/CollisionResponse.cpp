#include "CollisionResponse.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include "EnemyBaseClass.h"
#include "PlayerBaseClass.h"



// Überprüft, ob ein Objekt statisch ist, basierend auf seiner Kollisionsart.
bool Is_Static(std::shared_ptr<Collidable> obj)
{
    Collision_Type type = obj->Get_Collision_Type();
    return (type == Collision_Type::BOMB_WALL ||
            type == Collision_Type::GENERATOR ||
            type == Collision_Type::DOOR ||
            type == Collision_Type::BOMB_PICKUP ||
            type == Collision_Type::WALL);
}

void CollisionResponse::Resolve_Overlap(std::shared_ptr<Collidable> obj_A, const std::shared_ptr<Collidable> obj_B)
{
    // Hole die Hitboxen der beiden Objekte.
    Rectangle hitbox_A = obj_A->Get_Hitbox();
    Rectangle hitbox_B = obj_B->Get_Hitbox();

    // Berechne die Überlappung auf beiden Achsen.
    float overlap_X = std::min(hitbox_A.x + hitbox_A.width, hitbox_B.x + hitbox_B.width) - std::max(hitbox_A.x, hitbox_B.x);
    float overlap_Y = std::min(hitbox_A.y + hitbox_A.height, hitbox_B.y + hitbox_B.height) - std::max(hitbox_A.y, hitbox_B.y);

    // Prüfe, ob die Objekte statisch sind.
    bool is_A_static = Is_Static(obj_A);
    bool is_B_static = Is_Static(obj_B);

    // Wenn beide statisch sind, tue nichts.
    if (is_A_static && is_B_static)
    {
        return;
    }

    // Wenn A statisch ist, muss B dynamisch sein, da wir oben schon geprüft haben,
    // ob beide statisch sind.
    if (is_A_static)
    {
        if (overlap_X < overlap_Y)
        {
            float move_x = overlap_X;
            if (hitbox_A.x < hitbox_B.x) move_x *= -1;
            const_cast<std::shared_ptr<Collidable>&>(obj_B)->Set_Position({ hitbox_B.x - move_x, hitbox_B.y });
        }
        else
        {
            float move_y = overlap_Y;
            if (hitbox_A.y < hitbox_B.y) move_y *= -1;
            const_cast<std::shared_ptr<Collidable>&>(obj_B)->Set_Position({ hitbox_B.x, hitbox_B.y - move_y });
        }
    }
    // Wenn B statisch ist, muss A dynamisch sein.
    else if (is_B_static)
    {
        if (overlap_X < overlap_Y)
        {
            float move_x = overlap_X;
            if (hitbox_A.x < hitbox_B.x) move_x *= -1;
            obj_A->Set_Position({ hitbox_A.x + move_x, hitbox_A.y });
        }
        else
        {
            float move_y = overlap_Y;
            if (hitbox_A.y < hitbox_B.y) move_y *= -1;
            obj_A->Set_Position({ hitbox_A.x, hitbox_A.y + move_y });
        }
    }
    // Wenn beide dynamisch sind.
    else
    {
        if (overlap_X < overlap_Y)
        {
            float move_x = overlap_X;
            if (hitbox_A.x < hitbox_B.x) move_x *= -1;
            obj_A->Set_Position({ hitbox_A.x + move_x / 2.0f, hitbox_A.y });
            const_cast<std::shared_ptr<Collidable>&>(obj_B)->Set_Position({ hitbox_B.x - move_x / 2.0f, hitbox_B.y });
        }
        else
        {
            float move_y = overlap_Y;
            if (hitbox_A.y < hitbox_B.y) move_y *= -1;
            obj_A->Set_Position({ hitbox_A.x, hitbox_A.y + move_y / 2.0f });
            const_cast<std::shared_ptr<Collidable>&>(obj_B)->Set_Position({ hitbox_B.x, hitbox_B.y - move_y / 2.0f });
        }
    }
}


void CollisionResponse::Apply_Damage(std::shared_ptr<Collidable> target, int damage)
{
    if (!target) return;

    if (auto player = std::dynamic_pointer_cast<Player_Base_Class>(target))
    {
        player->Take_Damage(damage);
    }
    else if (auto enemy = std::dynamic_pointer_cast<enemy::Enemy_Base_Class>(target))
    {
        enemy->Take_Damage(damage);
    }
}

void CollisionResponse::Mark_For_Destruction(std::shared_ptr<Collidable> obj_To_Destroy)
{
    if (!obj_To_Destroy) return;
    obj_To_Destroy->Mark_For_Destruction();
}