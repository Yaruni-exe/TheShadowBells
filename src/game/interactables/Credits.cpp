#include "Credits.h"
#include <iostream>
#include <memory>
#include <string>

// Initialisierung der statischen Textur außerhalb der Klasse
Texture2D Credit::credit_texture = {0};

Credit::Credit(Vector2 position, int value)
    : value(value),
      // HIER WIRD DIE ANIMATION KORREKT INITIALISIERT!
      animation(Vector2{32, 32}, "assets/graphics/coin_animation.png", 8, 4) {

    // Die Textur wird nur geladen, wenn sie noch nicht existiert.
    if (credit_texture.id == 0) {
        credit_texture = LoadTexture("assets/graphics/coin_animation.png");
    }

    this->hitbox = {position.x, position.y, 32, 32};
}

Credit::~Credit() {
    // Da die Textur statisch ist, muss sie nur einmal entladen werden,
    // am besten in der GameScene am Ende des Spiels.
}

void Credit::Tick(float delta_time) {
    this->animation.Next_Frame();
}

void Credit::On_Collision(std::shared_ptr<Collidable> other) {
    if (other->Get_Collision_Type() == Collision_Type::PLAYER) {
        Mark_For_Destruction();
        if (auto player = std::dynamic_pointer_cast<Player_Base_Class>(other)) {
            player->AddScore(value);
        }
    }
}

void Credit::Draw() {
    this->animation.Draw_Current_Frame({hitbox.x, hitbox.y});
}

int Credit::GetValue() const {
    return value;
}

Collision_Type Credit::Get_Collision_Type() const {
    return Collision_Type::CONSUMABLE;
}