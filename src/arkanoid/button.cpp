#include "arkanoid/button.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid::scene {

Button::Button(const sf::Font& font, const std::string& label, unsigned int size, sf::Vector2f position)
: text_{font, "", 24}
, normal_color_(sf::Color::Black)
, hover_color_(consts::Orange)
{
    text_.setFont(font);
    text_.setString(label);
    text_.setCharacterSize(size);
    text_.setFillColor(normal_color_);

    sf::FloatRect bounds = text_.getLocalBounds();
    text_.setOrigin( {bounds.size.x / 2.f, bounds.size.y / 2.f} );
    text_.setPosition(position);
}

void Button::subscribe(std::function<void()> listener) {
    subscribers_.emplace_back(std::move(listener));
}

void Button::notify() const {
    for (const auto& callback : subscribers_) {
        callback();
    }
}

bool Button::is_mouse_over(const sf::RenderWindow& window) const {
    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return text_.getGlobalBounds().contains(mouse_pos);
}

void Button::handle_event(const sf::RenderWindow& window, const std::optional<sf::Event>& event) {
    if (is_mouse_over(window)) {
        text_.setFillColor(hover_color_);
        if (event->is<sf::Event::MouseButtonPressed>()) {
            const auto* mouse_event = event->getIf<sf::Event::MouseButtonPressed>();
            if (mouse_event && mouse_event->button == sf::Mouse::Button::Left) {
                notify();
            }
        }
    } else {
        text_.setFillColor(normal_color_);
    }
}

void Button::render(sf::RenderWindow& window) const {
    // Get text bounds
    auto bounds = text_.getLocalBounds();

    sf::Vector2f rect_size(bounds.size.x * 2, bounds.size.y * 2);

    // Rectangle origin & position
    sf::RectangleShape bg(rect_size);
    bg.setFillColor(sf::Color(255, 255, 255, 200)); // light white, mostly transparent

    // Match the text's centered origin/position
    sf::Vector2f text_center = text_.getPosition();
    bg.setOrigin( {rect_size.x / 2, rect_size.y / 3} );
    bg.setPosition(text_center);

    // Draw background then text
    window.draw(bg);
    window.draw(text_);
}


void Button::set_fill_color(sf::Color normal, sf::Color hover) {
    normal_color_ = normal;
    hover_color_ = hover;
}

void Button::set_text_color(sf::Color color) {
    text_.setFillColor(color);
}

} // namespace arkanoid::scene
