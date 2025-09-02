#include "BombPickup.h"
#include "raylib.h"
#include <iostream>
#include "../Gunslinger.h"

/*

Texture2D Bomb_Pickup::bomb_texture = {0};

void Bomb_Pickup::Load_Texture() {
    if (bomb_texture.id == 0) {
        bomb_texture = LoadTexture("assets/graphics/Items/bomb_pickup.png");
    }
}

void Bomb_Pickup::Unload_Texture() {
    if (bomb_texture.id != 0) {
        UnloadTexture(bomb_texture);
        bomb_texture.id = 0;
    }
}

Bomb_Pickup::Bomb_Pickup(Vector2 position)
    : animation(Vector2{32, 32}, bomb_texture, 7, 7) {
    this->hitbox = {position.x, position.y, 64, 64};
}

Bomb_Pickup::~Bomb_Pickup() {}

void Bomb_Pickup::Tick(float delta_time) {
    this->animation.Next_Frame();
}

void Bomb_Pickup::On_Collision(std::shared_ptr<Collidable> other) {
    if (other->Get_Collision_Type() == Collision_Type::PLAYER) {
        if (auto player = std::dynamic_pointer_cast<Gunslinger>(other)) {
            player->Add_Bomb();
            Mark_For_Destruction();
        }
    }
}

void Bomb_Pickup::Draw() {
    this->animation.Draw_Current_Frame({hitbox.x, hitbox.y});
}

Collision_Type Bomb_Pickup::Get_Collision_Type() const {
    return Collision_Type::BOMB_PICKUP;
}

*/