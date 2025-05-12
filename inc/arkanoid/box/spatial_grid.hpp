#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include <SFML/System.hpp>

namespace box::collision_detector
{

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept;
};

class SpatialGrid {
public:
    SpatialGrid(float cell_size);

    void clear();
    void insert(size_t particle_id, const sf::Vector2f& position);
    std::vector<std::pair<size_t, size_t>> potential_pairs() const;

private:
    std::pair<int, int> to_cell(const sf::Vector2f& position) const;

    float cell_size_;
    std::unordered_map<std::pair<int, int>, std::vector<size_t>, PairHash> cells_;
};

} // namespace box::collision_detector