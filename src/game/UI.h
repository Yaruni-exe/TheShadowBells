#pragma once

#include "raylib.h"
#include "Gunslinger.h"

class HUD
{
private:
    Texture2D portrait_texture;
    Texture2D healthbar_textures[5]; // Array für die 4 Zustände der Lebensanzeige
     std::shared_ptr<Gunslinger> player_ptr; // Ein Pointer zum Spielerobjekt

    Texture2D bomb_icon_texture;

public:
    // Der Konstruktor benötigt eine Referenz zum Spieler
    HUD(std::shared_ptr<Gunslinger> player);

    // Die Draw-Methode zeichnet die Benutzeroberfläche
    void Draw();

    // Destruktor, um Texturen zu entladen
    ~HUD();
};