#include "Level2Scene.h"

#include <EndScene.h>
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
#include "../game/spawner/Level1Spawner.h" // Wiederverwendeter Spawner
#include "../game/spawner/Level2Spawner.h"
#include "../config_enemys.h.in"
#include "../game/interactables/Generator.h"
#include "../game/interactables/GeneratorDoor.h"
#include "../game/PlayerClassOne.h"
#include "../core/CollisionManager.h"
#include "../game/EnemyExtendedBaseClass.h"
#include "LevelTransition.h"
#include "MenuScene.h"



using namespace std::string_literals;

game::scenes::Level2Scene::Level2Scene()
: p_cm(wb, objectManager.managed_objects)
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
    Rectangle spawner_area_1 = { 1344, 672, 256, 128 };
    auto spawner_1 = std::make_shared<Level1_Spawner>(
        spawner_area_1,
        objectManager,
        enemy_List,
        sp_mp,
        10,
        10.0f
    );
    objectManager.AddObject(spawner_1);

    // ZWEITER SPAWNER
    Rectangle spawner_area_2 = { 2016, 672, 256, 128 };
    auto spawner_2 = std::make_shared<Level1_Spawner>(
        spawner_area_2,
        objectManager,
        enemy_List,
        sp_mp,
        8,
        10.0f
    );
    objectManager.AddObject(spawner_2);


    // Dritter SPAWNER
    Rectangle spawner_area_3 = { 1344, 1088, 256, 96 };
    auto spawner_3 = std::make_shared<Level1_Spawner>(
        spawner_area_3,
        objectManager,
           enemy_List,
           sp_mp,
           6,
           10.0f
       );
    objectManager.AddObject(spawner_3);

    // Vierter SPAWNER
    Rectangle spawner_area_4 = { 2016, 1088, 256, 96 };
    auto spawner_4 = std::make_shared<Level1_Spawner>(
        spawner_area_4,
        objectManager,
           enemy_List,
           sp_mp,
           6,
           10.0f
       );
    objectManager.AddObject(spawner_4);

    Rectangle spawner_area_5 = { 1920, 1856, 160, 160 };
    auto spawner_5 = std::make_shared<Level1_Spawner>(
        spawner_area_5,
        objectManager,
           enemy_List,
           sp_mp,
           6,
           10.0f
       );
    objectManager.AddObject(spawner_5);

    Rectangle spawner_area_6 = { 2368, 1952, 128, 64 };
    auto spawner_6 = std::make_shared<Level2_Spawner>(
        spawner_area_6,
        objectManager,
           enemy_List,
           sp_mp,
           4,
           10.0f
       );
    objectManager.AddObject(spawner_6);

    Rectangle spawner_area_7 = { 2720, 800, 96, 96 };
    auto spawner_7 = std::make_shared<Level1_Spawner>(
        spawner_area_7,
        objectManager,
           enemy_List,
           sp_mp,
           6,
           10.0f
       );
    objectManager.AddObject(spawner_7);

    Rectangle spawner_area_8 = { 2528, 1504, 96, 64 };
    auto spawner_8 = std::make_shared<Level2_Spawner>(
        spawner_area_8,
        objectManager,
           enemy_List,
           sp_mp,
           5,
           10.0f
       );
    objectManager.AddObject(spawner_8);

    Rectangle spawner_area_9 = { 3680, 2112, 96, 96 };
    auto spawner_9 = std::make_shared<Level1_Spawner>(
        spawner_area_9,
        objectManager,
           enemy_List,
           sp_mp,
           5,
           10.0f
       );
    objectManager.AddObject(spawner_9);

    Rectangle spawner_area_10 = { 3200, 1248, 160, 224 };
    auto spawner_10 = std::make_shared<Level2_Spawner>(
        spawner_area_10,
        objectManager,
           enemy_List,
           sp_mp,
           5,
           15.0f
       );
    objectManager.AddObject(spawner_10);

    Rectangle spawner_area_11 = { 3872, 1248, 160, 224 };
    auto spawner_11 = std::make_shared<Level2_Spawner>(
        spawner_area_11,
        objectManager,
           enemy_List,
           sp_mp,
           4,
           20.0f
       );
    objectManager.AddObject(spawner_11);

    Rectangle spawner_area_12 = { 3552, 1472, 128, 160 };
    auto spawner_12 = std::make_shared<Level2_Spawner>(
        spawner_area_12,
        objectManager,
           enemy_List,
           sp_mp,
           4,
           20.0f
       );
    objectManager.AddObject(spawner_12);

    //  MÜNZEN ERSTELLT
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1376, 704}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1376, 1120}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1600, 2208}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2432, 928}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2752, 800}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2560, 1376}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1920, 832}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1920, 1024}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{3968, 1568}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{3840, 1568}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{3584, 1376}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{3616, 1376}, 100));


    // Load the generator texture once for all generators
     Generator::Load_Texture();
    // Load the door texture
    //GeneratorDoor::Load_Texture();

    // GENERATOR UND TÜR GRUPPE 1
    // Generatoren erstellen (unverändert)
    objectManager.AddObject(std::make_shared<Generator>(Vector2{3264, 1184}, "generator_group_1", 300.0f));
    objectManager.AddObject(std::make_shared<Generator>(Vector2{3926, 1184}, "generator_group_1", 300.0f));

    // Tür individuell mit eigener Hitbox und Sprite
    objectManager.AddObject(std::make_shared<GeneratorDoor>(
        Vector2{3584, 1408},       // Position bleibt gleich
        Vector2{64, 90},           // neue Hitbox
        "generator_group_1",       // Gruppierung
        objectManager,
        "assets/graphics/Items/Generator/Zauntor_Base_Sprite.png" // optional individuelles Sprite
    ));

    // GENERATOR UND TÜR GRUPPE 2
    objectManager.AddObject(std::make_shared<Generator>(Vector2{992, 736}, "generator_group_2", 1.0f));
    objectManager.AddObject(std::make_shared<GeneratorDoor>(
        Vector2{1216, 896},        // Position
        Vector2{40, 100},           // eigene Hitbox
        "generator_group_2",
        objectManager,
        "assets/graphics/Items/Generator/Zauntor_Base_Sprite.png"
    ));

    // GENERATOR UND TÜR GRUPPE 3
    objectManager.AddObject(std::make_shared<Generator>(Vector2{2208, 672}, "generator_group_3", 1.0f));
    objectManager.AddObject(std::make_shared<GeneratorDoor>(
        Vector2{2304, 896},        // Position
        Vector2{70, 85},           // eigene Hitbox
        "generator_group_3",
        objectManager,
        "assets/graphics/Items/Generator/Zauntor_Base_Sprite.png"
    ));


    // Medipack erstellen
    objectManager.AddObject(std::make_shared<Medipack>(Vector2{3232, 1568}, 25.0f));

    // Hinzufügen der Level-Übergangs-Hitbox
    Rectangle level_transition_hitbox = { 3584.0f, 1056.0f, 64.0f, 64.0f };
    objectManager.AddObject(std::make_shared<LevelTransition>(
        level_transition_hitbox,
        // Diese Lambda-Funktion ruft einfach die VideoScene auf, ohne den Pfad zu kennen.
        []() {
            game::core::Store::stage->SwitchToNewScene(
                "menu"s,
                std::make_unique<game::scenes::EndScene>()
            );
        }
    ));
}


