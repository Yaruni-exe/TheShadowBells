#include "StandardVampire.h"
#include "../../config_enemys.h.in"

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

    // --- ZUSTANDS-LOGIK ---

    // Wenn eine Angriffsanimation läuft, zähle den Timer herunter.
    if (attack_animation_timer > 0.0f) {
        attack_animation_timer -= delta_time;
    }

    // BEWEGUNG: Führe die Pathfinding-Logik nur aus, wenn gerade KEINE Angriffsanimation läuft.
    if (attack_animation_timer <= 0.0f) {
        Pathfinding(player_position.x, player_position.y, delta_time);
    }

    // --- ANGRIFFS-LOGIK ---
    float distance_to_player = Vector2Distance({this->hitbox.x, this->hitbox.y}, player_position);

    // Wenn der Spieler in Reichweite ist UND der Cooldown bereit ist UND keine Animation läuft...
    if (distance_to_player <= game::EnemyConfig::kStandardVampireAttackRange && this->attack_Cooldown_Timer <= 0.0f && attack_animation_timer <= 0.0f)
    {
        // ... dann starte die Angriffs-Animation.
        attack_animation_timer = 0.8f; // Setze die Dauer der Animation. Anpassen!

        // Führe den eigentlichen Angriff aus.
        this->Melee_Attack();
    }
}

    void StandardVampire::Tick(float delta_time)
    {
    }

    // Implementierung der Angriffsfunktionen
    void StandardVampire::Melee_Attack()
    {
        // Setzt den Cooldown in der Basisklasse zurück
        this->attack_Cooldown_Timer = this->attack_Cooldown_Duration;

        // TO-DO: Zukünftige Logik
        // 1. Setze Gegner-Zustand auf "ATTACKING"
        // 2. Spiele Angriffsanimation ab
        // 3. Erzeuge eine temporäre Hitbox für den Schaden
    }

    void StandardVampire::Range_Attack()
    {
    }

    void StandardVampire::Draw()
    {
        // TO-DO: Hier wird später die Animations-Logik basierend
        // auf dem Gegner-Zustand (Idle, Flying, Attacking, Dying) stehen.
        if (sprite.id > 0)
        {
            DrawTextureV(this->sprite, {this->hitbox.x, this->hitbox.y}, WHITE);
        }
    }
}