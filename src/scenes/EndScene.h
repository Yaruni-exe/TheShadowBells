#pragma once
#include "Scene.h"
#include <memory>
#include <raylib.h>
#include "RepeatAnimation.h"
#include "MenuButton.h"

namespace game::scenes {
    class EndScene final : public game::core::Scene
    {
    public:
        EndScene();
        ~EndScene() override;

        void Update() override;
        void Draw() override;

    private:
        RepeatAnimation animation;
        std::unique_ptr<MenuButton> return_button;
    };
}