game::scenes::Level2Scene::~Level2Scene()
{
}

void game::scenes::Level2Scene::Update()
{
    // Korrigierte Pause-Logik: Verwende SwitchToNewScene mit std::make_shared
    if (IsKeyPressed(KEY_ESCAPE))
        game::core::Store::stage->SwitchToNewScene("pause"s, std::make_shared<PauseScene>());

    // Die restliche Update-Logik deines Spiels, die nur ausgeführt wird,
    // wenn das Spiel aktiv (und nicht pausiert) ist

    if (IsKeyPressed(KEY_L)) {
        ToggleFullscreen();
    }

    // Mausposition in Spielkoordinaten umwandeln
    Vector2 screenMousePos = GetMousePosition();
    Vector2 worldMousePos = GetScreenToWorld2D(screenMousePos, cam->cam);

    // Spieler-Tick aufrufen
    sp_mp->Tick(dtm.Get_Dt(), worldMousePos);

    // Wichtige Korrektur: Die KI der Gegner muss VOR ihrem Tick-Aufruf aktualisiert werden.
    for (int i = 0; i < objectManager.managed_objects.size(); ++i) {
        auto& current_obj = objectManager.managed_objects[i];

        if (current_obj->Get_Collision_Type() == Collision_Type::ENEMY) {
            if (auto enemy = std::dynamic_pointer_cast<enemy::EnemyExtendedBaseClass>(current_obj)) {
                enemy->Update_AI(dtm.Get_Dt(), sp_mp->Get_Position());
            }
        }

        if (current_obj.get() != sp_mp.get()) {
            current_obj->Tick(dtm.Get_Dt());
        }
    }

    // Vermeide das Neuladen des HUDs und der Kamera bei jeder Aktualisierung
    if (GetScreenWidth() != windowWidth || GetScreenHeight() != windowHeight) {
        windowWidth = GetScreenWidth();
        windowHeight = GetScreenHeight();
        cam->cam.offset.x = windowWidth / 2.0f;
        cam->cam.offset.y = windowHeight / 2.0f;
    }

    // Kollisionsmanager und Objektbereinigung
    p_cm.Check_Collisions();
    objectManager.Cleanup_Objects();
    cam->Cam_Movement(dtm.Get_Dt());

    // dtm.Update() am Ende aufrufen
    dtm.Update();
}

void game::scenes::Level2Scene::Draw()
{
    ClearBackground(WHITE);
    screen.Draw_Level(this->cam, false);

    BeginMode2D(cam->cam);

    // Objekte zeichnen
    for (int i = 0; i < objectManager.managed_objects.size(); ++i) {
        objectManager.managed_objects[i]->Draw();
    }

    // Debugging-Hitboxen
    for (const auto& p_object : objectManager.managed_objects) {
        if (p_object != nullptr) {
            DrawRectangleLinesEx(p_object->Get_Hitbox(), 2.0f, RED);
        }
    }

    EndMode2D();

    screen.Draw_Level(this->cam, true);

    // HUD zeichnen
    this->hud_ptr->Draw();




}