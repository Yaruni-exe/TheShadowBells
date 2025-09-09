#include "BombWall.h"
#include "raylib.h"
#include <iostream>
#include "Explosion.h"

Texture2D Bomb_Wall::wall_texture = {0};
std::shared_ptr<game::core::Texture2D> Bomb_Wall::destroy_texture_ptr = nullptr;

void Bomb_Wall::Load_Texture() {
    if (wall_texture.id == 0) {
        wall_texture = LoadTexture("assets/graphics/Items/BombWall/Wand-Sprengstoff_Wald_Base_Sprite_horizontal.png");
    }
    // Lade die Animationstextur mit dem korrekten Konstruktor
    if (!destroy_texture_ptr) {
        destroy_texture_ptr = std::make_shared<game::core::Texture2D>("assets/graphics/Items/BombWall/Wand-Sprengstoff_Industrie_Opening_Animation_horizontal.png");
    }
}

void Bomb_Wall::Unload_Texture() {
    if (wall_texture.id != 0) {
        UnloadTexture(wall_texture);
        wall_texture.id = 0;
    }
    // Shared_ptr kümmert sich automatisch um die Entladung der Textur, wenn sie nicht mehr gebraucht wird
    destroy_texture_ptr = nullptr;
}

Bomb_Wall::Bomb_Wall(Vector2 position)
    // Verwende den Konstruktor mit den Positionsargumenten
    : destroy_animation(destroy_texture_ptr, 64, 64, 1, 10, 10, static_cast<int>(position.x), static_cast<int>(position.y)),
      state(BombWallState::IDLE) {
    this->hitbox = {position.x, position.y, 64, 64};
}

Bomb_Wall::~Bomb_Wall() {}

void Bomb_Wall::Tick(float delta_time) {
    if (state == BombWallState::DESTROYING) {
        // Rufe die Update-Methode der SpriteAnimated-Klasse auf
        destroy_animation.Update();
    }
}

void Bomb_Wall::On_Collision(std::shared_ptr<Collidable> other) {
    if (other->Get_Collision_Type() == Collision_Type::EXPLOSION) {
        if (state == BombWallState::IDLE) {
            state = BombWallState::DESTROYING;
        }
    }
}

void Bomb_Wall::Draw() {
    if (state == BombWallState::IDLE) {
        DrawTexture(wall_texture, hitbox.x, hitbox.y, WHITE);
    } else {
        // Da die Klasse 'draw' nicht besitzt, wird das Zeichnen extern gehandhabt.
        // Sie müssen ein separates Renderer-Objekt verwenden. Dies ist ein Platzhalter.
    }
}

Collision_Type Bomb_Wall::Get_Collision_Type() const {
    return Collision_Type::BOMB_WALL;
}