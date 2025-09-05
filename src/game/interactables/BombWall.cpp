#include "BombWall.h"
#include "raylib.h"
#include <iostream>

Texture2D Bomb_Wall::wall_texture = {0};

void Bomb_Wall::Load_Texture() {
    if (wall_texture.id == 0) {
        wall_texture = LoadTexture("assets/graphics/Items/BombWall/Wand-Sprengstoff_Industrie_Base_Sprite_Horizontal.png");
    }
}

void Bomb_Wall::Unload_Texture() {
    if (wall_texture.id != 0) {
        UnloadTexture(wall_texture);
        wall_texture.id = 0;
    }
}

Bomb_Wall::Bomb_Wall(Vector2 position)
    // NEU: FPS-Parameter übergeben
    : destroy_animation(Vector2{64, 64}, "assets/graphics/Items/BombWall/Wand-Sprengstoff_Industrie_Opening_Animation_horizontal.png", 10, 10, 10.0f),
      state(BombWallState::IDLE) {
    this->hitbox = {position.x, position.y, 64, 64};
}

Bomb_Wall::~Bomb_Wall() {}

void Bomb_Wall::Tick(float delta_time) {
    if (state == BombWallState::DESTROYING) {
        // NEU: Prüfe, ob die Animation abgeschlossen ist, indem du den Rückgabewert prüfst.
        if (destroy_animation.Next_Frame(delta_time)) {
            Mark_For_Destruction();
        }
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
        destroy_animation.Draw_Current_Frame({hitbox.x, hitbox.y});
    }
}

Collision_Type Bomb_Wall::Get_Collision_Type() const {
    return Collision_Type::BOMB_WALL;
}