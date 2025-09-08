#include "Level2Scene.h"
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
    Rectangle spawner_area_1 = { 1000, 1000, 100, 500 };
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
    Rectangle spawner_area_2 = { 1800, 1800, 150, 400 };
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
    Rectangle spawner_area_3 = { 2580, 230, 70, 200 };
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
    Rectangle spawner_area_4 = { 2980, 230, 90, 180 };
    auto spawner_4 = std::make_shared<Level1_Spawner>(
        spawner_area_4,
        objectManager,
           enemy_List,
           sp_mp,
           6,
           10.0f
       );
    objectManager.AddObject(spawner_4);

    //  MÜNZEN ERSTELLT
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1200, 1200}, 100));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1400, 1400}, 50));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1600, 1600}, 200));

    // GENERATOR UND TÜR GRUPPE 1
    // Load the generator texture once for all generators
    Generator::Load_Texture();

    // Load the door texture
    GeneratorDoor::Load_Texture();

    // Two generators and one door linked by "generator_group_1"
    objectManager.AddObject(std::make_shared<Generator>(Vector2{1800, 1000}, "generator_group_1", 150.0f));
    objectManager.AddObject(std::make_shared<Generator>(Vector2{1850, 1050}, "generator_group_1", 150.0f));
    objectManager.AddObject(std::make_shared<GeneratorDoor>(Vector2{1900, 1100}, "generator_group_1", objectManager));

    // GENERATOR UND TÜR GRUPPE 2
    // One generator and one door linked by "generator_group_2"
    objectManager.AddObject(std::make_shared<Generator>(Vector2{2000, 1600}, "generator_group_2", 150.0f));
    objectManager.AddObject(std::make_shared<GeneratorDoor>(Vector2{2050, 1600}, "generator_group_2", objectManager));



    // BOMBEN UND BOMBENWÄNDE ERSTELLEN

    Bomb_Pickup::Load_Texture();
    Bomb_Wall::Load_Texture();
    // Hinzufügen einer Bomb Wall
    objectManager.AddObject(std::make_shared<Bomb_Wall>(Vector2{2200, 2500}));

    // Hinzufügen eines Bomben-Pickups in der Nähe der Wand
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{2150, 2450}));

    // Sie können weitere Bombenwände und Pickups an anderen Positionen hinzufügen
    objectManager.AddObject(std::make_shared<Bomb_Wall>(Vector2{2600, 2800}));
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{2550, 2750}));

    // Medipack erstellen
    objectManager.AddObject(std::make_shared<Medipack>(Vector2{2500, 2700}, 25.0f));

    // Hinzufügen der Level-Übergangs-Hitbox
    Rectangle level_transition_hitbox = { 3500.0f, 3500.0f, 100.0f, 200.0f };
    objectManager.AddObject(std::make_shared<LevelTransition>(
        level_transition_hitbox,
        // Diese Lambda-Funktion ruft einfach die VideoScene auf, ohne den Pfad zu kennen.
        []() {
            game::core::Store::stage->SwitchToNewScene(
                "menu"s,
                std::make_unique<game::scenes::MenuScene>()
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


    EndMode2D();

    screen.Draw_Level(this->cam, true);

    // HUD zeichnen
    this->hud_ptr->Draw();

    std::string health_text = "HP: " + std::to_string(static_cast<int>(sp_mp->Get_Health()));
    DrawText(health_text.c_str(), 100, 95, 50, BLACK);
/*
    // Debugging-Hitboxen
    for (const auto& p_object : objectManager.managed_objects) {
        if (p_object != nullptr) {
            DrawRectangleLinesEx(p_object->Get_Hitbox(), 2.0f, RED);
        }
    }
    */
}