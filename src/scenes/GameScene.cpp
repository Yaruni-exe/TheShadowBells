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

    this->sp_mp = std::make_shared<Gunslinger>(sp, objectManager);
    objectManager.AddObject(sp_mp);

    cam = std::make_shared<Cam>(sp_mp);
    screen.LoadGameObjects(objectManager);

    windowWidth = GetScreenWidth();
    windowHeight = GetScreenHeight();

    cam->cam.offset.x = windowWidth / 2.0f;
    cam->cam.offset.y = windowHeight / 2.0f;

    Rectangle spawner_area = { 200, 200, 300, 300 };

    std::vector<enemy::Enemy_Base_Class*> enemy_List;

    auto spawner = std::make_shared<Level1_Spawner>(
        spawner_area,
        objectManager,
        enemy_List,
        sp_mp
    );

    objectManager.AddObject(spawner);
}

game::scenes::GameScene::~GameScene()
{
}

void game::scenes::GameScene::Update()
{
    if (IsKeyPressed(KEY_ESCAPE))
        game::core::Store::stage->SwitchToNewScene("pause"s, std::make_unique<PauseScene>());
    if (IsKeyPressed(KEY_L)) {
        ToggleFullscreen();
    }

    if (GetScreenWidth() != windowWidth || GetScreenHeight() != windowHeight) {
        windowWidth = GetScreenWidth();
        windowHeight = GetScreenHeight();

        cam->cam.offset.x = windowWidth / 2.0f;
        cam->cam.offset.y = windowHeight / 2.0f;
    }

    Vector2 screenMousePos = GetMousePosition();
    Vector2 worldMousePos = GetScreenToWorld2D(screenMousePos, cam->cam);

    // Rufe die Tick-Methode des Spielers nur EINMAL auf.
    sp_mp->Tick(dtm.Get_Dt(), worldMousePos);

    // Rufe die Tick-Methode für alle ANDEREN Objekte auf.
    for (int i = 0; i < objectManager.managed_objects.size(); ++i) {
        if (objectManager.managed_objects[i].get() != sp_mp.get()) {
            objectManager.managed_objects[i]->Tick(dtm.Get_Dt());
        }
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
  ///Hitbox anzeigen////
    for (const auto& p_object : objectManager.managed_objects)
    {
        if (p_object != nullptr)
        {
            DrawRectangleLinesEx(p_object->Get_Hitbox(), 2.0f, RED);
        }
    }
////////////////
    screen.Draw_Level(this->cam, true);
}