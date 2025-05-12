#pragma once

#include <vector>
#include <string>
#include "arkanoid/brick.hpp"

namespace arkanoid::level {

// Load from string pattern (e.g. "RRRRR\nGGGGG\nBBBBB")
std::vector<Brick> load_pattern(const std::string& pattern, sf::Vector2f origin, sf::Vector2f brick_size, int level_num = 1);

// Generate rows × cols procedurally, with spacing (0 = tight grid)
std::vector<Brick> load_grid(int rows, int cols, sf::Vector2f origin, sf::Vector2f brick_size, float spacing = 0.f, int level_num = 1);

} // namespace arkanoid::level
