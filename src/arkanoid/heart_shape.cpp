#include <math.h>

#include "arkanoid/heart_shape.hpp"

namespace arkanoid
{

Heart::Heart(float size, const sf::Color& color)
{
    create(size, color);
}

void Heart::setSize(float size)
{
    create(size, shape_.getFillColor());
}

void Heart::setFillColor(const sf::Color& color)
{
    shape_.setFillColor(color);
}

void Heart::setOutlineThickness(float thickness)
{
    shape_.setOutlineThickness(thickness);
}

void Heart::setOutlineColor(const sf::Color& color)
{
    shape_.setOutlineColor(color);
}

sf::FloatRect Heart::getLocalBounds() const
{
    return shape_.getLocalBounds();
}

sf::FloatRect Heart::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void Heart::create(float size, const sf::Color& color)
{
    // Generate points for the heart shape
    const int numPoints = 30;
    std::vector<sf::Vector2f> points;

    for (int i = 0; i < numPoints; ++i) {
        float t = i * 2.f * M_PI / numPoints;
        
        // Heart parametric equation
        float x = 16.f * std::pow(std::sin(t), 3);
        float y = 13.f * std::cos(t) - 5.f * std::cos(2.f * t) - 2.f * std::cos(3.f * t) - std::cos(4.f * t);
        
        // Scale and flip (the original equation produces an upside-down heart)
        x = x * size / 32.f;
        y = -y * size / 32.f;
        
        points.push_back(sf::Vector2f(x, y));
    }

    shape_.setPointCount(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        shape_.setPoint(i, points[i]);
    }

    shape_.setFillColor(color);
    shape_.setOrigin( {0, 0} );
}

void Heart::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(shape_, states);
}

void heart_shape::draw(sf::RenderTarget& target, sf::Vector2f start_position, size_t num_hearts, float size)
{
    if (num_hearts == 0 || size <= 0.f) return;

    const float padding = 2.f;

    for (size_t i = 0; i < num_hearts; ++i) {
        // scene::Heart heart(size, sf::Color::Red);
        Heart heart(size, sf::Color::Red);

        float x = start_position.x + i * (size + padding);
        float y = start_position.y;

        heart.setPosition({x, y});
        target.draw(heart);
    }
}

} // namespace arkanoid