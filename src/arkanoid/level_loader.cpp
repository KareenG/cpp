#include "arkanoid/level_loader.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

namespace arkanoid {

LevelLoader::LevelLoader(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Cannot open level file: " + filename);
    }

    nlohmann::json j;
    in >> j;
    int i = 1;
    for (const auto& lvl : j.at("levels")) {
        LevelData level;
        level.pattern_ = lvl.at("pattern").get<std::vector<std::string>>();
        level.level_num_ = i++;
        level.padding_top_ = lvl.value("padding_top", 100.f);
        level.padding_left_ = lvl.value("padding_left", 40.f);
        level.padding_right_ = lvl.value("padding_right", 40.f);
        level.brick_height_ = lvl.value("brick_height", 30.f);
        levels_.push_back(std::move(level));
    }
}

size_t LevelLoader::num_levels() const {
    return levels_.size();
}

const LevelData& LevelLoader::get_level(size_t idx) const {
    if (idx >= levels_.size())
        throw std::out_of_range("Level index out of range");
    return levels_[idx];
}

} // namespace arkanoid
