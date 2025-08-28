#include "MenuScene.h"
#include <string>
#include <raylib.h>
#include "Screen.h"
#include <Store.h>
#include "GameScene.h"
#include "../Vectors.h"

using namespace std::string_literals;

game::scenes::MenuScene::MenuScene()
{
    // Your scene initialization code here...
    background_texture = LoadTexture("assets/graphics/backgrounds/Menu.png");

}

game::scenes::MenuScene::~MenuScene()
{
    // Your scene cleanup code here...
    UnloadTexture(background_texture);
}

void game::scenes::MenuScene::Update()
{
    // Your process input and update game scene code here...

    if (IsKeyPressed(KEY_ENTER))
        game::core::Store::stage->ReplaceWithNewScene("menu"s, "game"s, std::make_unique<GameScene>());
}

void game::scenes::MenuScene::Draw()
{
    /*// Your scene drawing code here...
    // Note that scene-actors are drawn automatically
    //DrawText("Menu - press ENTER to load game scene", 10, 10, 30, LIGHTGRAY);
    for (int i = 0; i < vec_cons.size(); ++i)
    {
        vec_cons[i].Draw();
    }
    for (int i = 0; i < vec_walls.size(); ++i)
    {
        vec_walls[i].Draw();*/

    ClearBackground(BLACK); // Optional: Hintergrund füllen, falls das Bild nicht den gesamten Bildschirm ausfüllt.

    // Quelle: Das gesamte Bild von der Textur
    Rectangle source_rec = { 0.0f, 0.0f, (float)background_texture.width, (float)background_texture.height };

    // Ziel: Der gesamte Bildschirm
    Rectangle dest_rec = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };

    // Ursprung und Rotation sind 0.0f
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(background_texture, source_rec, dest_rec, origin, 0.0f, WHITE);

    // Ihre vorhandene Logik für den Text kann hier wieder eingefügt werden.
    DrawText("Menu - press ENTER to load game scene", 10, 10, 30, LIGHTGRAY);

    }

