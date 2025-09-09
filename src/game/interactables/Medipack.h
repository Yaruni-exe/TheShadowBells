#pragma once

#include "raylib.h"
#include "../Collidable.h"
#include "RepeatAnimation.h" // Neu hinzugefügt
#include <memory>

class Medipack : public Collidable
{
private:
    float healing_amount;
    // Anstatt einer statischen Textur, verwenden wir jetzt die Animationsklasse
    RepeatAnimation animation;

public:
    Medipack(Vector2 position, float heal_value);
    // Der Destruktor ist jetzt default, da die Animation die Textur selbst entlädt
    ~Medipack() override = default;

    void On_Collision(std::shared_ptr<Collidable> other) override;
    Collision_Type Get_Collision_Type() const override { return Collision_Type::CONSUMABLE; }
    void Tick(float delta_time) override; // Diese Methode wird nun benötigt
    void Draw() override;
};
