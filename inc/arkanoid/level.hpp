#pragma once

#include <vector>
#include <string>
#include "arkanoid/brick.hpp"

namespace arkanoid::level {

namespace util {

std::vector<std::unique_ptr<Brick>> load_grid(int level_num,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size,
    float padding_left,
    float padding_right,
    float padding_top,
    float brick_height);

std::vector<std::unique_ptr<Brick>> load_level_pattern_with_spaces(int level_num,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size,
    float padding_left,
    float padding_right,
    float padding_top,
    float brick_height
);

} // namespace util

std::vector<std::unique_ptr<Brick>> load(
    int level_num,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size,
    float padding_left,
    float padding_right,
    float padding_top,
    float brick_height);

} // namespace arkanoid::level
