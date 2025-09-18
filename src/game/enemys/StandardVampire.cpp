#include "StandardVampire.h"
#include "../../config_enemys.h.in"
#include <iostream>
#include <string>
#include "raymath.h"
#include <memory>
#include <vector>

namespace enemy
{
    // Deklaration und Initialisierung der statischen Member
    std::vector<Texture2D> StandardVampire::run_textures;
    int StandardVampire::frames_per_direction[4];
    float StandardVampire::frame_widths[4];
    bool StandardVampire::textures_loaded = false;

    // Texture paths for all directions
    const std::string run_paths[4] = {
        "assets/graphics/Enemies/StandardVampire/StandardVampir_Run_Cycle_Down.png",
        "assets/graphics/Enemies/StandardVampire/StandardVampir_Run_Cycle_Up.png",
        "assets/graphics/Enemies/StandardVampire/StandardVampir_Run_Cycle_Left.png",
        "assets/graphics/Enemies/StandardVampire/StandardVampir_Run_Cycle_Right.png",
    };

    StandardVampire::StandardVampire(Vector2 start_position)
        : EnemyExtendedBaseClass(
            "Standard Vampire",
            game::EnemyConfig::kStandardVampireHealth,
            game::EnemyConfig::kStandardVampireMovementSpeed,
            game::EnemyConfig::kStandardVampireDamage,
            game::EnemyConfig::kStandardVampireValue,
            game::EnemyConfig::kStandardVampireSpritePath,
            nullptr,
            start_position,
            game::EnemyConfig::kStandardVampireHitboxWidth,
            game::EnemyConfig::kStandardVampireHitboxHeight,
            game::EnemyConfig::kStandardVampireAttackCooldown
          ),
          current_direction_index(0),
          animation_timer(0.0f),
          current_frame(0),
          frames_per_second(1.0f)
    {
        // Lade Texturen nur einmal
        if (!textures_loaded) {
            for (int i = 0; i < 4; ++i) {
                run_textures.push_back(LoadTexture(run_paths[i].c_str()));
            }

            frames_per_direction[0] = 4;
            frame_widths[0] = 256.0f / 4.0f; // Front (Run Cycle Down)

            frames_per_direction[1] = 4;
            frame_widths[1] = 256.0f / 4.0f; // Back (Run Cycle Up)

            frames_per_direction[2] = 5;
            frame_widths[2] = 320.0f / 5.0f; // Left (Run Cycle Left)

            frames_per_direction[3] = 5;
            frame_widths[3] = 320.0f / 5.0f; // Right (Run Cycle Right)

            textures_loaded = true;
        }
    }

    StandardVampire::~StandardVampire() {
        // Die statischen Texturen werden am Ende des Programms automatisch freigegeben.
    }

    void StandardVampire::Update_AI(float delta_time, Vector2 player_position)
    {
        // --- Hit-Feedback: Gegner bleibt kurz stehen ---
        if (hit_timer > 0.0f) {
            is_Moving = false;
            return; // keine Bewegung oder Angriff während Hit
        }

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

        if (distance_to_player <= game::EnemyConfig::kStandardVampireAttackRange && this->attack_Cooldown_Timer <= 0.0f && attack_animation_timer <= 0.0f)
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

    void StandardVampire::Tick(float delta_time)
    {
        EnemyExtendedBaseClass::Tick(delta_time);
    }

    void StandardVampire::Melee_Attack()
    {
        this->attack_Cooldown_Timer = this->attack_Cooldown_Duration;
    }

    void StandardVampire::Range_Attack()
    {
        // Leere Implementierung
    }

    void StandardVampire::Draw()
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

        Vector2 draw_position = {
            hitbox.x + hitbox.width / 2.0f - frame_width / 2.0f,
            hitbox.y + hitbox.height / 2.0f - frame_height / 2.0f
        };

        // --- Hit-Feedback Farbe anwenden ---
        Color draw_color = WHITE;
        if (hit_timer > 0.0f) {
            draw_color = hit_color; // #6c4c44
        }

        DrawTextureRec(current_texture, source_rec, draw_position, draw_color);
    }
}
