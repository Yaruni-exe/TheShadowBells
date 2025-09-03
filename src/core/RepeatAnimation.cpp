#include "RepeatAnimation.h"
#include "raylib.h"

RepeatAnimation::RepeatAnimation(Vector2 sprite_size, const char* filename, int FC, int spl) {
    this->spritesheet = LoadTexture(filename);
    this->size = sprite_size;
    this->frame_Count = FC;
    this->sprites_per_line = spl;
    this->target = Rectangle{0, 0, this->size.x, this->size.y};
}

RepeatAnimation::RepeatAnimation(Vector2 sprite_size, Texture2D texture, int FC, int spl) {
    this->spritesheet = texture;
    this->size = sprite_size;
    this->frame_Count = FC;
    this->sprites_per_line = spl;
    this->target = Rectangle{0, 0, this->size.x, this->size.y};
}

void RepeatAnimation::First_Frame() {
    this->current_Frame = 0;
    this->target.x = 0;
    this->target.y = 0;
}

void RepeatAnimation::Next_Frame() {
    this->current_Frame++;

    if (this->current_Frame < this->frame_Count) {
        this->target.x = (this->current_Frame % this->sprites_per_line) * this->size.x;
        this->target.y = (this->current_Frame / this->sprites_per_line) * this->size.y;
    } else {
        First_Frame();
    }
}

void RepeatAnimation::Draw_Current_Frame(Vector2 pos) {
    DrawTextureRec(spritesheet, target, pos, WHITE);
}

// New overloaded function
void RepeatAnimation::Draw_Current_Frame(Vector2 pos, Vector2 draw_size) {
    Rectangle dest = { pos.x, pos.y, draw_size.x, draw_size.y };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(spritesheet, target, dest, origin, 0.0f, WHITE);
}