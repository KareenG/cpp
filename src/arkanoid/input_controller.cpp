#include "arkanoid/input_controller.hpp"

namespace arkanoid {

void InputController::bind_key(sf::Keyboard::Key key, std::function<void()> callback) {
    key_bindings_[key].emplace_back(std::move(callback));
    // Add to continuous keys if it's left/right
    if (key == sf::Keyboard::Key::Left || key == sf::Keyboard::Key::Right) {
        continuous_keys_[key] = false;
    }
}

void InputController::unbind_key(sf::Keyboard::Key key) {
    key_bindings_.erase(key);
    continuous_keys_.erase(key);
    key_pressed_status_.erase(key);
}

void InputController::clear() {
    key_bindings_.clear();
    continuous_keys_.clear();
    key_pressed_status_.clear();
}

void InputController::handle_event(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        sf::Keyboard::Key pressed_key = event.getIf<sf::Event::KeyPressed>()->code;
        if (!key_pressed_status_[pressed_key]) {
            auto it = key_bindings_.find(pressed_key);
            if (it != key_bindings_.end()) {
                for (auto& callback : it->second) {
                    callback();
                }
            }
        }
        key_pressed_status_[pressed_key] = true;
        if (continuous_keys_.find(pressed_key) != continuous_keys_.end()) {
            continuous_keys_[pressed_key] = true;
        }
    }
}

void InputController::handle_key_released(const sf::Event& event) {
    if (event.is<sf::Event::KeyReleased>()) {
        sf::Keyboard::Key released_key = event.getIf<sf::Event::KeyReleased>()->code;
        key_pressed_status_[released_key] = false;
        if (continuous_keys_.find(released_key) != continuous_keys_.end()) {
            continuous_keys_[released_key] = false;
        }
    }
}

void InputController::poll() {
    for (const auto& [key, is_active] : continuous_keys_) {
        if (is_active && sf::Keyboard::isKeyPressed(key)) {
            auto it = key_bindings_.find(key);
            if (it != key_bindings_.end()) {
                for (auto& callback : it->second) {
                    callback();
                }
            }
        }
    }
}

} // namespace arkanoid
