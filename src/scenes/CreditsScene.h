

#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#pragma once

#include "Scene.h"
#include <raylib.h>
#include <memory>
#include "MenuButton.h" // Die korrekte Header-Datei
#include "MenuScene.h"
#include <functional>
#include <string>

namespace game::scenes {
    class CreditsScene : public game::core::Scene {
    public:
        CreditsScene();
        ~CreditsScene();

        void Update() override;
        void Draw() override;

    private:
        Texture2D background_texture;
        std::unique_ptr<MenuButton> back_button;
    };
}

#endif //CREDITSSCENE_H
