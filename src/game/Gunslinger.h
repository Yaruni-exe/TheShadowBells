#ifndef GUNSLINGER_H
#define GUNSLINGER_H

#include "PlayerBaseClass.h"
#include "Animations.h"
#include "RepeatAnimation.h"
#include "MouseLook.h"
#include <vector>
#include "Object_Manager.h"

class Gunslinger : public Player_Base_Class
{
private:
    Vector2 size{20, 32};
    MouseLook mouseLook;
    Vector2 mouse_World_Position;

    std::vector<RepeatAnimation> idle_animations;
    std::vector<RepeatAnimation> run_animations;
    std::vector<RepeatAnimation> attack_animations;

    enum class PlayerState { IDLE, RUN, ATTACK };
    PlayerState currentState = PlayerState::IDLE;

    int attackFrameCounter = 0;
    const int attackFrameCountTotal = 7;

    float ranged_Cooldown_Timer; // Für die Kontrolle der Feuerrate

public:
    // Konstruktor ist jetzt identisch zur Player_Class_One
    Gunslinger(Vector2 start_Position, Object_Manager& om);
    ~Gunslinger();

    void Draw() override;
    // Die Tick-Methode muss die Mausposition in Weltkoordinaten erhalten
    void Tick(float delta_time, Vector2 worldMousePos);
    void Ranged_Attack() override;
private:
    void Clean_Up_Projectiles();
};

#endif // GUNSLINGER_H