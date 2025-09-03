#pragma once

#include <raylib.h>
#include <memory>

class RepeatAnimation {
private:
    int current_Frame=0;
    int frame_Count;
    int sprites_per_line;
    Vector2 size;
    Rectangle target;
    Texture2D spritesheet;

public:
    // Original-Konstruktor
    RepeatAnimation(Vector2 sprite_size, const char* filename, int FC, int spl);

    // NEU: Konstruktor, der eine bereits geladene Textur akzeptiert
    RepeatAnimation(Vector2 sprite_size, Texture2D texture, int FC, int spl);

    void Next_Frame();
    void First_Frame();
    void Draw_Current_Frame(Vector2);

    // New: Overloaded method to draw at a specific size
    void Draw_Current_Frame(Vector2 position, Vector2 draw_size);

    // New getter to get the current frame
    int Get_Current_Frame() const { return current_Frame; }

    // New getter for the frame count
    int Get_Frame_Count() const { return frame_Count; }
};