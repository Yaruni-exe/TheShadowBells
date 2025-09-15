/*#pragma once
#include "Scene.h"
#include <memory>
#include <raylib.h>
#include "RepeatAnimation.h"

namespace game::scenes {
    class CarScene final : public game::core::Scene
    {
    public:
        CarScene();
        ~CarScene() override;

        void Update() override;
        void Draw() override;

    private:
        RepeatAnimation animation;

        // Timer für automatischen Szenenwechsel
        float timer = 0.0f;
        float transition_time = 5.0f; // Zeit in Sekunden bis Szenenwechsel
    };
}
*/