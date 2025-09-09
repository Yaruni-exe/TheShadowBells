//
// Created by Teilnehmer on 08.09.2025.
//
#include "SpecialVampire.h"
#include "../../config_enemys.h.in"
#include <iostream>

namespace enemy
{
    SpecialVampire::SpecialVampire(Vector2 start_position)
        : EnemyExtendedBaseClass(
            "SpecialnVampire",
            game::EnemyConfig::kSpecialVampireHealth,
            game::EnemyConfig::kSpecialVampireMovementSpeed,
            game::EnemyConfig::kSpecialVampireDamage,
            game::EnemyConfig::kSpecialVampireValue,
            game::EnemyConfig::kSpecialVampireSpritePath,
            nullptr,
            start_position,
            game::EnemyConfig::kSpecialVampireHitboxWidth,
            game::EnemyConfig::kSpecialVampireHitboxHeight,
            game::EnemyConfig::kSpecialVampireAttackCooldown
          )
    {
        // Der Animations-Timer wird bereits in der ExtendedBaseClass initialisiert.
        // Hier sind keine weiteren Initialisierungen nötig, aber möglich.
    }

    void SpecialVampire::Update_AI(float delta_time, Vector2 player_position)
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
        if (distance_to_player <= game::EnemyConfig::kSpecialVampireAttackRange && this->attack_Cooldown_Timer <= 0.0f && attack_animation_timer <= 0.0f)
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

    void SpecialVampire::Tick(float delta_time)
    {
        // Die Logik für den Vampir ist nun komplett in Update_AI.
        EnemyExtendedBaseClass::Tick(delta_time);
    }

    // Implementierung der Angriffsfunktionen
    void SpecialVampire::Melee_Attack()
    {
        // Setzt den Cooldown in der Basisklasse zurück
        this->attack_Cooldown_Timer = this->attack_Cooldown_Duration;


    }

    void SpecialVampire::Range_Attack()
    {
        // Leere Implementierung für den Vampir, da er nur Nahkampfangriffe hat.
    }


    void SpecialVampire::Draw()
    {
        EnemyExtendedBaseClass::Draw();
    }
}