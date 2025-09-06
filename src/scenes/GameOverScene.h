#pragma once
#include "Scene.h"
#include <memory>
#include <raylib.h>

// Vorwärtsdeklaration der Game-Klasse
namespace game::core {
    class Game;
}

namespace game::scenes {
    class GameOverScene final : public game::core::Scene
    {
    public:
        GameOverScene(std::shared_ptr<game::core::Game> game);
        ~GameOverScene() override;

        void Update() override;
        void Draw() override;

    private:
        Texture2D background_texture;
        Texture2D return_button_texture_normal;
        Texture2D return_button_texture_hover;
        Rectangle return_button_rect;
        std::shared_ptr<game::core::Game> game_;
    };
}