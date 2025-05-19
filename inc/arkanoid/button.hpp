#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <optional>

namespace arkanoid::scene {

class Button {
public:
    Button(const sf::Font& font, const std::string& label, unsigned int size, sf::Vector2f position);

    // Subscribe to click event
    void subscribe(std::function<void()> listener);

    // Handle hover + click detection
    void handle_event(const sf::RenderWindow& window, const std::optional<sf::Event>& event);

    void render(sf::RenderWindow& window) const;

    void set_fill_color(sf::Color normal, sf::Color hover);
    void set_text_color(sf::Color color);

private:
    sf::Text text_;
    sf::Color normal_color_;
    sf::Color hover_color_;

    std::vector<std::function<void()>> subscribers_;

    bool is_mouse_over(const sf::RenderWindow& window) const;
    void notify() const;
};

} // namespace arkanoid::scene
