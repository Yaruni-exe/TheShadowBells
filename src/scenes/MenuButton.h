#pragma once

#include <string>
#include <functional>
#include <raylib.h>

namespace game::scenes {
    class MenuButton {
    public:
        Rectangle rect;
        std::function<void()> on_click;

        MenuButton(Rectangle r, const std::string& normal_path, const std::string& hover_path, std::function<void()> click_action);
        ~MenuButton();

        void Draw(Vector2 mouse_pos);
        bool IsHovered(Vector2 mouse_pos) const;

    private:
        Texture2D normal_texture;
        Texture2D hover_texture;
    };
}