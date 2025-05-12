#include "arkanoid/box/spatial_grid.hpp"
#include <cmath>

namespace box::collision_detector
{

SpatialGrid::SpatialGrid(float cell_size)
    : cell_size_(cell_size)
{
}

void SpatialGrid::clear()
{
    cells_.clear();
}

std::pair<int, int> SpatialGrid::to_cell(const sf::Vector2f& position) const
{
    return {
        static_cast<int>(std::floor(position.x / cell_size_)),
        static_cast<int>(std::floor(position.y / cell_size_))
    };
}

void SpatialGrid::insert(size_t particle_id, const sf::Vector2f& position)
{
    cells_[to_cell(position)].push_back(particle_id);
}

std::vector<std::pair<size_t, size_t>> SpatialGrid::potential_pairs() const
{
    std::vector<std::pair<size_t, size_t>> pairs;

    for (const auto& [cell, particle_ids] : cells_) {
        const auto size = particle_ids.size();
        if (size > 1) {
            for (size_t i = 0; i < size - 1; ++i) {
                for (size_t j = i + 1; j < size; ++j) {
                    pairs.emplace_back(particle_ids[i], particle_ids[j]);
                }
            }
        }
    }

    return pairs;
}

std::size_t PairHash::operator()(const std::pair<int, int>& p) const noexcept
{
    return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
}

} // namespace box::collision_detector
