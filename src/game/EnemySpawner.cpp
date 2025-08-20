#include "EnemySpawner.h"
#include "raylib.h"
#include "CollisionManager.h"
#include <iostream>

Enemy_Spawner::Enemy_Spawner(Rectangle spawner_Area, Object_Manager& om,
                             std::vector<enemy::Enemy_Base_Class*>& enemy_List,
                             float spawn_Rate, int max_Enemies)
    : spawner_Area(spawner_Area), object_manager_ref(om), enemy_List(enemy_List),
      spawn_Rate_(spawn_Rate), max_Enemies_(max_Enemies), time_Since_Last_Spawn_(0.0f) {}

void Enemy_Spawner::Tick(float delta_Time)
{
    // Diese generische Tick-Methode wird von der abgeleiteten Klasse aufgerufen.
    time_Since_Last_Spawn_ += delta_Time;

    if (time_Since_Last_Spawn_ >= (1.0f / spawn_Rate_) &&
        (int)enemy_List.size() < max_Enemies_) {

        Vector2 spawnPos = {
            static_cast<float>(GetRandomValue((int)spawner_Area.x, (int)(spawner_Area.x + spawner_Area.width - 32))),
            static_cast<float>(GetRandomValue((int)spawner_Area.y, (int)(spawner_Area.y + spawner_Area.height - 32)))
        };

        if (Is_Space_Free({ spawnPos.x, spawnPos.y, 32.0f, 32.0f })) {
            enemy::Enemy_Base_Class* new_Enemy = createEnemy(spawnPos);
            if (new_Enemy) {
                object_manager_ref.AddObject(std::shared_ptr<enemy::Enemy_Base_Class>(new_Enemy));
            }
        }
        time_Since_Last_Spawn_ = 0.0f;
    }
}

bool Enemy_Spawner::Is_Space_Free(const Rectangle& newHitbox) const
{
    for (const auto& obj : object_manager_ref.managed_objects) {
        if (obj->Get_Collision_Type() == Collision_Type::ENEMY_SPAWNER && CheckCollisionRecs(newHitbox, obj->Get_Hitbox())) {
            continue;
        }

        if (obj->Get_Collision_Type() == Collision_Type::WALL || obj->Get_Collision_Type() == Collision_Type::ENEMY) {
            if (CheckCollisionRecs(newHitbox, obj->Get_Hitbox())) {
                return false;
            }
        }
    }
    return true;
}

Collision_Type Enemy_Spawner::Get_Collision_Type() const
{
    return Collision_Type::ENEMY_SPAWNER;
}

void Enemy_Spawner::Draw()
{
    DrawRectangleLinesEx(spawner_Area, 2, GREEN);
}

void Enemy_Spawner::On_Collision(std::shared_ptr<Collidable> other) {

}