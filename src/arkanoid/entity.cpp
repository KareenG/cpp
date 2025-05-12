#include "arkanoid/entity.hpp"

namespace arkanoid
{

sf::Vector2f Entity::get_position() const
{ 
    return position_;
}
void Entity::set_position(const sf::Vector2f& pos)
{ 
    position_ = pos;
}
sf::Color Entity::get_color() const
{ 
    return color_;
}
void Entity::set_color(sf::Color const& color)
{ 
    color_ = std::move(color);
}
bool Entity::is_fixed() const
{ 
    return is_fixed_;
}
void Entity::set_fixed(bool fixed)
{ 
    is_fixed_ = fixed;
}

} // namespace arkanoid