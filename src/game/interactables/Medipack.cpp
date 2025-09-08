//
// Created by Teilnehmer on 03.09.2025.
//
#include "Medipack.h"
#include "../../game/PlayerBaseClass.h"

// Definition der statischen Variable
bool Medipack::texture_loaded = false;

Medipack::Medipack(Vector2 position, float heal_value)
    : healing_amount(heal_value)
{
    hitbox.x = position.x;
    hitbox.y = position.y;
    hitbox.width = 32; // Beispielgröße
    hitbox.height = 32; // Beispielgröße

    // Textur nur einmal laden
    if (!texture_loaded) {
        texture = LoadTexture("assets/graphics/Items/Healthpacks/Health-Pack (Item).png");
        texture_loaded = true;
    }
}

Medipack::~Medipack()
{
    if (texture_loaded) {
        UnloadTexture(texture);
        texture_loaded = false;
    }
}

void Medipack::On_Collision(std::shared_ptr<Collidable> other)
{
    // Wir casten das andere Objekt zu Player_Base_Class, da nur Spieler mit Medipacks interagieren können
    if (auto player = std::dynamic_pointer_cast<Player_Base_Class>(other)) {
        player->Heal(this->healing_amount);
        this->Mark_For_Destruction(); // Medipack soll nach Gebrauch verschwinden
    }
}

void Medipack::Draw()
{
    DrawTextureV(texture, {hitbox.x, hitbox.y}, WHITE);
}