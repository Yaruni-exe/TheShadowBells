#pragma once
#include "Scene.h"
#include <memory>
#include <functional>
#include <raylib.h>
#include "MenuButton.h"

namespace game::scenes
{
    class PauseScene final : public game::core::Scene
    {
    public:
        // Neuer Konstruktor mit Übergabe des Szenen-Namens
        PauseScene(const std::string& pausedSceneName); // Neuer Konstruktor
        ~PauseScene() override;

        void Update() override;
        void Draw() override;

    private:
        std::unique_ptr<MenuButton> continue_button;
        std::unique_ptr<MenuButton> menu_button;
        Texture2D background_texture;

        std::string paused_scene_name; // <-- neue Variable
    };
}
