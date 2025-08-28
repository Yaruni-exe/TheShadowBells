#include "UI.h"
#include <iostream>

HUD::HUD(std::shared_ptr<Player_Base_Class> player)
    : player_ptr(player)
{
    // Lade die 5 Texturen für die Lebensanzeige
    portrait_texture = LoadTexture("assets/graphics/UI/Placeholder_Charakterprotrat_UI.png");
    healthbar_textures[0] = LoadTexture("assets/graphics/UI/Sprite_Healthbar_full_4.png"); // 100%
    healthbar_textures[1] = LoadTexture("assets/graphics/UI/Sprite_Healthbar_3.png"); // 75%
    healthbar_textures[2] = LoadTexture("assets/graphics/UI/Sprite_Healthbar_2.png"); // 50%
    healthbar_textures[3] = LoadTexture("assets/graphics/UI/Sprite_Healthbar_1.png"); // 25%
    healthbar_textures[4] = LoadTexture("assets/graphics/UI/Sprite_Healthbar_0.png"); // 0%
}

HUD::~HUD()
{
    UnloadTexture(portrait_texture);
    for (int i = 0; i < 5; ++i) { // Schleife auf 5 aktualisieren
        UnloadTexture(healthbar_textures[i]);
    }
}

void HUD::Draw()
{
    // Position für das Portrait (oben links)
    Vector2 portrait_pos = {20, 20};
    DrawTextureV(portrait_texture, portrait_pos, WHITE);

    // Position für die Lebensanzeige (neben dem Portrait)
    Vector2 healthbar_pos = {portrait_pos.x + portrait_texture.width + 10, portrait_pos.y};

    // Bestimmen Sie, welche Textur gezeichnet werden soll
    int health_index = 0;
    if (player_ptr) {
        float health_percentage = player_ptr->Get_Health() / static_cast<float>(player_ptr->Get_Max_Health());

        // Die Abfragen werden von oben nach unten geprüft
        if (health_percentage == 1.0f) {
            health_index = 0; // Genau 100%
        } else if (health_percentage > 0.5f) {
            health_index = 1; // Zwischen 50% und 100%
        } else if (health_percentage > 0.25f) {
            health_index = 2; // Zwischen 25% und 50%
        } else if (health_percentage > 0.0f) {
            health_index = 3; // Zwischen 0% und 25%
        } else {
            health_index = 4; // Genau 0%
        }
    }

    DrawTextureV(healthbar_textures[health_index], healthbar_pos, WHITE);
}