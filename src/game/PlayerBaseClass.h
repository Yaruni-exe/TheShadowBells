//
// Created by Kruse on 23/05/2025.
//
#pragma once


#include "raylib.h"
#include "Collidable.h"
#include "CollisionManager.h"
#include "../Config.h.in"
#include "raymath.h"
#include "PlayerProjectile.h"
#include "Object_Manager.h"
#include <memory>

class Collision_Manager;

enum Facing_Direction {UP, DOWN, LEFT, RIGHT, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT};

class Player_Base_Class : public Collidable
{
protected:

    float player_Health;
    int player_Max_Health;
    float player_Movement_Speed;
    int player_Damage;
    int player_Score = 0;
    Vector2 player_Pos;
    Vector2 previous_Position;
    Collision_Manager* manager_Ptr;

    float melee_Cooldown;
    float ranged_Cooldown;
    bool inventory_Is_Full;
    Facing_Direction facing_Direction;
    bool is_Moving;


    Texture2D maintex= LoadTexture("assets/graphics/ball.png");

    float projectile_Speed;

    Object_Manager& om;

    Vector2 sprite_offset;

public:
    // Konstruktor
    Player_Base_Class(int max_Health, float movement_Speed, int damage, Vector2 start_Position, Object_Manager& om);

    // Destruktor
    ~Player_Base_Class() override;
    void Player_Input();
    void Tick(float delta_time) override;
    void virtual On_Collision(std::shared_ptr<Collidable> other) override;
    virtual void Draw() override;

    Vector2 Get_Position() const { return player_Pos; }

    void Update_Previous_Position();
    void Update_Facing_Direction();

    void Melee_Attack();
    virtual void Ranged_Attack();
    void Use_Item();
    void Heal(float amount);

    Collision_Type Get_Collision_Type() const override;
    Vector2 Get_Player_Pos();
    Vector2 Get_Player_Center();

    virtual void Take_Damage(int damage);
    float Get_Health() const { return player_Health; }
    int Get_Max_Health() const { return player_Max_Health; }


    void AddScore(int amount) { player_Score += amount; }

    int GetScore() const { return player_Score; }
};