#pragma once

#include "../EnemySpawner.h"
#include <vector>
#include <memory>
#include "Object_Manager.h"
#include "../PlayerBaseClass.h"
#include <map>
#include "../enemys/enemys_list.h"

class Level2_Spawner : public Enemy_Spawner
{
public:
    Level2_Spawner(Rectangle spawner_Area,
                   Object_Manager& om,
                   std::vector<enemy::Enemy_Base_Class*>& enemy_List, // Hinzufügen
                   std::shared_ptr<Player_Base_Class> player_ptr,
                   int max_enemies,
                   float spawn_rate);

    ~Level2_Spawner() override;
    void Tick(float delta_time) override;
    void Draw() override;
    void On_Collision(std::shared_ptr<Collidable> other) override;

private:
    void Update_And_Count_Spawned_Enemies(std::map<enemy::EnemyType, int>& counts);
    enemy::Enemy_Base_Class* createEnemy(Vector2 position) override;

    std::weak_ptr<Player_Base_Class> player_ptr_;
    float spawn_timer;
    int max_enemies_per_instance_; // This member is already here
    float spawn_rate_; // This member should be added
    int health_;
    Texture2D spawner_sprite;
    std::vector<std::weak_ptr<enemy::Enemy_Base_Class>> spawned_enemies_;
};
