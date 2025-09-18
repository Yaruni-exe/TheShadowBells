//
// Created by Teilnehmer on 15.08.2025.
//

#ifndef LEVEL2SCENE_H
#define LEVEL2SCENE_H

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
#include "../core/Object_Manager.h"

namespace game::scenes
{
    class Level2Scene final : public game::core::Scene
    {private:
        Vector2 sp{1030,1056};
        Rectangle wb{0,0,game::Config::kStageWidth*2,game::Config::kStageHeight*2};
        Collision_Manager p_cm;
        std::shared_ptr<Gunslinger> sp_mp;
        DT::timemachine dtm;
        std::vector<enemy::Enemy_Base_Class*> enemy_list;
        float windowWidth;
        float windowHeight;



        std::shared_ptr<HUD> hud_ptr;



    public:
        Level2Scene();

        ~Level2Scene() override;

        void Update() override;

        void Draw() override;

        int Level_Nbr = 2;

        Screen screen {&Level_Nbr};

        std::shared_ptr<Cam> cam;

        Object_Manager objectManager;

    private:
        // Add private members here...
    };
}

#endif //LEVEL2SCENE_H