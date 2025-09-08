#include "Explosion.h"
#include <iostream>

Texture2D Explosion::explosion_texture = {0};

void Explosion::Load_Texture() {
    if (explosion_texture.id == 0) {
        explosion_texture = LoadTexture("assets/graphics/interactables/Explosion.png");
    }
}

void Explosion::Unload_Texture() {
    if (explosion_texture.id != 0) {
        UnloadTexture(explosion_texture);
        explosion_texture.id = 0;
    }
}

Explosion::Explosion(Vector2 start_position)
    : Collidable(),
      animation(Vector2{32, 32}, explosion_texture, 7, 7, 10.0f)
{
    hitbox = {start_position.x, start_position.y, 32, 32};
    lifespan = 0.5f;
}

Explosion::~Explosion() {
    // Die Textur wird nun statisch verwaltet, also nicht hier entladen
}

void Explosion::Tick(float delta_time) {
    lifespan -= delta_time;
    if (lifespan <= 0.0f) {
        Mark_For_Destruction();
    }
    animation.Next_Frame(delta_time);
}

void Explosion::Draw() {
    Vector2 draw_position = {hitbox.x, hitbox.y};
    animation.Draw_Current_Frame(draw_position);
}

Collision_Type Explosion::Get_Collision_Type() const {
    return Collision_Type::EXPLOSION;
}

void Explosion::On_Collision(std::shared_ptr<Collidable> other) {
    // ...
}
