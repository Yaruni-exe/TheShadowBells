#ifndef LEVEL_TRANSITION_H
#define LEVEL_TRANSITION_H

#include "../game/Collidable.h"
#include <raylib.h>
#include <functional>

class LevelTransition : public Collidable {
public:
    // Der Konstruktor akzeptiert eine Hitbox und eine Aktion.
    LevelTransition(Rectangle hitbox, std::function<void()> transition_action);

    // Die folgenden Methoden müssen implementiert werden, da sie rein virtuell sind.
    Collision_Type Get_Collision_Type() const override;
    void Tick(float delta_time) override;
    void Draw() override;
    void On_Collision(std::shared_ptr<Collidable> other) override;

    // Diese öffentliche Methode wird vom Spieler aufgerufen.
    void TriggerTransition();

    // Virtualer Destruktor für korrekte Speicherfreigabe.
    virtual ~LevelTransition() = default;

private:
    std::function<void()> transition_action;
};

#endif // LEVEL_TRANSITION_H