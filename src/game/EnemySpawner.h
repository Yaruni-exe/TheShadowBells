#pragma once

#include "raylib.h"
#include <vector>
#include <memory>
#include "EnemyBaseClass.h"
#include "Collidable.h"
#include "CollisionManager.h"
#include "../core/Object_Manager.h"

class Enemy_Spawner : public Collidable
{
public:
    Enemy_Spawner(Rectangle spawner_Area, Object_Manager& om,
                  std::vector<enemy::Enemy_Base_Class*>& enemy_List,
                  float spawn_Rate, int max_Enemies);

    virtual void Tick(float delta_time) override;
    virtual void Draw() override;
    virtual void On_Collision(std::shared_ptr<Collidable> other) override;
    virtual Collision_Type Get_Collision_Type() const override; // Hinzugefügt

protected:
    virtual enemy::Enemy_Base_Class* createEnemy(Vector2 position) = 0;
    bool Is_Space_Free(const Rectangle& newHitbox) const;

    Rectangle spawner_Area;
    Object_Manager& object_manager_ref;
    std::vector<enemy::Enemy_Base_Class*>& enemy_List;
    float spawn_Rate_;
    int max_Enemies_;
    float time_Since_Last_Spawn_;
};