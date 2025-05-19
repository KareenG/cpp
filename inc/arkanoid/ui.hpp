#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid {
class OverlayLayer;
class UI {
public:
    explicit UI(const std::string& font_path = consts::FontArial);
    
    const sf::Font& font() const;
    void draw_score(sf::RenderWindow& window, int score) const;
    void draw_lives(sf::RenderWindow& window, int lives) const;
    void draw_game_over(sf::RenderWindow& window) const;
    void draw_win(sf::RenderWindow& window) const;
    void draw_level(sf::RenderWindow& window, int level) const;
    void draw_centered_text(sf::RenderWindow& window, const std::string& text, sf::Color color, unsigned size = 32) const;
    
    void draw_centered_text(sf::RenderWindow& window, const std::string& text, sf::Color color, unsigned size, float center_y) const;
    
    void draw_overlay(sf::RenderWindow& window, OverlayType type) const;

    void draw_name_input(sf::RenderWindow& window, const std::string& prompt, const std::string& input, bool cursor_blink = true) const;

private:
    sf::Font font_;
};

} // namespace arkanoid
