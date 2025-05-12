#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "arkanoid/box/particle.hpp"
#include "arkanoid/box/box.hpp"

namespace box
{

class Game {
public:
    using VelocityGenerator = std::function<sf::Vector2f()>;
    using ColorGenerator    = std::function<sf::Color()>;
    using RadiusGenerator   = std::function<float()>;
    using PositionGenerator = std::function<sf::Vector2f()>;

    Game(sf::Vector2u window_size = {800, 600},
         const std::string& title = "Particles in a Box",
         int particle_count = 1,
         const std::string& font_path = "arial.ttf");//,
        //  VelocityGenerator velocity_gen = default_velocity,
        //  ColorGenerator color_gen = default_color,
        //  RadiusGenerator radius_gen = default_radius,
        //  PositionGenerator position_gen = default_position);

    void run(int frames_per_second = 60);

private:
    void initialize_pause_text();
    void process_events();
    void update(sf::Time delta_time);
    void render();
    void add_random_ball();

    static const VelocityGenerator velocity_gen_;
    static const ColorGenerator    color_gen_;    
    static const RadiusGenerator   radius_gen_;
    static const PositionGenerator position_gen_;
    static inline sf::RectangleShape pause_background_{sf::Vector2f(1.f, 1.f)};

private:
    sf::RenderWindow window_;
    Box box_;
    std::vector<std::unique_ptr<Particle>> balls_;
    bool paused_{false};

    sf::Font font_;
    sf::Text pause_text_;
    bool pause_text_initialized_{false};
};

} // namespace box
