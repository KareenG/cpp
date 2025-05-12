#pragma once

#include <SFML/Graphics.hpp>

namespace box
{

class Entity {
public:
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    virtual sf::Vector2f get_position() const;
    virtual void set_position(const sf::Vector2f& pos);

    virtual sf::Color get_color() const;
    virtual void set_color(sf::Color color);

    virtual bool is_fixed() const;
    virtual void set_fixed(bool fixed);

    virtual sf::Vector2f get_velocity() const = 0;
    virtual void set_velocity(const sf::Vector2f& v) = 0;

    virtual float get_radius() const = 0;

protected:
    sf::Vector2f position_;
    sf::Color color_;
    bool is_fixed_ = false;
    sf::Vector2f position_last_;
};
        
} // namespace box
