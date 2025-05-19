#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "arkanoid/ui.hpp"

namespace arkanoid
{
    
class IOverlay {
public:
    virtual ~IOverlay() = default;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow&, const UI&) const = 0;
    virtual bool is_active() const = 0;
    virtual bool finished() const = 0;
};

} // namespace arkanoid

