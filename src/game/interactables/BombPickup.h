#pragma once

#include "../Collidable.h"
#include "../../core/RepeatAnimation.h"
#include "raylib.h"

class Bomb_Pickup : public Collidable {
private:
    RepeatAnimation animation;
    static Texture2D bomb_texture;

public:
    Bomb_Pickup(Vector2 position);
    ~Bomb_Pickup() override;

    static void Load_Texture();
    static void Unload_Texture();

    void Tick(float delta_time) override;
    void Draw() override;
    void On_Collision(std::shared_ptr<Collidable> other) override;

    Collision_Type Get_Collision_Type() const override;
};