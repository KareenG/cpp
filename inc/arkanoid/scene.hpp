#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

namespace arkanoid {

namespace scene
{

enum class SceneEvent {
    None,
    QuitScene,      // Escape pressed
    // Pause
};

enum class SceneID {
    None,
    Opening,
    Game,
    Top10
};

using SceneChangeCallback = std::function<void(SceneID)>;

class Scene {
public:
    virtual ~Scene() = default;

    virtual SceneEvent handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event) = 0;
    virtual void update(float dt) = 0; //SceneResult
    virtual void render(sf::RenderWindow& window) const = 0;

    // Add subscriber
    void subscribe_to_scene_change(SceneChangeCallback cb) {
        on_scene_change_ = std::move(cb);
    }

    virtual SceneID get_next_scene() const { return SceneID::None; }  //// TODO - REMOVE

protected:
    // Child scene can emit transitions
    void notify_scene_change(SceneID id) const {
        if (on_scene_change_) {
            on_scene_change_(id);
        }
    }

private:
    SceneChangeCallback on_scene_change_;
};

} // namespace scene

} // namespace arkanoid
