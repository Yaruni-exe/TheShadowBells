#include "Level1Scene.h"

#include <CarScene.h>
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
#include "../game/spawner/Level1Spawner.h"
#include "../game/spawner/Level2Spawner.h"
#include "../config_enemys.h.in"
#include "../game/interactables/Generator.h"
#include "../game/interactables/GeneratorDoor.h"
#include "../game/PlayerClassOne.h"
#include "../core/CollisionManager.h"
#include "../game/EnemyExtendedBaseClass.h"
#include "LevelTransition.h"
#include "Cutscene.h"
#include "Level2Scene.h"


using namespace std::string_literals;

game::scenes::Level1Scene::Level1Scene()
: p_cm(wb, objectManager.managed_objects) {
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
    Rectangle spawner_area_1 = { 936, 200, 48, 48 };
    auto spawner_1 = std::make_shared<Level1_Spawner>(
        spawner_area_1,
        objectManager,
        enemy_List,
        sp_mp,
        1,
        16.0f
    );
    objectManager.AddObject(spawner_1);

    // ZWEITER SPAWNER
    Rectangle spawner_area_2 = { 936, 672, 48, 36 };
    auto spawner_2 = std::make_shared<Level1_Spawner>(
        spawner_area_2,
        objectManager,
        enemy_List,
        sp_mp,
        1,
        16.0f
    );
    objectManager.AddObject(spawner_2);


    // Dritter SPAWNER
    Rectangle spawner_area_3 = { 960, 360, 32, 48 };
    auto spawner_3 = std::make_shared<Level1_Spawner>(
        spawner_area_3,
        objectManager,
           enemy_List,
           sp_mp,
           2,
           8.0f
       );
    objectManager.AddObject(spawner_3);

    // Vierter SPAWNER
    Rectangle spawner_area_4 = { 960, 520, 32, 48 };
    auto spawner_4 = std::make_shared<Level1_Spawner>(
        spawner_area_4,
        objectManager,
           enemy_List,
           sp_mp,
           2,
           8.0f
       );

    objectManager.AddObject(spawner_4);

    // Fuenfter SPAWNER
    Rectangle spawner_area_5 = { 1192, 200, 48, 48 };
    auto spawner_5 = std::make_shared<Level1_Spawner>(
        spawner_area_5,
        objectManager,
           enemy_List,
           sp_mp,
           2,
           8.0f
       );

    objectManager.AddObject(spawner_5);

    // Sechster SPAWNER
    Rectangle spawner_area_6 = { 1192, 672, 48, 36 };
    auto spawner_6 = std::make_shared<Level1_Spawner>(
        spawner_area_6,
        objectManager,
           enemy_List,
           sp_mp,
           2,
           8.0f
       );

    objectManager.AddObject(spawner_6);

    // Siebter SPAWNER
    Rectangle spawner_area_7 = { 2480, 288, 48, 96 };
    auto spawner_7 = std::make_shared<Level1_Spawner>(
        spawner_area_7,
        objectManager,
           enemy_List,
           sp_mp,
           3,
           8.0f
       );

    objectManager.AddObject(spawner_7);

    // Achter SPAWNER
    Rectangle spawner_area_8 = { 2592, 472, 96, 48 };
    auto spawner_8 = std::make_shared<Level1_Spawner>(
        spawner_area_8,
        objectManager,
           enemy_List,
           sp_mp,
           3,
           8.0f
       );

    objectManager.AddObject(spawner_8);

    // Neunter SPAWNER
    Rectangle spawner_area_9 = { 2784, 256, 36, 64 };
    auto spawner_9 = std::make_shared<Level1_Spawner>(
        spawner_area_9,
        objectManager,
           enemy_List,
           sp_mp,
           2,
           16.0f
       );

    objectManager.AddObject(spawner_9);

    // Zehnter SPAWNER
    Rectangle spawner_area_10 = { 2816, 380, 64, 36 };
    auto spawner_10 = std::make_shared<Level1_Spawner>(
        spawner_area_10,
        objectManager,
           enemy_List,
           sp_mp,
           2,
           16.0f
       );

    objectManager.AddObject(spawner_10);

    //  MÜNZEN ERSTELLT
    objectManager.AddObject(std::make_shared<Credit>(Vector2{420, 260}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{420, 644}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1040, 356}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1040, 548}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1648, 468}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1952, 324}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{1985, 672}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2307, 326}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2307, 547}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2438, 450}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2438, 482}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2690, 230}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2822, 646}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2948, 230}, 200));
    objectManager.AddObject(std::make_shared<Credit>(Vector2{2978, 262}, 200));

    // BOMBEN UND BOMBENWÄNDE ERSTELLEN

    Bomb_Pickup::Load_Texture();
    Bomb_Wall::Load_Destroy_Texture();   // nur noch die Zerstörungs-Animation statisch

   // Hinzufügen einer Bomb Wall
    objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{975, 324},
    Vector2{96, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_3Tiles.png",
    Vector2{0, 0}
));


    // Hinzufügen eines Bomben-Pickups in der Nähe der Wand
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{576, 220}));


    objectManager.AddObject(std::make_shared<Bomb_Wall>(
        Vector2{1167, 324},                    // Position
        Vector2{96, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_3Tiles.png",
    Vector2{0, 0}                         // Offset
        ));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{975, 584},
    Vector2{96, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_3Tiles.png",
    Vector2{0, 0}
));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{1167, 584},
    Vector2{96, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_3Tiles.png",
    Vector2{0, 0}
));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{2368, 400},
    Vector2{64, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_2Tiles.png",
    Vector2{0, 0}
));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{2496, 504},
    Vector2{64, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_2Tiles.png",
    Vector2{0, 0}
));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{2656, 294},
    Vector2{64, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_2Tiles.png",
    Vector2{0, 0}
));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{2656, 392},
    Vector2{64, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_2Tiles.png",
    Vector2{0, 0}
));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{2720, 504},
    Vector2{64, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_2Tiles.png",
    Vector2{0, 0}
));

