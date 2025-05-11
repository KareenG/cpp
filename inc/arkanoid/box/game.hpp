#pragma once

#include <functional>

#include "arkanoid/box/entity.hpp"
#include "arkanoid/box/particle.hpp"
#include "arkanoid/box/box.hpp"

namespace box
{

class Game {
public:
    using VelocityGenerator = std::function<sf::Vector2f()>;
    using ColorGenerator = std::function<sf::Color()>;
    using RadiusGenerator   = std::function<float()>;
    using PositionGenerator = std::function<sf::Vector2f()>;

    Game(sf::Vector2u window_size = {800, 600},
        const std::string& title = "Particles in a Box",
        int particle_count = 1,
        const std::string& font_path = "arial.ttf",
        VelocityGenerator velocity_gen = default_velocity,
        ColorGenerator color_gen = default_color,
        RadiusGenerator radius_gen = default_radius,
        PositionGenerator position_gen = default_position);

    void run(int frames_per_second = 60);

private:
    void initialize_pause_text();
    void process_events();
    void update(sf::Time deltaTime);
    void render();
    void add_random_ball();
    void handle_pause();

    static const VelocityGenerator default_velocity;
    static const ColorGenerator default_color;    
    static const RadiusGenerator   default_radius;
    static const PositionGenerator default_position;


private:
    sf::RenderWindow window_;
    Box box_;
    std::vector<std::unique_ptr<Particle>> balls_;
    bool paused_;//{false};
    const sf::Font font_;// = sf::Font("arial.ttf");
    sf::Text pause_text_;//{font, "", 24};
    bool pause_text_initialized_;// = false;
    VelocityGenerator velocity_gen_;
    ColorGenerator color_gen_;
    RadiusGenerator radius_gen_;
    PositionGenerator position_gen_;
};            

} // namespace box