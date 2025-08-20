#include "Level1Spawner.h"
#include <iostream>
#include "../enemys/enemys_list.h"
#include "../../config_enemys.h.in"
#include "../PlayerProjectile.h"
#include <numeric>
#include <raymath.h>
#include <map>

Level1_Spawner::Level1_Spawner(Rectangle spawner_Area,
                               Object_Manager& om,
                               std::vector<enemy::Enemy_Base_Class*>& enemy_List,
                               std::shared_ptr<Player_Base_Class> player_ptr)
  : Enemy_Spawner(spawner_Area, om, enemy_List, game::EnemyConfig::kSpawner1_SpawnRate, game::EnemyConfig::kSpawner1_MaxEnemies),
      player_ptr_(player_ptr),
      spawn_timer(game::EnemyConfig::kSpawner1_SpawnRate),
      max_enemies_per_instance_(game::EnemyConfig::kSpawner1_MaxEnemies),
      health_(1)
{
    this->hitbox = spawner_Area;
    this->spawner_sprite = LoadTexture("assets/graphics/spawner/Spawner_outside.png");
}

Level1_Spawner::~Level1_Spawner()
{
    if (spawner_sprite.id > 0)
    {
        UnloadTexture(this->spawner_sprite);
    }
}

// **DIESE FUNKTION FEHLTE VERMUTLICH IN IHRER DATEI**
void Level1_Spawner::Update_And_Count_Spawned_Enemies(std::map<enemy::EnemyType, int>& counts)
{
    counts.clear();
    spawned_enemies_.erase(std::remove_if(spawned_enemies_.begin(), spawned_enemies_.end(),
        [&counts](const std::weak_ptr<enemy::Enemy_Base_Class>& e) {
            if (auto locked_enemy = e.lock()) {
                if (auto insect = std::dynamic_pointer_cast<enemy::StandardVampire>(locked_enemy)) {
                    counts[enemy::EnemyType::STANDARD_VAMPIRE]++;
                }
                return false;
            }
            return true;
        }), spawned_enemies_.end());
}

void Level1_Spawner::Tick(float delta_time)
{
    if (health_ <= 0) return;

    // Rufen Sie die Tick-Methode der Basisklasse auf, die die Kollisionsprüfung durchführt
    //Enemy_Spawner::Tick(delta_time);

    // Ihre ursprüngliche Logik zur Verwaltung der gespawnten Feinde
    spawn_timer -= delta_time;
    if (spawn_timer <= 0.0f)
    {
        spawn_timer = spawn_Rate_;
        std::map<enemy::EnemyType, int> on_field_counts;
        Update_And_Count_Spawned_Enemies(on_field_counts);

        if (spawned_enemies_.size() < max_enemies_per_instance_)
        {
            std::vector<SpawnableEnemy> possible_spawns;
            int total_weight = 0;
            for (const auto& spawn_info : game::EnemyConfig::kSpawner1_EnemyPool)
            {
                int current_count = on_field_counts.count(spawn_info.type) ? on_field_counts[spawn_info.type] : 0;
                if (current_count < spawn_info.max_on_field) {
                    possible_spawns.push_back(spawn_info);
                    total_weight += spawn_info.weight;
                }
            }
            if (!possible_spawns.empty())
            {
                int random_value = GetRandomValue(0, total_weight - 1);
                int cumulative_weight = 0;
                for (const auto& spawn_info : possible_spawns)
                {
                    cumulative_weight += spawn_info.weight;
                    if (random_value < cumulative_weight)
                    {
                        Vector2 spawn_pos = {0.0f, 0.0f};
                        bool valid_pos_found = false;
                        const int max_tries = 10;
                        for (int i = 0; i < max_tries; ++i) {
                            spawn_pos = {
                                hitbox.x + (float)GetRandomValue(0, (int)hitbox.width - game::Config::Player_Hitbox_Width),
                                hitbox.y + (float)GetRandomValue(0, (int)hitbox.height - game::Config::Player_Hitbox_Height)
                            };

                            Rectangle new_enemy_hitbox = {spawn_pos.x, spawn_pos.y, game::Config::Player_Hitbox_Width, game::Config::Player_Hitbox_Height};

                            if (Is_Space_Free(new_enemy_hitbox)) {
                                if (auto player = player_ptr_.lock()) {
                                    if (CheckCollisionRecs(new_enemy_hitbox, player->Get_Hitbox())) {
                                        continue;
                                    }
                                }

                                bool collision_with_enemy = false;
                                for (const auto& enemy_weak_ptr : spawned_enemies_) {
                                    if (auto enemy_shared_ptr = enemy_weak_ptr.lock()) {
                                        if (CheckCollisionRecs(new_enemy_hitbox, enemy_shared_ptr->Get_Hitbox())) {
                                            collision_with_enemy = true;
                                            break;
                                        }
                                    }
                                }
                                if (collision_with_enemy) continue;

                                valid_pos_found = true;
                                break;
                            }
                        }

                        if (valid_pos_found) {
                            enemy::Enemy_Base_Class* new_enemy_raw = nullptr;
                            switch (spawn_info.type) {
                                case enemy::EnemyType::STANDARD_VAMPIRE:
                                    new_enemy_raw = new enemy::StandardVampire(spawn_pos);
                                    break;
                            }

                            if (new_enemy_raw) {
                                auto new_enemy_shared = std::shared_ptr<enemy::Enemy_Base_Class>(new_enemy_raw);
                                object_manager_ref.AddObject(new_enemy_shared);
                                spawned_enemies_.push_back(new_enemy_shared);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}


void Level1_Spawner::Draw()
{
    DrawTextureV(this->spawner_sprite, {(float)this->hitbox.x, (float)this->hitbox.y}, WHITE);
}

void Level1_Spawner::On_Collision(std::shared_ptr<Collidable> other)
{
    if (other->Get_Collision_Type() == Collision_Type::PLAYER_PROJECTILE)
    {
        this->health_--;
        if (health_ <= 0)
        {
            this->Mark_For_Destruction();
        }
    }
}

enemy::Enemy_Base_Class* Level1_Spawner::createEnemy(Vector2 position)
{
    return new enemy::StandardVampire(position);
}