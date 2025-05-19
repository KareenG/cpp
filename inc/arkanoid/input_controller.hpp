#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

namespace arkanoid {

class InputController {
public:
    /// Registers a callback to be invoked when a specific key is pressed.
    void bind_key(sf::Keyboard::Key key, std::function<void()> callback);

    /// Unbinds all callbacks for a given key.
    void unbind_key(sf::Keyboard::Key key);

    /// Clears all registered key bindings (e.g. when switching scenes).
    void clear();

    /// Dispatches the event to any registered key handlers.
    /// Call this from scene::Scene::handle_events().
    void handle_event(const sf::Event& event);

    /// Handles key released events.
    void handle_key_released(const sf::Event& event);

    /// Polls for continuous key actions (e.g. holding down arrow keys).
    void poll();

private:
    std::unordered_map<sf::Keyboard::Key, std::vector<std::function<void()>>> key_bindings_;
    std::unordered_map<sf::Keyboard::Key, bool> continuous_keys_;
    std::unordered_map<sf::Keyboard::Key, bool> key_pressed_status_;
};

} // namespace arkanoid
