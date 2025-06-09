#include <stdexcept>

#include "arkanoid/ui.hpp"
#include "arkanoid/heart_shape.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid {

UI::UI(const std::string& font_path)
: font_([&font_path]() {
    sf::Font f{};
    if (!f.openFromFile(font_path)) {
        throw std::runtime_error("Failed to load font from " + font_path);
    }
    return f;
    }())
{
}

void UI::draw_score(sf::RenderWindow& window, int score) const
{
    sf::Text score_text(font_, "Score: " + std::to_string(score), 24);
    sf::RectangleShape bg{{160.f, 20.f}};
    bg.setPosition( {8.f, 8.f} );
    bg.setFillColor(sf::Color::Black);
    window.draw(bg);
    window.draw(score_text);
}

void UI::draw_lives(sf::RenderWindow& window, int lives) const
{
    if(lives == 0) {
        return;
    }
    const float heart_size = 24.f;
    const float padding = 4.f;
    float total_width = heart_size * lives + padding * (lives - 1);

    float x_right = static_cast<float>(window.getSize().x) - 12.f;
    float x_start = x_right - total_width;
    float y_start = 14.f;//24.f;

    sf::Vector2f bg_size{total_width + 8.f, heart_size + 8.f};// 
    sf::Vector2f bg_position{x_start - 4.f, 0.f};//y_start - (bg_size.y - heart_size) / 2.f
    sf::RectangleShape heart_bg(bg_size);
    heart_bg.setPosition(bg_position);
    heart_bg.setFillColor(sf::Color::Black);
    window.draw(heart_bg);

    heart_shape::draw(window, {x_start + 18.f, y_start}, lives, heart_size); //
}

void UI::draw_game_over(sf::RenderWindow& window) const
{
    draw_centered_text(window, "Game Over", sf::Color::Red, 48);
}

void UI::draw_win(sf::RenderWindow& window) const
{
    draw_centered_text(window, "You Win", sf::Color::Green, 48);
}

void UI::draw_level(sf::RenderWindow& window, size_t level, size_t tot_levels) const
{
    sf::Text text{font_};
    text.setString("Round " + std::to_string(level) + '/' + std::to_string(tot_levels));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);
    // Center the text (adjust as needed)
    text.setOrigin( {text.getLocalBounds().size.x/2, text.getLocalBounds().size.y/2} );
    text.setPosition( {window.getSize().x/2.f, 12.f} );

    sf::RectangleShape bg({130.f, 20.f});
    bg.setPosition( {window.getSize().x/2.f - 65, 12.f} );
    bg.setFillColor(sf::Color::Black);
    window.draw(bg);
    window.draw(text);
}

void UI::draw_centered_text(sf::RenderWindow& window, const std::string& text, sf::Color color, unsigned size) const {
    sf::Text sf_text(font_, text, size);
    sf_text.setFillColor(color);
    auto bounds = sf_text.getLocalBounds();
    sf_text.setOrigin( {bounds.size.x / 2.f, bounds.size.y / 2.f} );
    sf_text.setPosition( {window.getSize().x / 2.f, window.getSize().y / 2.f} );
    window.draw(sf_text);
}

void UI::draw_centered_text(sf::RenderWindow& window, const std::string& text, sf::Color color, unsigned size, float center_y) const {
    sf::Text sf_text(font_, text, size);
    sf_text.setFillColor(color);
    auto bounds = sf_text.getLocalBounds();
    sf_text.setOrigin( {bounds.size.x / 2.f, bounds.size.y / 2.f} );
    sf_text.setPosition( {window.getSize().x / 2.f, center_y} );
    window.draw(sf_text);
}

void UI::draw_overlay(sf::RenderWindow& window, OverlayType type) const {
    sf::RectangleShape bg(sf::Vector2f(window.getSize()));
    bg.setFillColor(sf::Color(0, 0, 0, 192));
    window.draw(bg);

    switch (type) {
    case OverlayType::Win:
        draw_win(window);
        break;
    case OverlayType::GameOver:
        draw_game_over(window);
        break;
    case OverlayType::QuitConfirm:
        draw_centered_text(window, "Are you sure you want to quit the level?\nThe score will be lost.\n\n[Y]es / [N]o", sf::Color::Yellow, 34);
        break;
    default:
        break;
    }
}

void UI::draw_name_input(sf::RenderWindow& window, const std::string& prompt, const std::string& input, bool cursor_blink) const {
    sf::RectangleShape bg(sf::Vector2f(window.getSize()));
    bg.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(bg);

    std::string display_input = input;
    if (cursor_blink && (static_cast<int>(std::time(nullptr) * 2) % 2 == 0)) {
        display_input += '_';
    }
        
    float center_y = window.getSize().y / 2.f;
    draw_centered_text(window, prompt, sf::Color::Cyan, 30, center_y - 40.f);
    draw_centered_text(window, display_input, sf::Color::Yellow, 28, center_y + 60.f);
}

const sf::Font& UI::font() const
{ 
    return font_; 
}

void UI::draw_simple_text(sf::RenderWindow& window, const std::string& text, float x, float y, unsigned size, sf::Color color) const 
{
    sf::Text t(font_, text, size);
    t.setFillColor(color);
    t.setPosition( {x, y} );
    window.draw(t);
}

} // namespace arkanoid
