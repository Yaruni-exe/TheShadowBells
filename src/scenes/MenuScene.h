#pragma once

#include "Scene.h"
#include <raylib.h>
#include <memory>
#include "MenuButton.h" // Jetzt wird die separate Header-Datei inkludiert

namespace game::scenes {
    class MenuScene : public game::core::Scene {
    public:
        MenuScene();
        ~MenuScene();

        void Update() override;
        void Draw() override;

    private:
        Texture2D background_texture;
        std::unique_ptr<MenuButton> start_button;
        std::unique_ptr<MenuButton> controls_button;
        std::unique_ptr<MenuButton> credits_button;
        std::unique_ptr<MenuButton> exit_button;
    };
}