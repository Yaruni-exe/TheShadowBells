#include "Gunslinger.h"
#include "../config.h.in"
#include "raymath.h"
#include <string>
#include <cmath>
#include "PlayerProjectile.h"
#include <algorithm>
#include <iostream>

const std::string idle_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Back.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Front.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Right.png",
};

const std::string run_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Back.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Front.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png",
};

const std::string attack_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Back.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Front.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Right.png",
};

Gunslinger::Gunslinger(Vector2 start_Position, Object_Manager& om)
    : Player_Base_Class(game::Config::player_Class_One_Max_Health, game::Config::player_Class_One_Movement_Speed,
        game::Config::player_Class_One_Damage, start_Position, om)
{
    this->ranged_Cooldown_Timer = 0.0f;
    for (int i = 0; i < 8; ++i) {
        idle_animations.emplace_back(size, idle_paths[i].c_str(), 7, 7);
        run_animations.emplace_back(size, run_paths[i].c_str(), 7, 7);
        attack_animations.emplace_back(size, attack_paths[i].c_str(), 7, 7);
    }
}

Gunslinger::~Gunslinger() {}

void Gunslinger::Tick(float delta_time, Vector2 worldMousePos) {
    Player_Base_Class::Tick(delta_time);

    mouseLook.Update(this->player_Pos, worldMousePos);
    mouse_World_Position = worldMousePos;

    if (this->ranged_Cooldown_Timer > 0.0f) {
        this->ranged_Cooldown_Timer -= delta_time;
    }

    if (currentState == PlayerState::ATTACK) {
        attackFrameCounter++;
        if (attackFrameCounter >= attackFrameCountTotal) {
            currentState = PlayerState::IDLE;
            attackFrameCounter = 0;
        }
    } else {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && this->ranged_Cooldown_Timer <= 0.0f) {
            this->Ranged_Attack();
            currentState = PlayerState::ATTACK;
            attack_animations[mouseLook.GetDirectionIndex()].First_Frame();
            attackFrameCounter = 0;
        } else if (is_Moving) {
            currentState = PlayerState::RUN;
        } else {
            currentState = PlayerState::IDLE;
        }
    }
}

void Gunslinger::Draw()
{
    int current_direction_index = mouseLook.GetDirectionIndex();
    RepeatAnimation* current_animation = nullptr;

    if (currentState == PlayerState::IDLE || currentState == PlayerState::RUN) {
        if (is_Moving) {
            current_animation = &run_animations[current_direction_index];
        } else {
            current_animation = &idle_animations[current_direction_index];
        }
    } else if (currentState == PlayerState::ATTACK) {
        current_animation = &attack_animations[current_direction_index];
    }

    if (current_animation) {
        // HIER  Zahlen für  Offset.
        Vector2 draw_position = {this->player_Pos.x - 16, this->player_Pos.y};

        current_animation->Draw_Current_Frame(draw_position);
        current_animation->Next_Frame();
    }
}

void Gunslinger::Ranged_Attack() {
    Vector2 target_Position = this->mouse_World_Position;

    float delta_vector_x = target_Position.x - this->hitbox.x;
    float delta_vector_y = target_Position.y - this->hitbox.y;
    float distance_to_target = std::sqrt(delta_vector_x * delta_vector_x + delta_vector_y * delta_vector_y);

    if (distance_to_target > 0) {
        Vector2 fire_direction = {
                delta_vector_x / distance_to_target,
                delta_vector_y / distance_to_target
        };
        std::shared_ptr<game::Player_Projectile> sp_temp_projectile(new game::Player_Projectile(
                Vector2{this->hitbox.x, this->hitbox.y},
                fire_direction,
                this->player_Damage,
                game::Config::player_Projectile_Sprite_Path));
        om.AddObject(sp_temp_projectile);
        this->ranged_Cooldown_Timer = 0.5f;
    }
}