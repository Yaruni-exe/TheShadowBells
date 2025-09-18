//
// Created by Manza on 6/22/2025.
//

#pragma once
#include "raylib.h"
#include "Collidable.h"

namespace game {

    class Enemy_Projectile : public Collidable {
    public:
        Vector2 position;
        Vector2 velocity;
        bool is_active;
        int damage;
        Texture2D sprite;
        Rectangle hitbox;


        Enemy_Projectile(Vector2 start_position, Vector2 direction, float projectile_speed, int damage, const char* sprite_path);
        ~Enemy_Projectile();

        void Tick(float delta_time) override;
        void Draw() override;


        Collision_Type Get_Collision_Type() const override;
        void On_Collision(std::shared_ptr<Collidable> other) override;
    };
}