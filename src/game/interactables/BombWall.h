#pragma once

#include "raylib.h"
#include <memory>
#include <string>
#include "../Collidable.h"
#include "../../core/SpriteAnimated.h"
#include "../../core/Texture2d.h"

enum class BombWallState
{
    IDLE,
    DESTROYING
};

class Bomb_Wall : public Collidable
{
private:
    game::core::SpriteAnimated destroy_animation;
    BombWallState state;

    Texture2D sprite_texture;   // individuelle Sprite-Textur pro Instanz
    Vector2 sprite_offset;      // individueller Offset fürs Zeichnen

    static std::shared_ptr<game::core::Texture2D> destroy_texture_ptr; // geteilte Zerstörungs-Textur

public:
    // Neuer Konstruktor mit allen Parametern
    Bomb_Wall(Vector2 position,
              Vector2 hitbox_size,
              const std::string& sprite_path,
              Vector2 sprite_offset = {0,0});

    ~Bomb_Wall() override;

    void Tick(float delta_time) override;
    void Draw() override;
    void On_Collision(std::shared_ptr<Collidable> other) override;
    Collision_Type Get_Collision_Type() const override;

    BombWallState Get_State() const { return this->state; }

    // Lade/Entlade die Zerstörungs-Animation (geteilt von allen BombWalls)
    static void Load_Destroy_Texture();
    static void Unload_Destroy_Texture();
};
