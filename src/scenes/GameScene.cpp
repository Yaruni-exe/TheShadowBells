#include "GameScene.h"
#include <memory>
#include <string>
#include <raylib-cpp.hpp>
#include <raylib.h>
#include "Screen.h"
#include <Store.h>
#include "PauseScene.h"
#include "Renderer.h"
#include "SpriteAnimated.h"

#include "../game/spawner/Level1Spawner.h"
#include "../config_enemys.h.in"

#include "../game/PlayerClassOne.h"
#include "../core/CollisionManager.h"

using namespace std::string_literals;

game::scenes::GameScene::GameScene()
{
    dtm.Start();

    // 1. Spieler erstellen und hinzufügen
    this->sp_mp=std::make_shared<Player_Class_One>(sp,objectManager);
    objectManager.AddObject(sp_mp);

    // 2. Kamera erstellen und mit Spieler verbinden
    cam=std::make_shared<Cam>(sp_mp);
    screen.LoadGameObjects(objectManager);

    // 3. Spawner erstellen und hinzufügen
    // Definiere den Spawnbereich
    Rectangle spawner_area = { 200, 200, 300, 300 };
    // Die obstacle_List muss mit deinen Wänden gefüllt werden,
    // hier als leere Liste für das Beispiel.
    std::vector<Rectangle> obstacle_List = {};
    // enemy_List wird von Level1Spawner nicht mehr direkt verwendet,
    // da er die Gegner dem ObjectManager hinzufügt. Aber die Signatur
    // der Basisklasse erfordert sie noch.
    std::vector<enemy::Enemy_Base_Class*> enemy_List;

    auto spawner = std::make_shared<Level1_Spawner>(
        spawner_area,
        obstacle_List,
        enemy_List,
        game::EnemyConfig::kSpawner1_SpawnRate,
        game::EnemyConfig::kSpawner1_MaxEnemies,
        objectManager
    );

        objectManager.AddObject(spawner);

    // Your scene initialization code here...

}

game::scenes::GameScene::~GameScene()
{
    // Your scene cleanup code here...
}

void game::scenes::GameScene::Update()
{
    // Your process input and update game scene code here...
    if (IsKeyPressed(KEY_ESCAPE))
        game::core::Store::stage->SwitchToNewScene("pause"s, std::make_unique<PauseScene>());
    if (IsKeyPressed(KEY_L)){
        ToggleFullscreen();
    }



    for (int i = 0; i < objectManager.managed_objects.size(); ++i) {
        objectManager.managed_objects[i]->Tick(dtm.Get_Dt());
    }
    this->cam->Cam_Movement(dtm.Get_Dt());
    this->p_cm->Check_Collisions();
    objectManager.Cleanup_Objects();
    dtm.Update();
}

void game::scenes::GameScene::Draw()
{
    BeginDrawing();
    ClearBackground(WHITE);
    screen.Draw_Level(this->cam, false);
    BeginMode2D(cam->cam);

    for (int i = 0; i < objectManager.managed_objects.size(); ++i) {
        objectManager.managed_objects[i]->Draw();
    }

    /////////hitbox anzeigen///////
    for (const auto& p_object : objectManager.managed_objects)
    {
        if (p_object != nullptr)
        {
            DrawRectangleLinesEx(p_object->Get_Hitbox(), 2.0f, RED);
        }
    }
    //////////////


    screen.Draw_Level(this->cam, true);


}