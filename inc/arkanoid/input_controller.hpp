#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

namespace arkanoid
{
    
namespace input_controller {

/// Registers a callback to be invoked when a specific key is pressed.
void bind_key(sf::Keyboard::Key key, std::function<void()> callback);

/// Unbinds all callbacks for a given key.
void unbind_key(sf::Keyboard::Key key);

/// Clears all registered key bindings (e.g. when switching scenes).
void clear();

/// Dispatches the event to any registered key handlers.
/// Call this from scene::Scene::handle_events().
void handle_event(const sf::Event& event);

void handle_key_released(const sf::Event& event);

void poll();

} // namespace input_controller

} // namespace arkanoid
