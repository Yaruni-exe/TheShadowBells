#include "Credits.h"
#include <iostream>
#include <memory>
#include <string>

// Die statische Textur-Variable wurde in der .h-Datei entfernt,
// daher brauchen wir sie hier auch nicht mehr.

Credit::Credit(Vector2 position, int value)
    : value(value),

      animation(Vector2{28, 27}, "assets/graphics/Items/Credits/Credits_Shine_Animation.png", 9, 9, 1.0f) {

    this->hitbox = {position.x, position.y, 27, 27};
    // Die Logik zum Laden der Textur ist nun die Aufgabe von RepeatAnimation.
}

Credit::~Credit() {
    // Da die Textur nicht mehr statisch ist, wird sie von RepeatAnimation
    // automatisch entladen, wenn das Objekt zerstört wird.
}

void Credit::Tick(float delta_time) {
    // Hier übergeben wir delta_time, um die Animation voranzutreiben.
    this->animation.Next_Frame(delta_time);
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