#pragma once

#include "../Collidable.h"
#include "../../core/Object_Manager.h"
#include <string>

class GeneratorDoor : public Collidable {
private:
    std::string group_id;
    Object_Manager& objectManager;
    static Texture2D door_texture;

public:
    GeneratorDoor(Vector2 position, const std::string& group_id, Object_Manager& om);
    ~GeneratorDoor() override;

    static void Load_Texture();
    static void Unload_Texture();

    void Tick(float delta_time) override;
    void On_Collision(std::shared_ptr<Collidable> other) override;
    void Draw() override;

    Collision_Type Get_Collision_Type() const override;
};