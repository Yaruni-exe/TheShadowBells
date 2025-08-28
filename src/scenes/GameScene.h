#pragma once
#include <Scene.h>
#include "Screen.h"
#include "CollisionManager.h"
#include "../game/PlayerClassOne.h"
#include "DeltaTimeMachine.h"
#include "Cam.h"
#include "../game/EnemyBaseSpawner.h"
#include  "../game/Gunslinger.h"
#include "../game/UI.h"

namespace game::scenes
{
    class GameScene final : public game::core::Scene
    {private:
        Vector2 sp{390,500};
        Rectangle wb{0,0,game::Config::kStageWidth*2,game::Config::kStageHeight*2};
        Collision_Manager* p_cm =new Collision_Manager(wb,objectManager.managed_objects);
        //std::shared_ptr<Player_Class_One> sp_mp;
        std::shared_ptr<Gunslinger> sp_mp;
        DT::timemachine dtm;
        std::vector<enemy::Enemy_Base_Class*> enemy_list;
        float windowWidth;
        float windowHeight;

        std::shared_ptr<HUD> hud_ptr;

    public:
        GameScene();

        ~GameScene() override;

        void Update() override;

        void Draw() override;

        int Level_Nbr = 1;

        Screen screen {&Level_Nbr};

        std::shared_ptr<Cam> cam;

        Object_Manager objectManager;

    private:
        // Add private members here...
    };
}