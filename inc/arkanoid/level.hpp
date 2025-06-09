#pragma once

#include <vector>
#include <string>
#include "arkanoid/brick.hpp"
#include "arkanoid/standard_brick.hpp"
#include "arkanoid/indestructible_brick.hpp"
#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/level_data.hpp"

namespace arkanoid::level {

namespace util {

inline auto brick_factory = [](char c, const sf::Vector2f& size, const sf::Vector2f& pos, int level) -> std::unique_ptr<arkanoid::Brick> {

    // Get color
    auto color_it = consts::ColorMap.find(c);
    sf::Color color = (color_it != consts::ColorMap.end()) ? color_it->second : sf::Color::White;

    // Indestructible
    if (c == 'Y') {
        return std::make_unique<IndestructibleBrick>(size, pos, color);
    }
    // Dynamic/gray: score depends on level
    if (c == 'D') {
        int score = 50 * level;
        return std::make_unique<StandardBrick>(size, pos, color, score);
    }

    // Normal: use CharToScore or fallback
    int score = consts::GrayBrickBaseScore;
    auto score_it = consts::BrickCharToScore .find(c);
    if (score_it != consts::BrickCharToScore .end()) {
        score = score_it->second;
    }
    return std::make_unique<StandardBrick>(size, pos, color, score);
};

std::vector<std::unique_ptr<Brick>> load_grid_from_pattern(
    const LevelData& level_dat,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size
);

} // namespace util

std::vector<std::unique_ptr<Brick>> load(
    const LevelData& level_dat,
    sf::Vector2f box_left_top_boarders,
    sf::Vector2f box_size
);

} // namespace arkanoid::level
