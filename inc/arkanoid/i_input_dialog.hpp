#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "arkanoid/ui.hpp"

namespace arkanoid
{
    
class IInputDialog {
public:
    virtual ~IInputDialog() = default;
    virtual void show(const std::string& prompt, std::function<void(const std::string&)>) = 0;
    virtual void handle_text(uint32_t unicode) = 0;
    virtual void handle_key(sf::Keyboard::Key key) = 0;
    virtual void reset() = 0;
    virtual const std::string& input() const = 0;
    virtual const std::string& prompt() const = 0;
};

} // namespace arkanoid

