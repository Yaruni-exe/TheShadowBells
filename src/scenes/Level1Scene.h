//
// Created by Teilnehmer on 15.08.2025.
//

#ifndef LEVEL1SCENE_H
#define LEVEL1SCENE_H

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
    class Level1Scene final : public game::core::Scene
    {private:
        Vector2 sp{358,468};
        Rectangle wb{0,0,game::Config::kStageWidth*2,game::Config::kStageHeight*2};
       // Collision_Manager* p_cm =new Collision_Manager(wb,objectManager.managed_objects);
        Collision_Manager p_cm;
        //std::shared_ptr<Player_Class_One> sp_mp;
        std::shared_ptr<Gunslinger> sp_mp;
        DT::timemachine dtm;
        std::vector<enemy::Enemy_Base_Class*> enemy_list;
        float windowWidth;
        float windowHeight;

        std::shared_ptr<HUD> hud_ptr;



    public:
        Level1Scene();

        ~Level1Scene() override;

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

#endif //LEVEL1SCENE_H
