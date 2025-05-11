#include <cmath> // for sin and cos
#include <cstdlib> // uint8_t

#include "arkanoid/box/game.hpp"
#include "arkanoid/box/collision_detector.hpp"

namespace box
{

const Game::VelocityGenerator Game::default_velocity = []() {
    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.1415926f;
    float speed = 50.f + static_cast<float>(std::rand() % 100);
    return sf::Vector2f{std::cos(angle) * speed, std::sin(angle) * speed};
};

const Game::ColorGenerator Game::default_color = []() {
    return sf::Color(
        static_cast<uint8_t>(std::rand() % 256),
        static_cast<uint8_t>(std::rand() % 256),
        static_cast<uint8_t>(std::rand() % 256)
    );
};

const Game::RadiusGenerator Game::default_radius = [] {
    return 20.f + static_cast<float>(std::rand() % 10); // radius in [20, 29]
};

const Game::PositionGenerator Game::default_position = [] {
    return sf::Vector2f{
        100.f + static_cast<float>(std::rand() % 600),
        100.f + static_cast<float>(std::rand() % 400)
    };
};

Game::Game(sf::Vector2u window_size,
        const std::string& title,
        int particle_count,
        const std::string& font_path,
        VelocityGenerator velocity_gen,
        ColorGenerator color_gen,
        RadiusGenerator radius_gen,
        PositionGenerator position_gen)
: window_(sf::VideoMode(window_size), title)
, box_({0.f, 0.f}, sf::Vector2f(window_size))
, paused_(false)
, font_([&font_path]() {
 sf::Font f{};
 if (!f.openFromFile(font_path)) {
     throw std::runtime_error("Failed to load font from " + font_path);
 }
 return f;
}())
, pause_text_{font_, "", 24}
, pause_text_initialized_{false}
, velocity_gen_{std::move(velocity_gen)}
, color_gen_{std::move(color_gen)}
, radius_gen_{std::move(radius_gen)}
, position_gen_{std::move(position_gen)}
{
    window_.setFramerateLimit(60);

    for (int i = 0; i < particle_count; ++i) {
        add_random_ball();
    }
}

void Game::run(int frames_per_second) {
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    sf::Time time_per_frame = sf::seconds(1.f / static_cast<float>(frames_per_second));

    while(window_.isOpen()) {
        process_events();
        bool repaint = false;
        time_since_last_update += clock.restart();
        while (time_since_last_update > time_per_frame) {
            time_since_last_update -= time_per_frame;
            repaint = true;
            update(time_per_frame);
        }
        if (repaint) {
            render();
        }
    }
}

void Game::initialize_pause_text()
{
    pause_text_.setFont(font_);
    pause_text_.setCharacterSize(24);
    pause_text_.setFillColor(sf::Color::White);
    pause_text_.setString("[PAUSED] Press Space to Resume");
    pause_text_.setPosition(sf::Vector2f(10.f, 10.f));
    pause_text_initialized_ = true;
}

void Game::add_random_ball()
{
    const sf::Vector2f position = position_gen_();
    const float radius = radius_gen_();
    const sf::Vector2f velocity = velocity_gen_();
    const sf::Color color = color_gen_();

    balls_.emplace_back(std::make_unique<Particle>(position, radius, velocity, color));
}

void Game::process_events()
{
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>() ||
            (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
            window_.close();
        }
        if (event->is<sf::Event::KeyPressed>()) {
            auto code = event->getIf<sf::Event::KeyPressed>()->code;
            if (code == sf::Keyboard::Key::Space) {
                paused_ = !paused_;
                if (paused_) {
                    handle_pause(); // block until unpaused
                }
            } else if (code == sf::Keyboard::Key::Enter) {
                add_random_ball();
            } else if (code == sf::Keyboard::Key::Backspace && !balls_.empty()) {
                balls_.pop_back();
            }
        }
    }
}

void Game::update(sf::Time delta_time) {
    float dt = delta_time.asSeconds();
    for (auto& ball : balls_) {
        ball->update(dt);
        collision_detector::bounce_off_walls(*ball, box_);
    }
    for (std::size_t i = 0; i < balls_.size(); ++i) {
        for (std::size_t j = i + 1; j < balls_.size(); ++j) {
            collision_detector::bounce_particles(*balls_[i], *balls_[j]);
        }
    }
}

void Game::render() {
    if(paused_ && !pause_text_initialized_) {
        initialize_pause_text();
    }
    window_.clear();
    box_.draw(window_);
    for(auto& ball : balls_) {
        ball->draw(window_);
    }
    if (paused_) {
        window_.draw(pause_text_);
    }
    window_.display();
}

void Game::handle_pause()
{
    if (!pause_text_initialized_) {
        initialize_pause_text();
    }

    // Display pause screen once
    window_.clear();
    box_.draw(window_);
    for (const auto& ball : balls_) {
        ball->draw(window_);
    }
    window_.draw(pause_text_);
    window_.display();

    // Enter blocking loop until unpaused
    while (paused_ && window_.isOpen()) {
        while (const std::optional pause_event = window_.pollEvent()) {
            if (pause_event->is<sf::Event::Closed>()) {
                window_.close();
                return;
            }
            if (pause_event->is<sf::Event::KeyPressed>() &&
                pause_event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space) {
                paused_ = false;
            }
        }
        //sf::sleep(sf::milliseconds(50));
    }
}

    
} // namespace box
