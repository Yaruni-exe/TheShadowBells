//
// Created by $Will on 22.06.2025.
//

#include "PlayerClassOne.h"
#include "../config.h.in"
#include "raylib.h" // For IsKeyDown

Player_Class_One::Player_Class_One(Vector2 start_Position)
    : Player_Base_Class(game::Config::player_Class_One_Max_Health, game::Config::player_Class_One_Movement_Speed,
        game::Config::player_Class_One_Damage, start_Position),
      // --- START OF MEMBER INITIALIZER LIST ---
      // 1. Initialize the size Vector2 members first
      size_top_down{20, 32},
      size_left_right{27, 32},
      // 2. Then, initialize the RepeatAnimation members, using the now-initialized size members
      Run_Front{size_top_down, "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Front.png", 7, 7},
      Run_Back{size_top_down, "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Back.png", 7, 7},
      Run_Left{size_left_right, "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Left.png", 8, 8},
      Run_Right{size_left_right, "assets/graphics/Characters/Gunslinger/Gunslinger_Run_Cycle_Right.png", 8, 8}
      // --- END OF MEMBER INITIALIZER LIST ---
{
    // Hitbox
    this->hitbox.width = 20.0f; // Set a default hitbox width
    this->hitbox.height = 32.0f;

    // Set the initial animation
    current_animation = &Run_Front;
}
Player_Class_One::~Player_Class_One() {
    // If RepeatAnimation handles LoadTexture/UnloadTexture internally,
    // its destructors will be called automatically when Player_Class_One is destroyed.
    // No explicit UnloadTexture calls needed here unless RepeatAnimation *doesn't*
    // handle resource cleanup in its destructor.
}

void Player_Class_One::Draw() {
    this->is_Moving = false; // Reset movement status

    // Select animation based on WASD input
    if (IsKeyDown(KEY_W)) {
        current_animation = &Run_Back;
        this->is_Moving = true;
    }
    if (IsKeyDown(KEY_S)) {
        current_animation = &Run_Front;
        this->is_Moving = true;
    }
    if (IsKeyDown(KEY_A)) {
        current_animation = &Run_Left;
        this->is_Moving = true;
    }
    if (IsKeyDown(KEY_D)) {
        current_animation = &Run_Right;
        this->is_Moving = true;
    }

    // Draw the current frame of the selected animation
    current_animation->Draw_Current_Frame(this->player_Pos);

    // Only advance the animation if the character is moving
    if (this->is_Moving) {
        current_animation->Next_Frame();
    }
}