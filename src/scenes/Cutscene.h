#ifndef CUTSCENE_H
#define CUTSCENE_H

#pragma once

#include "Scene.h"
#include <raylib.h>
#include <memory>
#include <string>

namespace game::scenes {
    class Cutscene : public game::core::Scene {
    public:
        Cutscene();
        ~Cutscene();

        void Update() override;
        void Draw() override;

    private:
        Texture2D spritesheet{};
        bool is_ready = false;

        int frameWidth;
        int frameHeight;
        int totalFrames;
        int currentFrame = 0;

        float fps;       // Animationsgeschwindigkeit
        float playTime;  // Abspielzeit
        float duration;  // Gesamtdauer bis Szenenwechsel
    };
}

#endif // CUTSCENE_H
