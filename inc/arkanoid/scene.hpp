#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid {

namespace scene
{

enum class SceneEvent {
    None,
    QuitScene,      // Escape pressed
    LaunchBall,     // Spacebar first press
    PauseToggle     // Spacebar toggle after launch
};

enum class SceneID {
    None,
    Opening,
    Game,
    Top10
};

class Scene {
public:
    virtual ~Scene() = default;

    virtual SceneEvent handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;

    virtual SceneID get_next_scene() const { return SceneID::None; }
};

} // namespace scene

} // namespace arkanoid
