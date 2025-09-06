/*

#include "Cutscene.h"
#include <Store.h>
#include "Level2Scene.h"


using namespace std::string_literals;

namespace game::scenes {
    Cutscene::Cutscene() {
        std::string video_path = "assets/videos/mein_video.mp4";
        TraceLog(LOG_INFO, "Lade Video von: %s", video_path.c_str());
        video_player = LoadVideo(video_path.c_str());
        if (video_player.frameCount > 0) {
            is_video_ready = true;
            PlayVideo(video_player);
        } else {
            TraceLog(LOG_WARNING, "Video konnte nicht geladen werden.");
            is_video_ready = false;
        }
    }

    Cutscene::~Cutscene() {
        if (is_video_ready) {
            UnloadVideo(video_player);
        }
    }

    void Cutscene::Update() {
        if (!is_video_ready) {
            game::core::Store::stage->SwitchToNewScene("level2"s, std::make_unique<Level2Scene>());
            return;
        }

        UpdateVideo(video_player);
        if (GetFrameTime() > 0.0f) {
            has_played_once = true;
        }
        
        if (has_played_once && GetVideoTime(video_player) >= GetVideoLength(video_player) - GetFrameTime()) {
            TraceLog(LOG_INFO, "Video beendet, wechsle zu Level 2.");
            game::core::Store::stage->SwitchToNewScene("level2"s, std::make_unique<Level2Scene>());
        }

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            game::core::Store::stage->SwitchToNewScene("level2"s, std::make_unique<Level2Scene>());
        }
    }

    void Cutscene::Draw() {
        ClearBackground(BLACK);
        if (is_video_ready) {
            Texture2D video_frame = GetVideoTexture(video_player);
            if (video_frame.id > 0) {
                DrawTexturePro(
                    video_frame,
                    { 0, 0, (float)video_frame.width, (float)video_frame.height },
                    { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
                    { 0, 0 }, 0.0f, WHITE
                );
            }
        }
    }
}


 */