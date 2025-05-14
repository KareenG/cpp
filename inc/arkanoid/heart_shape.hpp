#pragma once

#include <SFML/Graphics.hpp>

namespace arkanoid
{

namespace scene
{

class Heart : public sf::Drawable, public sf::Transformable {
public:
    Heart(float size = 100.f, const sf::Color& color = sf::Color::Red);
    void setSize(float size);
    void setFillColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setOutlineColor(const sf::Color& color);
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
   
private:
    void create(float size, const sf::Color& color);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::ConvexShape shape_;
};
    
namespace HeartShape
{

// Draw multiple hearts in a row
void draw(sf::RenderTarget& target, sf::Vector2f start_position, size_t num_hearts, float size); 

} // namespace HeartShape

} // namespace scene
    
} // namespace arkanoid