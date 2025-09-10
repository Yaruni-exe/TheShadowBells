#include "BombWall.h"
#include "raylib.h"
#include <iostream>
#include "Explosion.h"

// statische Zerstörungs-Textur (geteilt von allen BombWalls)
std::shared_ptr<game::core::Texture2D> Bomb_Wall::destroy_texture_ptr = nullptr;

Bomb_Wall::Bomb_Wall(Vector2 position,
                     Vector2 hitbox_size,
                     const std::string& sprite_path,
                     Vector2 sprite_offset)
    : destroy_animation(destroy_texture_ptr, 64, 64, 1, 10, 10,
                        static_cast<int>(position.x), static_cast<int>(position.y)),
      state(BombWallState::IDLE),
      sprite_offset(sprite_offset)
{
    // Hitbox setzen
    this->hitbox = { position.x, position.y, hitbox_size.x, hitbox_size.y };

    // Sprite-Textur laden (individuell pro Wand)
    sprite_texture = LoadTexture(sprite_path.c_str());
}

Bomb_Wall::~Bomb_Wall()
{
    // individuelle Sprite-Textur entladen
    if (sprite_texture.id != 0)
    {
        UnloadTexture(sprite_texture);
        sprite_texture.id = 0;
    }
}

void Bomb_Wall::Tick(float delta_time)
{
    if (state == BombWallState::DESTROYING)
    {
        // Update der Zerstörungsanimation
        destroy_animation.Update();
    }
}

void Bomb_Wall::On_Collision(std::shared_ptr<Collidable> other)
{
    if (other->Get_Collision_Type() == Collision_Type::EXPLOSION)
    {
        if (state == BombWallState::IDLE)
        {
            state = BombWallState::DESTROYING;
        }
    }
}

void Bomb_Wall::Draw()
{
    if (state == BombWallState::IDLE)
    {
        DrawTexture(sprite_texture,
                    hitbox.x + sprite_offset.x,
                    hitbox.y + sprite_offset.y,
                    WHITE);
    }
    else
    {
        // Hinweis: die Animation selbst wird bereits in Tick() geupdated.
        // Falls du sie hier zeichnen willst, müsstest du destroy_animation.Draw() o.ä. aufrufen.
    }
}

Collision_Type Bomb_Wall::Get_Collision_Type() const
{
    return Collision_Type::BOMB_WALL;
}

void Bomb_Wall::Load_Destroy_Texture()
{
    if (!destroy_texture_ptr)
    {
        destroy_texture_ptr = std::make_shared<game::core::Texture2D>(
            "assets/graphics/Items/BombWall/Wand-Sprengstoff_Industrie_Opening_Animation_horizontal.png"
        );
    }
}

void Bomb_Wall::Unload_Destroy_Texture()
{
    destroy_texture_ptr = nullptr;
}
