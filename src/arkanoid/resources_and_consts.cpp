#include "arkanoid/resources_and_consts.hpp"

#include <stdexcept>

namespace arkanoid::resources {

static std::unordered_map<std::string, sf::Font> font_cache;
static std::unordered_map<std::string, sf::Texture> texture_cache;

const sf::Font& get_font(const std::string& path)
{
    auto it = font_cache.find(path);
    if (it != font_cache.end()) {
        return it->second;
    }

    sf::Font font;
    if (!font.openFromFile(path)) {
        throw std::runtime_error("Failed to load font from: " + path);
    }

    font_cache[path] = std::move(font);
    return font_cache.at(path);
}

const sf::Texture& get_texture(const std::string& path)
{
    auto it = texture_cache.find(path);
    if (it != texture_cache.end()) {
        return it->second;
    }

    sf::Texture tex;
    if (!tex.loadFromFile(path)) {
        throw std::runtime_error("Failed to load texture from: " + path);
    }

    texture_cache[path] = std::move(tex);
    return texture_cache.at(path);
}

void clear()
{
    font_cache.clear();
    texture_cache.clear();
}

} // namespace arkanoid::resources
