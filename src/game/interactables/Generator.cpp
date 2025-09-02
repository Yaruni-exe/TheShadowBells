#include "Generator.h"
#include "raylib.h"
#include <iostream>
#include "../PlayerProjectile.h"
#include "../EnemyBaseClass.h"

// Definition der statischen Texturvariable
Texture2D Generator::generator_texture = {0};

void Generator::Load_Texture() {
    if (generator_texture.id == 0) {
        generator_texture = LoadTexture("assets/graphics/Items/Generator/Generator_Activate_Animation.png");
    }
}

void Generator::Unload_Texture() {
    if (generator_texture.id != 0) {
        UnloadTexture(generator_texture);
        generator_texture.id = 0;
    }
}

Generator::Generator(Vector2 position, const std::string& group_id, float health)
    : group_id(group_id), health(health), max_health(health),
      animation(Vector2{32, 23}, generator_texture, 6, 600) {

    this->hitbox = {position.x, position.y, 32, 23};
    // Der Animation-Member wird jetzt oben in der Initialisierungsliste konstruiert.
    // Dieser Code ist daher nicht mehr notwendig:
    // this->animation = RepeatAnimation(Vector2{32, 32}, generator_texture, 7, 7);
}

Generator::~Generator() {
    // Statische Texturen werden in einer zentralen Stelle entladen (z.B. im Destruktor der GameScene)
}

void Generator::Tick(float delta_time) {
    this->animation.Next_Frame();
}

void Generator::On_Collision(std::shared_ptr<Collidable> other) {
    if (other->Get_Collision_Type() == Collision_Type::PLAYER_PROJECTILE) {
        if (auto projectile = std::dynamic_pointer_cast<game::Player_Projectile>(other)) {
            this->health -= projectile->damage;
            projectile->Mark_For_Destruction();
        }
        if (this->health <= 0) {
            Mark_For_Destruction();
        }
    } else if (other->Get_Collision_Type() == Collision_Type::PLAYER ||
               other->Get_Collision_Type() == Collision_Type::ENEMY) {
        // Die Kollision wurde erkannt. Der Generator kann als festes Hindernis behandelt werden.
    }
}

void Generator::Draw() {
    this->animation.Draw_Current_Frame({hitbox.x, hitbox.y});
    DrawRectangle(hitbox.x, hitbox.y - 10, hitbox.width, 5, BLACK);
    DrawRectangle(hitbox.x, hitbox.y - 10, hitbox.width * (this->health / this->max_health), 5, RED);
}

Collision_Type Generator::Get_Collision_Type() const {
    return Collision_Type::GENERATOR;
}

std::string Generator::Get_Group_ID() const {
    return group_id;
}