objectManager.AddObject(std::make_shared<Bomb_Wall>(
    Vector2{2912, 504},
    Vector2{96, 20},
    "assets/graphics/Items/BombWall/Wand_Sprengstoff_Wald_Sprite_Horizontal_3Tiles.png",
    Vector2{0, 0}
));


    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{576, 656}));
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{968, 448}));
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{2084, 416}));
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{2084, 480}));
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{2820, 464}));
    objectManager.AddObject(std::make_shared<Bomb_Pickup>(Vector2{2980, 228}));


    // Medipack erstellen
    objectManager.AddObject(std::make_shared<Medipack>(Vector2{1120, 448}, 40.0f));
    objectManager.AddObject(std::make_shared<Medipack>(Vector2{2568, 340}, 40.0f));

    // Hinzufügen der Level-Übergangs-Hitbox
    Rectangle level_transition_hitbox = { 2912.0f, 640.0f, 96.0f, 32.0f };
    objectManager.AddObject(std::make_shared<LevelTransition>(
        level_transition_hitbox,
        // Diese Lambda-Funktion ruft einfach die VideoScene auf, ohne den Pfad zu kennen.
[]() {
    game::core::Store::stage->SwitchToNewScene(
        "level2"s,
        //std::make_unique<game::scenes::Level2Scene>()
        std::make_unique<game::scenes::Cutscene>()
    );
}
));
}



game::scenes::Level1Scene::~Level1Scene()
{
}

void game::scenes::Level1Scene::Update()
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

void game::scenes::Level1Scene::Draw()
{
    ClearBackground(WHITE);
    screen.Draw_Level(this->cam, false);

    BeginMode2D(cam->cam);

    // Objekte zeichnen
    for (int i = 0; i < objectManager.managed_objects.size(); ++i) {
        objectManager.managed_objects[i]->Draw();
    }

/*
    // Hitboxen anzeigen
    for (const auto& p_object : objectManager.managed_objects) {
        if (p_object != nullptr) {
            DrawRectangleLinesEx(p_object->Get_Hitbox(), 2.0f, RED);
        }
    }
*/

    EndMode2D();

    screen.Draw_Level(this->cam, true);

    // HUD zeichnen
      this->hud_ptr->Draw();



   /* std::string health_text = "HP: " + std::to_string(static_cast<int>(sp_mp->Get_Health()));
    DrawText(health_text.c_str(), 100, 95, 50, BLACK);
    */

/*
    // Minimap
    for (const auto& p_object : objectManager.managed_objects) {
        if (p_object != nullptr) {
            DrawRectangleLinesEx(p_object->Get_Hitbox(), 2.0f, RED);
        }
    }
*/

}