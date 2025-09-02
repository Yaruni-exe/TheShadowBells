#pragma once

#include "../Collidable.h"
#include "../../core/RepeatAnimation.h"
#include "raylib.h"

enum class BombWallState {
    IDLE,
    DESTROYING
};

class Bomb_Wall : public Collidable {
private:
    static Texture2D wall_texture;
    RepeatAnimation destroy_animation;
    BombWallState state;
    bool animation_finished = false;

public:
    Bomb_Wall(Vector2 position);
    ~Bomb_Wall() override;

    static void Load_Texture();
    static void Unload_Texture();

    void Tick(float delta_time) override;
    void Draw() override;
    void On_Collision(std::shared_ptr<Collidable> other) override;

    Collision_Type Get_Collision_Type() const override;
};