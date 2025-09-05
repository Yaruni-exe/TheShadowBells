#include "RepeatAnimation.h"
#include "raylib.h"

RepeatAnimation::RepeatAnimation(Vector2 sprite_size, const char* filename, int FC, int spl, float FPS) {
    this->spritesheet = LoadTexture(filename);
    this->size = sprite_size;
    this->frame_Count = FC;
    this->sprites_per_line = spl;
    this->target = Rectangle{0, 0, this->size.x, this->size.y};

    this->frame_Time = 1.0f / FPS;
    this->frame_Timer = 0.0f;
}

RepeatAnimation::RepeatAnimation(Vector2 sprite_size, Texture2D texture, int FC, int spl, float FPS) {
    this->spritesheet = texture;
    this->size = sprite_size;
    this->frame_Count = FC;
    this->sprites_per_line = spl;
    this->target = Rectangle{0, 0, this->size.x, this->size.y};

    this->frame_Time = 1.0f / FPS;
    this->frame_Timer = 0.0f;
}

bool RepeatAnimation::Next_Frame(float delta_time) {
    bool cycle_finished = false;
    this->frame_Timer += delta_time;

    if (this->frame_Timer >= this->frame_Time) {
        this->current_Frame++;

        if (this->current_Frame >= this->frame_Count) {
            this->current_Frame = 0;
            cycle_finished = true;
        }

        this->target.x = (this->current_Frame % this->sprites_per_line) * this->size.x;
        this->target.y = (this->current_Frame / this->sprites_per_line) * this->size.y;

        this->frame_Timer -= this->frame_Time;
    }
    return cycle_finished;
}

// HIER: Implementierung der fehlenden Methoden
void RepeatAnimation::First_Frame() {
    this->current_Frame = 0;
    this->target.x = 0;
    this->target.y = 0;
    this->frame_Timer = 0.0f;
}

void RepeatAnimation::Draw_Current_Frame(Vector2 position) {
    // Rufe die Standard-Raylib-Funktion auf
    DrawTextureRec(this->spritesheet, this->target, position, WHITE);
}

void RepeatAnimation::Draw_Current_Frame(Vector2 position, Vector2 draw_size) {
    // Rufe die skalierte Raylib-Funktion auf
    DrawTexturePro(this->spritesheet, this->target, {position.x, position.y, draw_size.x, draw_size.y}, {0, 0}, 0.0f, WHITE);
}
