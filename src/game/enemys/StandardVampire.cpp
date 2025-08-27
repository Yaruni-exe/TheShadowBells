#include "StandardVampire.h"
#include "../../config_enemys.h.in"
#include <iostream>

namespace enemy
{
    StandardVampire::StandardVampire(Vector2 start_position)
        : EnemyExtendedBaseClass(
            "Standard Vampire",
            game::EnemyConfig::kStandardVampireHealth,
            game::EnemyConfig::kStandardVampireMovementSpeed,
            game::EnemyConfig::kStandardVampireDamage,
            game::EnemyConfig::kStandardVampireValue,
            game::EnemyConfig::kStandardVampireSpritePath,
            nullptr,
            start_position,
            game::EnemyConfig::kStandardVampireHitboxWidth,
            game::EnemyConfig::kStandardVampireHitboxHeight,
            game::EnemyConfig::kStandardVampireAttackCooldown
          )
    {
        // Der Animations-Timer wird bereits in der ExtendedBaseClass initialisiert.
        // Hier sind keine weiteren Initialisierungen nötig, aber möglich.
    }

    void StandardVampire::Update_AI(float delta_time, Vector2 player_position)
    {
        // Rufe zuerst die Basis-Tick-Funktion auf (z.B. für Cooldowns)
        EnemyExtendedBaseClass::Tick(delta_time);

        // --- ZUSTANDS-LOGIK UND TIMER ---
        if (attack_animation_timer > 0.0f) {
            attack_animation_timer -= delta_time;
            // Zustand auf ATTACKING setzen und Bewegung stoppen, solange die Animation läuft.
            current_state = EnemyState::ATTACKING;
            this->is_Moving = false;
        } else {
            // Zustand zurücksetzen, wenn die Animation beendet ist.
            current_state = EnemyState::IDLE;
        }

        // --- ANGRIFFS-LOGIK ---
        float distance_to_player = Vector2Distance({this->hitbox.x, this->hitbox.y}, player_position);

        // Wenn der Spieler in Reichweite ist UND der Cooldown bereit ist UND keine Animation läuft...
        if (distance_to_player <= game::EnemyConfig::kStandardVampireAttackRange && this->attack_Cooldown_Timer <= 0.0f && attack_animation_timer <= 0.0f)
        {
            // ... dann starte die Angriffs-Animation.
            attack_animation_timer = 0.8f; // Setze die Dauer der Animation.

            // Führe den eigentlichen Angriff aus.
            this->Melee_Attack();
        }

        // --- BEWEGUNGS-LOGIK / PATHFINDING ---
        // Rufe Pathfinding nur auf, wenn der Gegner sich bewegen soll.
        if (current_state != EnemyState::ATTACKING && current_state != EnemyState::DYING)
        {
            // Ruft die überschriebene Pathfinding-Methode auf
            this->Pathfinding(player_position.x, player_position.y, delta_time);
        }
    }

    void StandardVampire::Tick(float delta_time)
    {
        // Die Logik für den Vampir ist nun komplett in Update_AI.
        EnemyExtendedBaseClass::Tick(delta_time);
    }

    // Implementierung der Angriffsfunktionen
    void StandardVampire::Melee_Attack()
    {
        // Setzt den Cooldown in der Basisklasse zurück
        this->attack_Cooldown_Timer = this->attack_Cooldown_Duration;


    }

    void StandardVampire::Range_Attack()
    {
        // Leere Implementierung für den Vampir, da er nur Nahkampfangriffe hat.
    }

    // *** FEHLENDE IMPLEMENTIERUNG HINZUGEFÜGT ***
    void StandardVampire::Draw()
    {
        EnemyExtendedBaseClass::Draw();
    }
}