#include "Gunslinger.h"
#include "../config.h.in"
#include "raymath.h"
#include <string>

// Arrays with file paths for each of the 8 directions
const std::string idle_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_Right.png",
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_UpRight.png",
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_Up.png",
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_UpLeft.png",
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_Left.png",
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_DownLeft.png",
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_Down.png",
    "assets/graphics/Characters/Gunslinger/Idle/Gunslinger_Idle_DownRight.png"
};

const std::string run_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Run/Gunslinger_Run_Right.png",
    "assets/graphics/Characters/Gunslinger/Run/Gunslinger_Run_UpRight.png",
    "assets/graphics/Characters/Gunslinger/Run/Gunslinger_Run_Up.png",
    "assets/graphics/Characters/Gunslinger/Run/Gunslinger_Run_UpLeft.png",
    "assets/graphics/Characters/Gunslinger/Run/Gunslinger_Run_Left.png",
    "assets/graphics/Characters/Run/Gunslinger_Run_DownLeft.png",
    "assets/graphics/Characters/Run/Gunslinger_Run_Down.png",
    "assets/graphics/Characters/Run/Gunslinger_Run_DownRight.png"
};

const std::string attack_paths[8] = {
    "assets/graphics/Characters/Gunslinger/Attack/Gunslinger_Attack_Right.png",
    "assets/graphics/Characters/Gunslinger/Attack/Gunslinger_Attack_UpRight.png",
    "assets/graphics/Characters/Gunslinger/Attack/Gunslinger_Attack_Up.png",
    "assets/graphics/Characters/Gunslinger/Attack/Gunslinger_Attack_UpLeft.png",
    "assets/graphics/Characters/Attack/Gunslinger_Attack_Left.png",
    "assets/graphics/Characters/Attack/Gunslinger_Attack_DownLeft.png",
    "assets/graphics/Characters/Attack/Gunslinger_Attack_Down.png",
    "assets/graphics/Characters/Attack/Gunslinger_Attack_DownRight.png"
};

Gunslinger::Gunslinger(Vector2 start_Position, Object_Manager& om)
    : Player_Base_Class(game::Config::player_Class_One_Max_Health, game::Config::player_Class_One_Movement_Speed,
        game::Config::player_Class_One_Damage, start_Position, om)
{
    // Die Pfade werden nun basierend auf der Richtung geladen
    for (int i = 0; i < 8; ++i) {
        // Explizite Konvertierung des std::string zu einem C-Style-String
        idle_animations.emplace_back(size, idle_paths[i].c_str(), 7, 7);
        run_animations.emplace_back(size, run_paths[i].c_str(), 7, 7);
        attack_animations.emplace_back(size, attack_paths[i].c_str(), 7, 7);
    }
}

Gunslinger::~Gunslinger() {}

// Die Tick-Methode erhält nun die Mausposition als Argument
void Gunslinger::Tick(float delta_time, Vector2 worldMousePos) {
    Player_Base_Class::Tick(delta_time);

    // Die Mausposition muss nicht mehr umgerechnet werden, sie wird direkt verwendet
    mouseLook.Update(this->player_Pos, worldMousePos);

    // 1. Angriff hat Priorität
    if (currentState == PlayerState::ATTACK) {
        attackFrameCounter++;
        if (attackFrameCounter >= attackFrameCountTotal) {
            currentState = PlayerState::IDLE;
            attackFrameCounter = 0;
        }
        return;
    }

    // 2. Zustand basierend auf Input ändern
    bool is_attacking = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (is_attacking) {
        currentState = PlayerState::ATTACK;
        attack_animations[mouseLook.GetDirectionIndex()].First_Frame();
        attackFrameCounter = 0;
    } else if (is_Moving) {
        currentState = PlayerState::RUN;
    } else {
        currentState = PlayerState::IDLE;
    }
}

void Gunslinger::Draw() {
    int current_direction_index = mouseLook.GetDirectionIndex();
    RepeatAnimation* current_animation = nullptr;

    if (currentState == PlayerState::IDLE || currentState == PlayerState::RUN) {
        if (is_Moving) {
            current_animation = &run_animations[current_direction_index];
        } else {
            current_animation = &idle_animations[current_direction_index];
        }
    } else if (currentState == PlayerState::ATTACK) {
        current_animation = &attack_animations[current_direction_index];
    }

    if (current_animation) {
        current_animation->Draw_Current_Frame(this->player_Pos);
        current_animation->Next_Frame();
    }
}