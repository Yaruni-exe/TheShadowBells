#pragma once
#include "Scene.h"
#include <string>
#include <raylib.h>
#include <memory>
#include <functional>

namespace game::scenes
{
    class MenuButton {
    public:
        Rectangle rect;
        Texture2D normal_texture;
        Texture2D hover_texture;
        std::function<void()> on_click;

        MenuButton(Rectangle r, const std::string& normal_path, const std::string& hover_path, std::function<void()> click_action);
        ~MenuButton();
        void Draw(Vector2 mouse_pos);
        bool IsHovered(Vector2 mouse_pos) const;
    };

    class MenuScene final : public game::core::Scene
    {
    public:
        MenuScene();
        ~MenuScene() override;

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