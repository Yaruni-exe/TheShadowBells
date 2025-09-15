#include "LevelTransition.h"
#include <iostream>


// Der Konstruktor initialisiert die Basisklasse-Hitbox und die Aktion.
LevelTransition::LevelTransition(Rectangle hitbox, std::function<void()> action)
    : transition_action(action) {
    this->hitbox = hitbox;
}

// Gibt den Kollisionstyp zurück, wie vom Spieler erwartet.
Collision_Type LevelTransition::Get_Collision_Type() const {
    return Collision_Type::LEVEL_EXIT;
}

// Eine leere Tick-Methode.
void LevelTransition::Tick(float delta_time) {
}

// Zeichnet die Hitbox für Debugging-Zwecke.
void LevelTransition::Draw() {
   // DrawRectangleRec(hitbox, GREEN);
}

// Die eigentliche Logik wird nicht hier, sondern im Gunslinger ausgeführt.
void LevelTransition::On_Collision(std::shared_ptr<Collidable> other) {
}

// Führt die übergebene Funktion aus.
void LevelTransition::TriggerTransition() {
    if (transition_action) {
        transition_action();
    }
}