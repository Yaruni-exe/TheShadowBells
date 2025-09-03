//
// Created by Teilnehmer on 03.09.2025.
//

#ifndef MEDIPACK_H
#define MEDIPACK_H

#pragma once

#include "raylib.h"
#include "../Collidable.h"
#include <memory>

class Medipack : public Collidable
{
private:
    float healing_amount;
    Texture2D texture;
    static bool texture_loaded; // Stellt sicher dass  Textur nur einmal geladen wird

public:
    Medipack(Vector2 position, float heal_value);
    ~Medipack();

    void On_Collision(std::shared_ptr<Collidable> other) override;
    Collision_Type Get_Collision_Type() const override { return Collision_Type::CONSUMABLE; }
    void Tick(float delta_time) override {} // Medipack benötigt keine Tick-Logik
    void Draw() override;
};

#endif //MEDIPACK_H
