#pragma once

#include "../Collidable.h"
#include "../../core/Object_Manager.h"
#include <string>
#include <memory>
#include <raylib.h>

class GeneratorDoor : public Collidable {
private:
    std::string group_id;
    Object_Manager& objectManager;

    std::shared_ptr<Texture2D> texture_ptr; // individuelle Textur

public:
    GeneratorDoor(Vector2 position,
                  Vector2 size,
                  const std::string& group_id,
                  Object_Manager& om,
                  const std::string& sprite_path = "");

    ~GeneratorDoor() override;

    void Tick(float delta_time) override;
    void On_Collision(std::shared_ptr<Collidable> other) override;
    void Draw() override;

    Collision_Type Get_Collision_Type() const override;

    // optional: statische Methoden für globale Texturen
    static std::shared_ptr<Texture2D> Load_Texture(const std::string& path);
};
