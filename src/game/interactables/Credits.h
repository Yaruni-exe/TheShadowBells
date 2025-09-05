#pragma once

#include "../Collidable.h"
#include "RepeatAnimation.h"
#include "../PlayerBaseClass.h"

class Credit : public Collidable {
private:
    int value;
    RepeatAnimation animation;
    // Die statische Textur ist nicht mehr notwendig, da die Animation sie selbst lädt.
    // statische Variable für die Textur, die von allen Münzen geteilt wird.
    // static Texture2D credit_texture;

public:
    Credit(Vector2 position, int value);
    ~Credit() override;

    void Tick(float delta_time) override;
    void On_Collision(std::shared_ptr<Collidable> other) override;
    void Draw() override;

    int GetValue() const;
    Collision_Type Get_Collision_Type() const override;
};