#pragma once

#include <raylib.h>
#include <memory>

class RepeatAnimation {
private:
    int current_Frame = 0;
    int frame_Count;
    int sprites_per_line;
    Vector2 size;
    Rectangle target;
    Texture2D spritesheet;

    float frame_Time;
    float frame_Timer;

public:
    // Zwei verschiedene Konstruktoren, die den FPS-Parameter benötigen
    RepeatAnimation(Vector2 sprite_size, const char* filename, int FC, int spl, float FPS);
    RepeatAnimation(Vector2 sprite_size, Texture2D texture, int FC, int spl, float FPS);

    // Die Next_Frame-Methode gibt nun einen bool zurück
    bool Next_Frame(float delta_time);

    // Die Methoden, die der Linker als fehlend gemeldet hat
    void First_Frame();
    void Draw_Current_Frame(Vector2);
    void Draw_Current_Frame(Vector2 position, Vector2 draw_size);

    int Get_Current_Frame() const { return current_Frame; }
    int Get_Frame_Count() const { return frame_Count; }
};
