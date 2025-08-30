#include "GeneratorDoor.h"
#include "raylib.h"
#include "Generator.h"
#include <iostream>

// Definition der statischen Texturvariable
Texture2D GeneratorDoor::door_texture = {0};

void GeneratorDoor::Load_Texture() {
    if (door_texture.id == 0) {
        door_texture = LoadTexture("assets/graphics/Items/door.png");
    }
}

void GeneratorDoor::Unload_Texture() {
    if (door_texture.id != 0) {
        UnloadTexture(door_texture);
        door_texture.id = 0;
    }
}

GeneratorDoor::GeneratorDoor(Vector2 position, const std::string& group_id, Object_Manager& om)
    : group_id(group_id), objectManager(om) {
    this->hitbox = {position.x, position.y, (float)door_texture.width, (float)door_texture.height};
}

GeneratorDoor::~GeneratorDoor() {
    // Die Textur wird als statische Ressource in der GameScene entladen.
}

void GeneratorDoor::Tick(float delta_time) {
    // Überprüfe, ob alle zugehörigen Generatoren zerstört sind
    int remaining_generators = 0;
    for (const auto& obj : objectManager.managed_objects) {
        if (obj->Get_Collision_Type() == Collision_Type::GENERATOR) {
            if (auto gen = std::dynamic_pointer_cast<Generator>(obj)) {
                if (gen->Get_Group_ID() == this->group_id) {
                    remaining_generators++;
                }
            }
        }
    }

    if (remaining_generators == 0) {
        Mark_For_Destruction();
        std::cout << "GeneratorDoor " << group_id << " is open!" << std::endl;
    }
}

void GeneratorDoor::On_Collision(std::shared_ptr<Collidable> other) {
    // Türen blockieren alles außer Projektilen
    if (other->Get_Collision_Type() != Collision_Type::PLAYER_PROJECTILE &&
        other->Get_Collision_Type() != Collision_Type::ENEMY_PROJECTILE) {
        // Mache einfach nichts, die Tür agiert wie eine Wand
        }
}

void GeneratorDoor::Draw() {
    DrawTexture(door_texture, hitbox.x, hitbox.y, WHITE);
}

Collision_Type GeneratorDoor::Get_Collision_Type() const {
    return Collision_Type::DOOR;
}