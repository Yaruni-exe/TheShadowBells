//
// Created by Teilnehmer on 08.09.2025.
//

#ifndef SPECIALVAMPIRE_H
#define SPECIALVAMPIRE_H

#pragma once

#include "../EnemyExtendedBaseClass.h"
#include "raymath.h"
#include "../config_enemys.h.in"

namespace enemy
{
    /**
     * @brief Repräsentiert den Standardvampir.
     * Erbt von der erweiterten Basisklasse und implementiert seine spezifische Logik.
     */
    class SpecialVampire : public EnemyExtendedBaseClass
    {
    public:
        /**
         * @brief Konstruktor für den Standardvampir.
         * @param start_position Die Position, an der der Gegner gespawnt wird.
         */
        SpecialVampire(Vector2 start_position);
        ~SpecialVampire() override = default;

        //  Wir implementieren die Angriffsfunktionen
        void Melee_Attack() override;
        void Range_Attack() override;

        /**
         * @brief Die Update-Methode wird jeden Frame aufgerufen.
         * Hier wird die KI gesteuert (z.B. wann der Gegner angreift).
         * @param delta_time Die Zeit seit dem letzten Frame.
         * @param player_position Die aktuelle Position des Spielers.
         */
        void Update_AI(float delta_time, Vector2 player_position) override;

        /**
         * @brief Erfüllt den Vertrag der Collidable-Klasse.
         */
        void Tick(float delta_time) override;

        /**
         * @brief Zeichnet den Standardvampir.
         */
        void Draw() override;
    };
}

#endif //SPECIALVAMPIRE_H
