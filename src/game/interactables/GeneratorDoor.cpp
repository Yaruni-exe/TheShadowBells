#include "GeneratorDoor.h"
#include "Generator.h"
#include <iostream>

GeneratorDoor::GeneratorDoor(Vector2 position,
                             Vector2 size,
                             const std::string& group_id,
                             Object_Manager& om,
                             const std::string& sprite_path)
    : group_id(group_id), objectManager(om) {

    // Hitbox individuell setzen
    this->hitbox = { position.x, position.y, size.x, size.y };

    // Textur laden, entweder eigene oder leer (kann statisch gecached werden)
    if (!sprite_path.empty()) {
        texture_ptr = Load_Texture(sprite_path);
    } else {
        texture_ptr = nullptr;
    }
}

GeneratorDoor::~GeneratorDoor() {
    // Shared Pointer sorgt automatisch für sauberes Entladen
}

void GeneratorDoor::Tick(float delta_time) {
    // Überprüfe, ob alle Generatoren der Gruppe zerstört sind
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
    // Blockiert Spieler/Gegner
    if (other->Get_Collision_Type() == Collision_Type::PLAYER ||
        other->Get_Collision_Type() == Collision_Type::ENEMY) {
        // Logik wird extern über Hitboxen gehandhabt
    }
}

void GeneratorDoor::Draw() {
    if (!texture_ptr) return;

    // Textur mittig in der Hitbox zeichnen
    float draw_x = hitbox.x + (hitbox.width - texture_ptr->width) / 2.0f;
    float draw_y = hitbox.y + (hitbox.height - texture_ptr->height) / 2.0f;

    DrawTexture(*texture_ptr, draw_x, draw_y, WHITE);
}

Collision_Type GeneratorDoor::Get_Collision_Type() const {
    return Collision_Type::DOOR;
}

// Hilfsfunktion: lädt Textur und gibt Shared Pointer zurück
std::shared_ptr<Texture2D> GeneratorDoor::Load_Texture(const std::string& path) {
    auto tex = std::make_shared<Texture2D>(LoadTexture(path.c_str()));
    return tex;
}
