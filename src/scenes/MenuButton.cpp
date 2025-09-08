#include "MenuButton.h"
#include <iostream> // For debugging output

namespace game::scenes {
    MenuButton::MenuButton(Rectangle r, const std::string& normal_path, const std::string& hover_path, std::function<void()> click_action)
        : rect(r), on_click(click_action) {

        // Load textures
        normal_texture = LoadTexture(normal_path.c_str());
        hover_texture = LoadTexture(hover_path.c_str());

        // --- START DEBUGGING ---
        if (normal_texture.id == 0) {
            std::cout << "DEBUG: FAILED to load normal texture from: " << normal_path << std::endl;
        } else {
            std::cout << "DEBUG: SUCCESSFULLY loaded normal texture from: " << normal_path << std::endl;
            std::cout << "DEBUG: Texture dimensions - Width: " << normal_texture.width << ", Height: " << normal_texture.height << std::endl;
        }

        if (hover_texture.id == 0) {
            std::cout << "DEBUG: FAILED to load hover texture from: " << hover_path << std::endl;
        } else {
            std::cout << "DEBUG: SUCCESSFULLY loaded hover texture from: " << hover_path << std::endl;
            std::cout << "DEBUG: Texture dimensions - Width: " << hover_texture.width << ", Height: " << hover_texture.height << std::endl;
        }
        // --- END DEBUGGING ---
    }

    MenuButton::~MenuButton() {
        UnloadTexture(normal_texture);
        UnloadTexture(hover_texture);
    }

    void MenuButton::Draw(Vector2 mouse_pos) {
        Texture2D current_texture; // Change to a local copy
        if (CheckCollisionPointRec(mouse_pos, this->rect)) {
            current_texture = this->hover_texture;
        } else {
            current_texture = this->normal_texture;
        }

        // Add a check before drawing to prevent crashes and ensure texture is valid
        if (current_texture.id > 0) {
            Rectangle source_rec = {0.0f, 0.0f, (float)current_texture.width, (float)current_texture.height};
            Vector2 origin = {0.0f, 0.0f};
            DrawTexturePro(current_texture, source_rec, this->rect, origin, 0.0f, WHITE);
        } else {
            // Draw a red rectangle as a visible placeholder if the texture is invalid
            DrawRectangleRec(this->rect, RED);
        }
    }

    bool MenuButton::IsHovered(Vector2 mouse_pos) const {
        return CheckCollisionPointRec(mouse_pos, this->rect);
    }
}