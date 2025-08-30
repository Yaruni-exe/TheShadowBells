#pragma once

#include "../Collidable.h"
#include "../../core/RepeatAnimation.h"
#include <string>

class Generator : public Collidable {
private:
    float health;
    float max_health;
    RepeatAnimation animation;
    std::string group_id;

    // Die statische Texturvariable gehört zur Klasse, nicht zum Objekt
    static Texture2D generator_texture;

public:
    // Konstruktor akzeptiert nun keine Textur mehr
    Generator(Vector2 position, const std::string& group_id, float health);
    ~Generator() override;

    // Statische Methoden zum Laden und Entladen der Textur
    static void Load_Texture();
    static void Unload_Texture();

    // Core methods from Collidable
    void Tick(float delta_time) override;
    void On_Collision(std::shared_ptr<Collidable> other) override;
    void Draw() override;

    Collision_Type Get_Collision_Type() const override;

    // Getter for the group_id
    std::string Get_Group_ID() const;
};