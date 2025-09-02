#include "Explosion.h"
#include <iostream>

// Globale Textur, damit sie nur einmal geladen wird
Texture2D explosion_texture = LoadTexture("assets/graphics/interactables/Explosion.png");

Explosion::Explosion(Vector2 start_position)
    : Collidable(), // Ruft den Standardkonstruktor der Basisklasse auf
      animation(Vector2{32, 32}, explosion_texture, 7, 7)
{
    hitbox = {start_position.x, start_position.y, 32, 32};
    lifespan = 0.5f; // Lebensdauer in Sekunden
}

Explosion::~Explosion() {
    UnloadTexture(explosion_texture);
}

void Explosion::Tick(float delta_time) {
    lifespan -= delta_time;
    if (lifespan <= 0.0f) {
        Mark_For_Destruction();
    }
}

void Explosion::Draw() {
    Vector2 draw_position = {hitbox.x, hitbox.y};
    animation.Draw_Current_Frame(draw_position);
    animation.Next_Frame();
}

Collision_Type Explosion::Get_Collision_Type() const {
    return Collision_Type::EXPLOSION;
}

void Explosion::On_Collision(std::shared_ptr<Collidable> other) {
    // Handle collisions with enemies
    if (other->Get_Collision_Type() == Collision_Type::ENEMY) {
        // Here you would apply damage to the enemy
    }
}
