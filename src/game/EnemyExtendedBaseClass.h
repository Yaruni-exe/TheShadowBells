#pragma once

#include "EnemyBaseClass.h"
#include <memory>

namespace enemy
{
    // Neuer Enum-Typ, um den Zustand des Gegners zu verfolgen
    enum class EnemyState { IDLE, CHASING, ATTACKING, DYING };

    /**
     * @brief Eine erweiterte Basisklasse für Gegner, die KI-Funktionalität hinzufügt.
     *
     * Diese Klasse erbt von der ursprünglichen Enemy_Base_Class und fügt
     * reine virtuelle Funktionen für KI-Logik, Angriffe und weitere
     * nützliche Member-Variablen hinzu, um die Entwicklung konkreter Gegner
     * zu vereinfachen.
     */
    class EnemyExtendedBaseClass : public Enemy_Base_Class
    {
    protected:
        // Neue Member-Variablen aus der zweiten Version
        EnemyState current_state;
        float attack_animation_timer;

    public:
        // Konstruktor, der die Parameter an die ursprüngliche Basisklasse weiterleitet
        EnemyExtendedBaseClass(std::string name, int health, float movement_speed, int damage, int value,
                                const char* sprite_path, const char* projectile_sprite_path, Vector2 start_position, int width, int height,
                                float cooldown_duration)
            : Enemy_Base_Class(name, health, movement_speed, damage, value, sprite_path, projectile_sprite_path,
                               start_position, width, height, cooldown_duration),
              current_state(EnemyState::IDLE), // Neue Variable initialisieren
              attack_animation_timer(0.0f) {}

        virtual ~EnemyExtendedBaseClass() = default;

        // --- Reine virtuelle Funktionen (MUSS von abgeleiteten Klassen implementiert werden) ---
        virtual void Update_AI(float delta_time, Vector2 player_position) = 0;
        virtual void Melee_Attack() = 0;
        virtual void Range_Attack() = 0;

        // --- Geerbte Methoden, die wir in dieser Klasse überschreiben, um die Logik anzupassen ---
        void Take_Damage(int damage_amount);
        void Pathfinding(float target_Position_X, float target_Position_Y, float delta_Time) override;
        void On_Collision(std::shared_ptr<Collidable> other) override;
        void Draw() override;
        virtual void Tick(float delta_time);
    };
}