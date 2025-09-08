#pragma once

#include "raylib.h"
#include <memory>
#include "../Collidable.h"
#include "../../core/SpriteAnimated.h"
#include "../../core/Texture2d.h"

enum class BombWallState
{
    IDLE,
    DESTROYING
};

class Bomb_Wall : public Collidable
{
private:
    game::core::SpriteAnimated destroy_animation;
    BombWallState state;
    static Texture2D wall_texture;
    static std::shared_ptr<game::core::Texture2D> destroy_texture_ptr;

public:
    Bomb_Wall(Vector2 position);
    ~Bomb_Wall() override;

    void Tick(float delta_time) override;
    void Draw() override;
    void On_Collision(std::shared_ptr<Collidable> other) override;
    Collision_Type Get_Collision_Type() const override;

    BombWallState Get_State() const { return this->state; }

    static void Load_Texture();
    static void Unload_Texture();
};