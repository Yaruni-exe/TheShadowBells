#pragma once
#include "../Collidable.h"
#include "../../core/RepeatAnimation.h"
#include "raylib.h"
#include <memory>

class Explosion : public Collidable {
private:
    RepeatAnimation animation;
    float lifespan;
    static Texture2D explosion_texture;

public:
    Explosion(Vector2 start_position);
    ~Explosion() override;

    static void Load_Texture();
    static void Unload_Texture();

    void Tick(float delta_time) override;
    void Draw() override;
    Collision_Type Get_Collision_Type() const override;
    void On_Collision(std::shared_ptr<Collidable> other) override;
};
