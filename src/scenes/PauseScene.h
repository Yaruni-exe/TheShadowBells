#pragma once
#include "Scene.h"
#include <memory>
#include <functional>
#include <raylib.h>
#include "MenuScene.h" // Stellt MenuButton bereit

namespace game::scenes
{
    class PauseScene final : public game::core::Scene
    {
    public:
        PauseScene();
        ~PauseScene() override;

        void Update() override;
        void Draw() override;

    private:
        std::unique_ptr<MenuButton> continue_button;
        std::unique_ptr<MenuButton> menu_button;
    };
}