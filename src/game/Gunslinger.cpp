#include "Gunslinger.h"
#include "../config.h.in"
#include "raymath.h"

// ... (Pfade für Animationen bleiben gleich)

// Der Konstruktor ist jetzt identisch zur Player_Class_One
Gunslinger::Gunslinger(Vector2 start_Position, Object_Manager& om)
    : Player_Base_Class(game::Config::player_Class_One_Max_Health, game::Config::player_Class_One_Movement_Speed,
        game::Config::player_Class_One_Damage, start_Position, om)
{
    for (int i = 0; i < 8; ++i) {
        idle_animations.emplace_back(size, "assets/graphics/Characters/Gunslinger/Gunslinger_Idle_Front.png", 7, 7);
        run_animations.emplace_back(size, "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png", 7, 7);
        attack_animations.emplace_back(size, "assets/graphics/Characters/Gunslinger/Gunslinger_Attack_Right.png", 7, 7);
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