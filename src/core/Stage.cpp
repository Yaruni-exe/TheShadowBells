#include <memory>
#include <map>
#include "Stage.h"
#include "Renderer.h"


game::core::Stage::Stage(const std::string& new_Scene_Name, std::unique_ptr<game::core::Scene> scene)
{
    this->next_Scene_ = std::move(scene);
    this->scenes_.insert(std::make_pair(new_Scene_Name, this->next_Scene_));
}

void game::core::Stage::SwitchToScene(const std::string& new_Scene_Name)
{
    auto it = this->scenes_.find(new_Scene_Name);
    if(it != this->scenes_.end())
        this->next_Scene_ = it->second;
}

void game::core::Stage::SwitchToNewScene(const std::string &new_Scene_Name, std::shared_ptr<game::core::Scene> scene)
{
    this->next_Scene_ = std::move(scene);
    this->scenes_.insert(std::make_pair(new_Scene_Name, this->next_Scene_));
}

void game::core::Stage::ReplaceWithNewScene(const std::string& old_Scene_Name,
    const std::string& new_Scene_Name, std::shared_ptr<game::core::Scene> scene)
{
    this->next_Scene_ = std::move(scene);
    this->next_scene_name_ = new_Scene_Name;
    this->old_scene_to_replace_ = old_Scene_Name;
}

void game::core::Stage::ReplaceWithExistingScene(const std::string &old_Scene_Name, const std::string &new_Scene_Name)
{
    auto it = this->scenes_.find(new_Scene_Name);

    if(it != this->scenes_.end())
    {
        this->scenes_.erase(old_Scene_Name);
        this->next_Scene_ = it->second;
    }
}

const std::shared_ptr<game::core::Scene> &game::core::Stage::Scene() const
{
    return this->scene_;
}

const std::map<std::string, std::shared_ptr<game::core::Scene>> &game::core::Stage::Scenes() const
{
    return this->scenes_;
}

void game::core::Stage::ClearAllScenes()
{
    this->scenes_.clear();
    this->scene_ = nullptr;
    this->next_Scene_ = nullptr;
}

void game::core::Stage::Update()
{
    // Verarbeite die Anfragen
    if (this->next_Scene_ || !this->next_scene_name_.empty())
    {
        // Lösche die alte Szene, wenn eine Ersetzungs-Anfrage vorliegt
        if (!this->old_scene_to_replace_.empty()) {
            this->scenes_.erase(this->old_scene_to_replace_);
            this->old_scene_to_replace_ = "";
        }

        // Lösche eine Szene, wenn eine "existierende Szene"-Anfrage vorliegt
        if (!this->old_scene_to_erase_.empty()) {
            this->scenes_.erase(this->old_scene_to_erase_);
            this->old_scene_to_erase_ = "";
        }

        // Wechsle zu einer existierenden Szene
        if (this->next_Scene_ == nullptr && !this->next_scene_name_.empty()) {
            auto it = this->scenes_.find(this->next_scene_name_);
            if(it != this->scenes_.end()) {
                this->scene_ = it->second;
            } else {
                // Szenenname existiert nicht, setze auf nullptr, um Absturz zu vermeiden
                this->scene_ = nullptr;
            }
        }
        // Wechsle zu einer neuen Szene
        else if (this->next_Scene_ != nullptr) {
            this->scene_ = std::move(this->next_Scene_);
            this->scenes_.insert(std::make_pair(this->next_scene_name_, this->scene_));
        }

        this->next_scene_name_ = "";
    }

    // Führe die Aktualisierung der Szene nur aus, wenn der Zeiger gültig ist
    if(this->scene_) {
        this->scene_->Update();
    }
}

void game::core::Stage::Draw()
{
    ClearBackground(WHITE);

    // Zeichne nur, wenn der Zeiger gültig ist
    if (this->scene_) {
        for (auto const& [key, val] : this->scene_->actors)
        {
            val->sprite()->Update();

            if(val->sprite()->visible)
                game::core::Renderer::DrawTexture(val->sprite());
        }

        this->scene_->Draw();
    }
}
