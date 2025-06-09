#pragma once

#include <string>
#include <vector>

#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/level_data.hpp"

namespace arkanoid {

class LevelLoader {
public:
    // Loads from a given JSON file, throws on failure
    explicit LevelLoader(const std::string& filename = consts::LevelsFile);

    // Number of levels loaded
    size_t num_levels() const;

    // Get a specific level (0-based index)
    const LevelData& get_level(size_t idx) const;

private:
    std::vector<LevelData> levels_;
};

} // namespace arkanoid
