#include "Gunslinger.h"
#include "../config.h.in"
#include "raymath.h"
#include <string>
#include <cmath>
#include "PlayerProjectile.h"
#include <algorithm>
#include <iostream>
#include "interactables/Explosion.h"
#include "interactables/BombWall.h"
#include "CollisionResponse.h"
#include "interactables/BombPickup.h"
#include "EnemyProjectile.h"
#include "../scenes/LevelTransition.h"

// Pfade zu den Texturen
const std::string idle_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Back.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Front.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Animation_Right.png",
};

const std::string run_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Back.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Front.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png",
};

const std::string attack_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Right.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_BackRight.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Back.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_BackLeft.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Left.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_FrontLeft.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_Front.png",
    "assets/graphics/Characters/Gunslinger/Gunslinger_Fight_Animation_FrontRight.png",
};

Gunslinger::Gunslinger(Vector2 start_Position, Object_Manager& om)
    : Player_Base_Class(game::Config::player_Class_One_Max_Health, game::Config::player_Class_One_Movement_Speed,
        game::Config::player_Class_One_Damage, start_Position, om)
{
    this->ranged_Cooldown_Timer = 0.0f;

    // Texturen für alle Richtungen laden
    for (int i = 0; i < 8; ++i) {
        idle_textures.push_back(LoadTexture(idle_paths[i].c_str()));
        run_textures.push_back(LoadTexture(run_paths[i].c_str()));
        attack_textures.push_back(LoadTexture(attack_paths[i].c_str()));
    }
}

Gunslinger::~Gunslinger() {
    // Texturen entladen
    for (int i = 0; i < 8; ++i) {
        UnloadTexture(idle_textures[i]);
        UnloadTexture(run_textures[i]);
        UnloadTexture(attack_textures[i]);
    }
}

void Gunslinger::Tick(float delta_time, Vector2 worldMousePos) {
    Player_Base_Class::Tick(delta_time);

    mouseLook.Update(this->player_Pos, worldMousePos);
    mouse_World_Position = worldMousePos;

    if (this->ranged_Cooldown_Timer > 0.0f) {
        this->ranged_Cooldown_Timer -= delta_time;
    }

    // Überprüfen, ob der Spieler tot ist
    if (this->player_Health <= 0) {
        // Hier können wir ein Flag setzen oder eine globale Funktion aufrufen,
        // um den Game-Over-Screen zu aktivieren.
        // Zum Beispiel:
        // game_manager.SetGameState(GameState::GAME_OVER);
    }

    // Animationen aktualisieren
    frame_timer += delta_time;
    if (frame_timer >= animation_speed) {
        frame_timer = 0.0f;
        current_frame++;
        if (current_frame >= 7) {
            current_frame = 0;
            if (currentState == PlayerState::ATTACK) {
                currentState = PlayerState::IDLE;
            }
        }
    }

    if (currentState != PlayerState::ATTACK) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && this->ranged_Cooldown_Timer <= 0.0f) {
            this->Ranged_Attack();
            currentState = PlayerState::ATTACK;
            current_frame = 0;
        } else if (is_Moving) {
            currentState = PlayerState::RUN;
        } else {
            currentState = PlayerState::IDLE;
        }
    }
}

void Gunslinger::Add_Bomb() {
    this->bombs++;
    std::cout << "Bombe aufgesammelt! Aktuelle Bomben: " << this->bombs << std::endl;
}

int Gunslinger::Get_Bomb_Count() const {
    return this->bombs;
}

void Gunslinger::Use_Bomb() {
    if (this->bombs > 0) {
        this->bombs--;
        om.AddObject(std::make_shared<Explosion>(this->Get_Player_Pos()));
    }
}

