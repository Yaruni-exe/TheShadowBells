#include "PlayerProjectile.h"
#include <raymath.h>
#include "EnemyBaseClass.h"

namespace game {
    Player_Projectile::Player_Projectile(Vector2 start_position, Vector2 direction, int damage, const char* sprite_path)
            : position(start_position),
              damage(damage),
              total_Distance_Traveled(0.0f) {
        this->velocity.x = direction.x * game::Config::player_Class_One_Projectile_Speed;
        this->velocity.y = direction.y * game::Config::player_Class_One_Projectile_Speed;
        this->sprite = LoadTexture(sprite_path);
        this->hitbox = { position.x, position.y, (float)this->sprite.width, (float)this->sprite.height };
    }

    Player_Projectile::~Player_Projectile() {
        if (sprite.id > 0) {
            UnloadTexture(sprite);
        }
    }

    void Player_Projectile::Tick(float delta_time) {
        // Stoppe, wenn das Objekt zur Zerstörung markiert ist
        if (Is_Marked_For_Destruction()) return;

        position.x += velocity.x * delta_time;
        position.y += velocity.y * delta_time;
        hitbox.x = position.x;
        hitbox.y = position.y;

        float distance_this_frame = Vector2Length(Vector2Scale(velocity, delta_time));
        total_Distance_Traveled += distance_this_frame;

        if (total_Distance_Traveled >= game::Config::player_Projectile_Max_Range) {
            Mark_For_Destruction();
        }
    }

    void Player_Projectile::Draw() {
        if (Is_Marked_For_Destruction()) return;
        DrawTextureV(sprite, position, WHITE);
    }

    Collision_Type Player_Projectile::Get_Collision_Type() const {
        return Collision_Type::PLAYER_PROJECTILE;
    }

    void Player_Projectile::On_Collision(std::shared_ptr<Collidable> other) {
        // Wenn das Projektil bereits zur Zerstörung markiert ist, tue nichts mehr.
        if (Is_Marked_For_Destruction()) return;

        if (other->Get_Collision_Type() == Collision_Type::ENEMY) {
            // Direktes Casting, da 'other' ein gültiger shared_ptr ist.
            std::shared_ptr<enemy::Enemy_Base_Class> enemy_ptr = std::dynamic_pointer_cast<enemy::Enemy_Base_Class>(other);
            if (enemy_ptr) {
                enemy_ptr->Take_Damage(this->damage);
            }
            // Zerstöre das Projektil sofort, damit es keinen weiteren Schaden verursacht.
            Mark_For_Destruction();
        } else if (other->Get_Collision_Type() == Collision_Type::WALL) {
            Mark_For_Destruction();
        }
    }
}