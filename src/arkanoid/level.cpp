#include <sstream>

#include "arkanoid/level.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid::level {

sf::Color get_color(char c, int row = 0) {
    auto it = consts::ColorMap.find(c);
    if (it != consts::ColorMap.end()) return it->second;
    static const std::vector<sf::Color> row_colors = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue,
        sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta
    };
    return row_colors[row % row_colors.size()];
}

std::vector<std::unique_ptr<Brick>> util::load_grid_from_pattern(
    const LevelData& level_dat,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size
)
{
    const auto& lines = level_dat.pattern_;
    int level_num = level_dat.level_num_;
    float padding_left = level_dat.padding_left_;
    float padding_right = level_dat.padding_right_;
    float padding_top = level_dat.padding_top_;
    float brick_height = level_dat.brick_height_;

    std::vector<std::unique_ptr<Brick>> bricks;
    int max_width = 0;
    int height = static_cast<int>(lines.size());
    for (const auto& line : lines)
        max_width = std::max(max_width, static_cast<int>(line.size()));

    const float brick_thickness = 1.0f;
    const float box_thickness = 2.0f;

    float usable_width = box_size.x - padding_left - padding_right - ((max_width + 1) * brick_thickness) - 2 * box_thickness;
    float brick_width = usable_width / max_width;
    float usable_height = box_size.y - padding_top - padding_top - (height * brick_thickness);
    float curr_brick_height = brick_height;
    if (height * brick_height > usable_height)
        curr_brick_height = usable_height / height;

    float start_x = box_left_top_boarders.x + padding_left + brick_thickness + (brick_width) / 2;
    float start_y = box_left_top_boarders.y + padding_top + brick_thickness + box_thickness + curr_brick_height / 2;

    for (int row = 0; row < height; ++row) {
        const std::string& current_line = lines[row];
        for (size_t col = 0; col < current_line.size(); ++col) {
            char c = current_line[col];
            if (c == ' ' || c == '.') continue;

            sf::Vector2f pos(
                start_x + col * (brick_width + brick_thickness),
                start_y + row * (curr_brick_height + 2 * brick_thickness)
            );
            sf::Vector2f size(brick_width, curr_brick_height);
            // Use level_num (from LevelData or pass as param if needed)
            bricks.push_back(brick_factory(c, size, pos, level_num));
        }
    }
    return bricks;
}

std::vector<std::unique_ptr<Brick>> load(
    const LevelData& level_dat,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size
)
{
    return util::load_grid_from_pattern(level_dat, box_left_top_boarders, box_size);
}

} // namespace arkanoid::level
