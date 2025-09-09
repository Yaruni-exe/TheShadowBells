#include "SpecialVampire.h"
#include "../../config_enemys.h.in"
#include <iostream>
#include <string>
#include "raymath.h"
#include <memory>
#include <vector>

namespace enemy
{
    // Deklaration und Initialisierung der statischen Member
    std::vector<Texture2D> SpecialVampire::run_textures;
    int SpecialVampire::frames_per_direction[4];
    float SpecialVampire::frame_widths[4];
    bool SpecialVampire::textures_loaded = false;

    // Texture paths for all directions
    const std::string run_paths[4] = {
        "assets/graphics/Enemies/SpecialVampire/Enemy_02_Run_Cycle_front.png",
        "assets/graphics/Enemies/SpecialVampire/Enemy_02_Run_Cycle_back.png",
        "assets/graphics/Enemies/SpecialVampire/Enemy_02_Run_Cycle_left.png",
        "assets/graphics/Enemies/SpecialVampire/Enemy_02_Run_Cycle_right.png",
    };

    SpecialVampire::SpecialVampire(Vector2 start_position)
        : EnemyExtendedBaseClass(
            "SpecialnVampire",
            game::EnemyConfig::kSpecialVampireHealth,
            game::EnemyConfig::kSpecialVampireMovementSpeed,
            game::EnemyConfig::kSpecialVampireDamage,
            game::EnemyConfig::kSpecialVampireValue,
            game::EnemyConfig::kSpecialVampireSpritePath,
            nullptr,
            start_position,
            game::EnemyConfig::kSpecialVampireHitboxWidth,
            game::EnemyConfig::kSpecialVampireHitboxHeight,
            game::EnemyConfig::kSpecialVampireAttackCooldown
          ),
          current_direction_index(0),
          animation_timer(0.0f),
          current_frame(0),
          frames_per_second(10.0f) // Die Animationsgeschwindigkeit kann hier angepasst werden.
    {
        // Lade Texturen und konfiguriere nur einmal
        if (!textures_loaded) {
            for (int i = 0; i < 4; ++i) {
                run_textures.push_back(LoadTexture(run_paths[i].c_str()));
            }

            // Setze die spezifischen Werte basierend auf den Assets
            frames_per_direction[0] = 8;
            frame_widths[0] = 344.0f / 8.0f; // Front (Run Cycle Down)

            frames_per_direction[1] = 8;
            frame_widths[1] = 344.0f / 8.0f; // Back (Run Cycle Up)

            frames_per_direction[2] = 8;
            frame_widths[2] = 344.0f / 8.0f; // Left (Run Cycle Left)

            frames_per_direction[3] = 8;
            frame_widths[3] = 344.0f / 8.0f; // Right (Run Cycle Right)

            textures_loaded = true;
        }
    }

    SpecialVampire::~SpecialVampire() {
        // Die statischen Texturen werden am Ende des Programms automatisch freigegeben.
    }

    void SpecialVampire::Update_AI(float delta_time, Vector2 player_position)
    {
        Vector2 old_position = { this->hitbox.x, this->hitbox.y };
        EnemyExtendedBaseClass::Tick(delta_time);

        if (attack_animation_timer > 0.0f) {
            attack_animation_timer -= delta_time;
            current_state = EnemyState::ATTACKING;
            this->is_Moving = false;
        } else {
            current_state = EnemyState::IDLE;
        }

        float distance_to_player = Vector2Distance({this->hitbox.x, this->hitbox.y}, player_position);

        if (distance_to_player <= game::EnemyConfig::kSpecialVampireAttackRange && this->attack_Cooldown_Timer <= 0.0f && attack_animation_timer <= 0.0f)
        {
            attack_animation_timer = 0.8f;
            this->Melee_Attack();
        }

        if (current_state != EnemyState::ATTACKING && current_state != EnemyState::DYING)
        {
            this->Pathfinding(player_position.x, player_position.y, delta_time);
        }

        Vector2 new_position = { this->hitbox.x, this->hitbox.y };
        Vector2 movement_vector = Vector2Subtract(new_position, old_position);

        if (Vector2Length(movement_vector) > 0.0f) {
            this->is_Moving = true;
            if (abs(movement_vector.x) > abs(movement_vector.y)) {
                if (movement_vector.x > 0) {
                    current_direction_index = 3; // Rechts
                } else {
                    current_direction_index = 2; // Links
                }
            } else {
                if (movement_vector.y > 0) {
                    current_direction_index = 0; // Unten / Vorne
                } else {
                    current_direction_index = 1; // Oben / Hinten
                }
            }

            animation_timer += delta_time;
            if (animation_timer >= 1.0f / frames_per_second) {
                animation_timer = 0.0f;
                current_frame++;
                
                if (current_frame >= frames_per_direction[current_direction_index]) {
                    current_frame = 0;
                }
            }
        } else {
            this->is_Moving = false;
        }
    }

    void SpecialVampire::Tick(float delta_time)
    {
        EnemyExtendedBaseClass::Tick(delta_time);
    }

    void SpecialVampire::Melee_Attack()
    {
        this->attack_Cooldown_Timer = this->attack_Cooldown_Duration;
    }

    void SpecialVampire::Range_Attack()
    {
        // Leere Implementierung für den Vampir, da er nur Nahkampfangriffe hat.
    }

    void SpecialVampire::Draw()
    {
        if (run_textures.empty()) return;
        
        Texture2D current_texture = run_textures[current_direction_index];
        
        float frame_width = frame_widths[current_direction_index];
        float frame_height = (float)current_texture.height;

        Rectangle source_rec = {
            (float)current_frame * frame_width,
            0.0f,
            frame_width,
            frame_height
        };
        
        // Zentriere den Sprite auf der Hitbox, indem wir den Mittelpunkt der Hitbox verwenden
        Vector2 draw_position = {
            hitbox.x + hitbox.width / 2.0f - frame_width / 2.0f,
            hitbox.y + hitbox.height / 2.0f - frame_height / 2.0f
        };

        DrawTextureRec(current_texture, source_rec, draw_position, WHITE);
    }
}
