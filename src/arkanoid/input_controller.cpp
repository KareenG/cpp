#include "arkanoid/input_controller.hpp"
#include <unordered_map>
#include <vector>

namespace arkanoid {
namespace input_controller {

// Maps keys to their callback functions
static std::unordered_map<sf::Keyboard::Key, std::vector<std::function<void()>>> key_bindings;

// Tracks which keys should have continuous behavior (like movement keys)
static std::unordered_map<sf::Keyboard::Key, bool> continuous_keys = {
    {sf::Keyboard::Key::Left, false},
    {sf::Keyboard::Key::Right, false}
};

// Keys that have been pressed and not yet released
static std::unordered_map<sf::Keyboard::Key, bool> key_pressed_status;

void bind_key(sf::Keyboard::Key key, std::function<void()> callback) {
    key_bindings[key].emplace_back(std::move(callback));
    
    // If it's a movement key, add it to continuous keys if not already there
    if (key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right) {
        continuous_keys[key] = false;
    }
}

void unbind_key(sf::Keyboard::Key key) {
    key_bindings.erase(key);
    continuous_keys.erase(key);
    key_pressed_status.erase(key);
}

void clear() {
    key_bindings.clear();
    continuous_keys.clear();
    key_pressed_status.clear();
}

void handle_event(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        sf::Keyboard::Key pressed_key = event.getIf<sf::Event::KeyPressed>()->code;
        
        // Only trigger callbacks if the key wasn't already being held down
        if (!key_pressed_status[pressed_key]) {
            auto it = key_bindings.find(pressed_key);
            if (it != key_bindings.end()) {
                for (auto& callback : it->second) {
                    callback(); // Execute the callback
                }
            }
        }
        
        // Mark key as pressed
        key_pressed_status[pressed_key] = true;
        
        // If this is a continuous key, set its flag
        if (continuous_keys.find(pressed_key) != continuous_keys.end()) {
            continuous_keys[pressed_key] = true;
        }
    }
}

void handle_key_released(const sf::Event& event) {
    if (event.is<sf::Event::KeyReleased>()) {
        sf::Keyboard::Key released_key = event.getIf<sf::Event::KeyReleased>()->code;
        
        // Mark key as released
        key_pressed_status[released_key] = false;
        
        // If this is a continuous key, reset its flag
        if (continuous_keys.find(released_key) != continuous_keys.end()) {
            continuous_keys[released_key] = false;
        }
    }
}

void poll() {
    // Check all continuous keys and execute their callbacks if pressed
    for (const auto& [key, is_active] : continuous_keys) {
        if (is_active && sf::Keyboard::isKeyPressed(key)) {
            auto it = key_bindings.find(key);
            if (it != key_bindings.end()) {
                for (auto& callback : it->second) {
                    callback(); // Execute the callback continuously
                }
            }
        }
    }
}

} // namespace input_controller
} // namespace arkanoid
