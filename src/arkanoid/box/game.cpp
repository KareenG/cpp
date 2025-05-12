#include <cmath> // for sin and cos
#include <cstdlib> // uint8_t

#include "arkanoid/box/game.hpp"
#include "arkanoid/box/collision_detector.hpp"

namespace box
{

const Game::VelocityGenerator Game::velocity_gen_ = []() {
    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.1415926f;
    float speed = 50.f + static_cast<float>(std::rand() % 100);
    return sf::Vector2f{std::cos(angle) * speed, std::sin(angle) * speed};
};

const Game::ColorGenerator Game::color_gen_ = []() {
    return sf::Color(
        static_cast<uint8_t>(std::rand() % 256),
        static_cast<uint8_t>(std::rand() % 256),
        static_cast<uint8_t>(std::rand() % 256)
    );
};

const Game::RadiusGenerator Game::radius_gen_ = [] {
    return 20.f + static_cast<float>(std::rand() % 10); // radius in [20, 29]
};

const Game::PositionGenerator Game::position_gen_ = [] {
    return sf::Vector2f{
        100.f + static_cast<float>(std::rand() % 600),
        100.f + static_cast<float>(std::rand() % 400)
    };
};

Game::Game(sf::Vector2u window_size, const std::string& title, int particle_count, const std::string& font_path)
: window_(sf::VideoMode(window_size), title)
, box_({20.f, 20.f}, sf::Vector2f(window_size) - sf::Vector2f{40.f, 40.f})
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
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    initialize_pause_text();

    for (int i = 0; i < particle_count; ++i) {
        add_random_ball();
    }
}

void Game::initialize_pause_text()
{
    pause_text_.setFont(font_);
    pause_text_.setCharacterSize(24);
    pause_text_.setFillColor(sf::Color::Black);
    pause_text_.setString("[PAUSED] Press Space to Resume");

    // Estimate size: width = character_size * num_chars * scale
    constexpr float char_width_estimate = 0.6f; // average width in em units
    constexpr float padding = 20.f;

    unsigned int char_size = pause_text_.getCharacterSize();
    std::size_t char_count = pause_text_.getString().getSize();

    float estimated_text_width  = char_size * char_width_estimate * static_cast<float>(char_count);
    float estimated_text_height = char_size * 1.5f;

    sf::Vector2f center = {
        static_cast<float>(window_.getSize().x) / 2.f,
        static_cast<float>(window_.getSize().y) / 2.f
    };

    // Manually center text using estimated dimensions
    pause_text_.setOrigin( {estimated_text_width / 2.f, estimated_text_height / 2.f} );
    pause_text_.setPosition(center);

    // Configure pause background using the same estimates
    pause_background_.setSize({estimated_text_width + padding, estimated_text_height + padding});
    pause_background_.setFillColor(sf::Color::White);
    pause_background_.setOrigin(pause_background_.getSize() / 2.f);
    pause_background_.setPosition(center);

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
            } else if (code == sf::Keyboard::Key::Enter) {
                add_random_ball();
            } else if (code == sf::Keyboard::Key::Backspace && !balls_.empty()) {
                balls_.pop_back();
            }
        }
    }
}

void Game::update(sf::Time delta_time)
{
    if (paused_) {
        return;
    }
        
    float dt = delta_time.asSeconds();

    // Update particle logic clearly
    for (auto& ball : balls_) {
        ball->update(dt);
        collision_detector::handle_box_collision(*ball, box_);
    }

    // Simple collision logic
    for (size_t i = 0; i < balls_.size(); ++i) {
        for (size_t j = i + 1; j < balls_.size(); ++j) {
            collision_detector::handle_particle_collision(*balls_[i], *balls_[j]);
        }
    }  
}

void Game::render()
{
    window_.clear(sf::Color::Black);
    box_.draw(window_);
    for (const auto& ball : balls_)
        ball->draw(window_);

    if (paused_ && pause_text_initialized_) {
        window_.draw(pause_background_);
        window_.draw(pause_text_);
    }

    window_.display();
}

void Game::run(int fps)
{
    sf::Clock clock;
    sf::Time time_per_frame = sf::seconds(1.f / fps);
    sf::Time accumulator = sf::Time::Zero;

    while (window_.isOpen()) {
        process_events();
        accumulator += clock.restart();

        while (accumulator >= time_per_frame) {
            accumulator -= time_per_frame;
            update(time_per_frame);
        }
        render();
    }
}
    
} // namespace box
