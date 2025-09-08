
/*

#ifndef CUTSCENE_H
#define CUTSCENE_H

#pragma once

#include "Scene.h"
#include <raylib.h>
#include <memory>
#include <string>
#include <rvideo.h>

namespace game::scenes {
    class Cutscene : public game::core::Scene {
    public:
        Cutscene();
        ~Cutscene();

        void Update() override;
        void Draw() override;

    private:
        Video video_player;
        bool is_video_ready = false;
        bool has_played_once = false;
    };
}

#endif // CUTSCENE_H

*/