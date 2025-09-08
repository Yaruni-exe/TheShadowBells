
/*

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
#include "../game/interactables/Credits.h"
#include "../game/interactables/BombWall.h"
#include "../game/interactables/BombPickup.h"
#include "../game/interactables/Medipack.h"

#include "../game/spawner/Level1Spawner.h"
#include "../config_enemys.h.in"
#include "../game/interactables/Generator.h"
#include "../game/interactables/GeneratorDoor.h"

#include "../game/PlayerClassOne.h"
#include "../core/CollisionManager.h"

#include "../game/EnemyExtendedBaseClass.h"

using namespace std::string_literals;

game::scenes::GameScene::GameScene()
{
    dtm.Start();

    this->sp_mp = std::make_shared<Gunslinger>(sp, objectManager);
    objectManager.AddObject(sp_mp);

    // HUD erstellen und den Spielerpointer übergeben
    this->hud_ptr = std::make_shared<HUD>(sp_mp);

    cam = std::make_shared<Cam>(sp_mp);
    screen.LoadGameObjects(objectManager);

    windowWidth = GetScreenWidth();
    windowHeight = GetScreenHeight();

    cam->cam.offset.x = windowWidth / 2.0f;
    cam->cam.offset.y = windowHeight / 2.0f;

    std::vector<enemy::Enemy_Base_Class*> enemy_List;

    // Erster Spawner
    Rectangle spawner_area_1 = { 780, 250, 60, 400 };
    auto spawner_1 = std::make_shared<Level1_Spawner>(
        spawner_area_1,
        objectManager,
        enemy_List,
        sp_mp,
        6,
        20.0f
    );
    objectManager.AddObject(spawner_1);

    // ZWEITER SPAWNER
    Rectangle spawner_area_2 = { 970, 250, 60, 370 };
    auto spawner_2 = std::make_shared<Level1_Spawner>(
        spawner_area_2,
        objectManager,
        enemy_List,
        sp_mp,
        4,
        20.0f
    );
    objectManager.AddObject(spawner_2);


// Dritter SPAWNER
    Rectangle spawner_area_3 = { 2580, 230, 70, 200 };
    auto spawner_3 = std::make_shared<Level1_Spawner>(
        spawner_area_3,
        objectManager,
           enemy_List,
           sp_mp,
           4,
           12.0f
       );
    objectManager.AddObject(spawner_3);

    // Vierter SPAWNER
    Rectangle spawner_area_4 = { 2980, 230, 90, 180 };
    auto spawner_4 = std::make_shared<Level1_Spawner>(
        spawner_area_4,
        objectManager,
           enemy_List,
           sp_mp,
           4,
           12.0f
       );
    objectManager.AddObject(spawner_4);

    //  MÜNZEN ERSTELLT
    objectManager.AddObject(std::make_shared<Credit>(Vector2{600, 600}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{800, 800}, 50));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1000, 1000}, 200));

    // GENERATOR UND TÜR GRUPPE 1
    // Load the generator texture once for all generators
    Generator::Load_Texture();

    // Load the door texture
    GeneratorDoor::Load_Texture();

    // Two generators and one door linked by "generator_group_1"
    objectManager.AddObject(std::make_shared<Generator>(Vector2{800, 400}, "generator_group_1", 150.0f));
    objectManager.AddObject(std::make_shared<Generator>(Vector2{850, 450}, "generator_group_1", 150.0f));
    objectManager.AddObject(std::make_shared<GeneratorDoor>(Vector2{900, 400}, "generator_group_1", objectManager));

    // GENERATOR UND TÜR GRUPPE 2
    // One generator and one door linked by "generator_group_2"
    objectManager.AddObject(std::make_shared<Generator>(Vector2{1000, 600}, "generator_group_2", 150.0f));
    objectManager.AddObject(std::make_shared<GeneratorDoor>(Vector2{1050, 600}, "generator_group_2", objectManager));

    // BOMBEN UND BOMBENWÄNDE ERSTELLEN
    // Hinzufügen einer Bomb Wall
    objectManager.AddObject(std::make_shared<Bomb_Wall>(Vector2{1200, 500}));

    // Hinzufügen eines Bomben-Pickups in der Nähe der Wand
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{1150, 500}));

    // Sie können weitere Bombenwände und Pickups an anderen Positionen hinzufügen
    objectManager.AddObject(std::make_shared<Bomb_Wall>(Vector2{2000, 800}));
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{1950, 750}));

    // Medipack erstellen
    objectManager.AddObject(std::make_shared<Medipack>(Vector2{1500, 700}, 25.0f));

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
        auto& current_obj = objectManager.managed_objects[i];


        // Prüfe, ob das Objekt ein Gegner ist und führe dessen KI-Logik aus.
        if (current_obj->Get_Collision_Type() == Collision_Type::ENEMY) {
            if (auto enemy = std::dynamic_pointer_cast<enemy::EnemyExtendedBaseClass>(current_obj)) {
                enemy->Update_AI(dtm.Get_Dt(), sp_mp->Get_Position());
            }
        }


        if (current_obj.get() != sp_mp.get()) {
            current_obj->Tick(dtm.Get_Dt());
        }
    }

    // DIESE ZEIEL WURDE ENTFERNT
   // objectManager.AddObject(std::make_shared<Credit>(Vector2{600, 600}, 100));


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
    }s
    ////////////////


    screen.Draw_Level(this->cam, true);

    // Zeigt die Lebenspunkte des Spielers oben links an
    std::string health_text = "HP: " + std::to_string(static_cast<int>(sp_mp->Get_Health()));
    DrawText(health_text.c_str(), 100, 95, 50, BLACK);

    this->hud_ptr->Draw();
}
*/