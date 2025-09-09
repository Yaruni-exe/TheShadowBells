//
// Created by Teilnehmer on 03.09.2025.
//
#include "Medipack.h"
#include "../../game/PlayerBaseClass.h"

Medipack::Medipack(Vector2 position, float heal_value)
    : healing_amount(heal_value),
      // Initialisieren der Animation. Passen Sie die Werte an Ihr Sprite-Sheet an.
      // Annahme: 32x32px pro Frame, 4 Frames, 4 Spalten
      animation(Vector2{32, 32}, "assets/graphics/Items/Healthpacks/Health_Pack_Animation.png", 11, 11, 1.0f)
{
    this->hitbox = {position.x, position.y, 24, 24};
}

void Medipack::Tick(float delta_time)
{
    // Die Animation vorantreiben
    this->animation.Next_Frame(delta_time);
}

void Medipack::On_Collision(std::shared_ptr<Collidable> other)
{
    if (auto player = std::dynamic_pointer_cast<Player_Base_Class>(other)) {
        player->Heal(this->healing_amount);
        this->Mark_For_Destruction();
    }
}

void Medipack::Draw()
{
    Vector2 new_size = {24, 24};
    // Den aktuellen Animations-Frame zeichnen
    this->animation.Draw_Current_Frame({hitbox.x, hitbox.y}, new_size);
}
