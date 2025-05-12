#include "arkanoid/level.hpp"
#include <sstream>

namespace arkanoid::level {

static const std::unordered_map<char, sf::Color> color_map = {
    {'R', sf::Color::Red},
    {'G', sf::Color::Green},
    {'B', sf::Color::Blue},
    {'Y', sf::Color::Yellow},
    {'C', sf::Color::Cyan},
    {'M', sf::Color::Magenta},
    {'W', sf::Color::White}
};

sf::Color get_color(char c, int row = 0)
{
    auto it = color_map.find(c);
    if (it != color_map.end()) return it->second;

    // fallback: color by row if c is not mapped
    static const std::vector<sf::Color> row_colors = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue,
        sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta
    };
    return row_colors[row % row_colors.size()];
}

std::vector<Brick> load_pattern(const std::string& pattern, sf::Vector2f origin, sf::Vector2f brick_size, int level_num)
{
    (void)level_num;

    std::vector<Brick> bricks;
    std::istringstream ss(pattern);
    std::string line;
    int row = 0;

    while (std::getline(ss, line)) {
        for (size_t col = 0; col < line.size(); ++col) {
            char c = line[col];
            if (c == ' ' || c == '.') continue;

            sf::Vector2f pos = origin + sf::Vector2f(col * brick_size.x, row * brick_size.y);
            sf::Color color = get_color(c, row);
            bricks.emplace_back(brick_size, pos, color);
        }
        ++row;
    }
    return bricks;
}

std::vector<Brick> load_grid(int rows, int cols, sf::Vector2f origin, sf::Vector2f brick_size, float spacing, int level_num)
{
    (void)level_num;
    
    std::vector<Brick> bricks;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            sf::Vector2f pos = origin + sf::Vector2f(
                c * (brick_size.x + spacing),
                r * (brick_size.y + spacing)
            );
            sf::Color color = get_color('?', r); // fallback to color by row
            bricks.emplace_back(brick_size, pos, color);
        }
    }
    return bricks;
}

} // namespace arkanoid::level
