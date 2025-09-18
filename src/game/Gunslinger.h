#ifndef GUNSLINGER_H
#define GUNSLINGER_H

#include "PlayerBaseClass.h"
#include "Animations.h"
#include "MouseLook.h"
#include <vector>
#include "Object_Manager.h"
#include <memory>
#include "raylib.h"
#include "Collidable.h"
#include "EnemyBaseClass.h"

class Gunslinger : public Player_Base_Class
{

    Vector2 size{64, 31};
    MouseLook mouseLook;
    Vector2 mouse_World_Position;

    void On_Collision(std::shared_ptr<Collidable> other) override;

    // Wir verwenden jetzt einfache Texturen und verwalten die Animation manuell
    std::vector<Texture2D> idle_textures;
    std::vector<Texture2D> run_textures;
    std::vector<Texture2D> attack_textures;

    enum class PlayerState { IDLE, RUN, ATTACK };
    PlayerState currentState = PlayerState::IDLE;

    // Für die manuelle Animation
    int current_frame = 0;
    float frame_timer = 0.0f;
    const float animation_speed = 0.4f;

    float ranged_Cooldown_Timer; // Für die Kontrolle der Feuerrate
    int bombs = 0;

public:
    Gunslinger(Vector2 start_Position, Object_Manager& om);
    ~Gunslinger();

    void Draw() override;
    // Die Tick-Methode muss die Mausposition in Weltkoordinaten erhalten
    void Tick(float delta_time, Vector2 worldMousePos);
    void Ranged_Attack() override;
    void Add_Bomb();
    int Get_Bomb_Count() const;
    void Use_Bomb();

private:
    void Clean_Up_Projectiles();
};

#endif // GUNSLINGER_H