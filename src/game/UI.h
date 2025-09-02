#pragma once

#include "raylib.h"
#include "PlayerBaseClass.h"

class HUD
{
private:
    Texture2D portrait_texture;
    Texture2D healthbar_textures[5]; // Array für die 4 Zustände der Lebensanzeige
    std::shared_ptr<Player_Base_Class> player_ptr; // Ein Pointer zum Spielerobjekt

public:
    // Der Konstruktor benötigt eine Referenz zum Spieler
    HUD(std::shared_ptr<Player_Base_Class> player);

    // Die Draw-Methode zeichnet die Benutzeroberfläche
    void Draw();

    // Destruktor, um Texturen zu entladen
    ~HUD();
};