void Gunslinger::On_Collision(std::shared_ptr<Collidable> other) {
    Collision_Type otherType = other->Get_Collision_Type();

    switch(otherType) {
        case Collision_Type::ENEMY:
        {
            CollisionResponse::Resolve_Overlap(shared_from_this(), other);
            break;
        }
        case Collision_Type::ENEMY_PROJECTILE:
        {
            // Typumwandlung und Handhabung des Schadens durch Projektile
            if (auto enemy_projectile = std::dynamic_pointer_cast<game::Enemy_Projectile>(other)) {
                this->Take_Damage(enemy_projectile->damage);
                enemy_projectile->Mark_For_Destruction();
            }
            break;
        }
        case Collision_Type::BOMB_WALL:
        {
            if (this->Get_Bomb_Count() > 0) {
                this->Use_Bomb();
                if (auto bombWall = std::dynamic_pointer_cast<Bomb_Wall>(other)) {
                    other->On_Collision(std::make_shared<Explosion>(Vector2{bombWall->Get_Hitbox().x, bombWall->Get_Hitbox().y}));
                }
            }
            break;
        }
        case Collision_Type::WALL:
        case Collision_Type::DOOR:
        case Collision_Type::GENERATOR:
        {
            CollisionResponse::Resolve_Overlap(shared_from_this(), other);
            break;
        }
        case Collision_Type::BOMB_PICKUP:
        {
            if (auto bombPickup = std::dynamic_pointer_cast<Bomb_Pickup>(other)) {
                this->Add_Bomb();
                bombPickup->Mark_For_Destruction();
            }
            break;
        }
        case Collision_Type::LEVEL_EXIT:
        {
            // Versuche, das kollidierende Objekt als LevelTransition zu behandeln.
            if (auto level_transition = std::dynamic_pointer_cast<LevelTransition>(other)) {
                level_transition->TriggerTransition();
            }
            break;
        }
        default:
            break;
    }
}

void Gunslinger::Draw()
{
    int current_direction_index = mouseLook.GetDirectionIndex();
    Texture2D current_texture;

    if (currentState == PlayerState::IDLE) {
        current_texture = idle_textures[current_direction_index];
    } else if (currentState == PlayerState::RUN) {
        current_texture = run_textures[current_direction_index];
    } else if (currentState == PlayerState::ATTACK) {
        current_texture = attack_textures[current_direction_index];
    }

    // Stelle sicher, dass der Frame-Index innerhalb des gültigen Bereichs liegt
    if (current_frame < 0) {
        current_frame = 0;
    } else if (current_frame >= 7) {
        current_frame = 0; // Zurück zum Anfang der Animation
    }

    // Das Quellrechteck berechnet den Ausschnitt für den aktuellen Frame
    // Der Code geht davon aus, dass die Spritesheets horizontal angeordnet sind.
    Rectangle sourceRec = { (float)current_frame * size.x, 0.0f, size.x, size.y };

    // Die Zielposition auf dem Bildschirm für die gezeichnete Textur
    Vector2 draw_position = { this->player_Pos.x - 16, this->player_Pos.y };

    DrawTextureRec(current_texture, sourceRec, draw_position, WHITE);
}

void Gunslinger::Ranged_Attack() {
    Vector2 target_Position = this->mouse_World_Position;

    float delta_vector_x = target_Position.x - this->hitbox.x;
    float delta_vector_y = target_Position.y - this->hitbox.y;
    float distance_to_target = std::sqrt(delta_vector_x * delta_vector_x + delta_vector_y * delta_vector_y);

    if (distance_to_target > 0) {
        Vector2 fire_direction = {
                delta_vector_x / distance_to_target,
                delta_vector_y / distance_to_target
        };
        std::shared_ptr<game::Player_Projectile> sp_temp_projectile(new game::Player_Projectile(
                Vector2{this->hitbox.x, this->hitbox.y},
                fire_direction,
                this->player_Damage,
                game::Config::player_Projectile_Sprite_Path));
        om.AddObject(sp_temp_projectile);
        this->ranged_Cooldown_Timer = 0.5f;
    }
}
/*
void Gunslinger::Clean_Up_Projectiles() {

    // Projektile jetzt durch den Object_Manager verwaltet werden.
}
*/