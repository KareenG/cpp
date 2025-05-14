#include "arkanoid/game.hpp"
#include "arkanoid/input_controller.hpp"
#include <cmath>

namespace arkanoid {

using VelocityGenerator = std::function<sf::Vector2f()>;
const VelocityGenerator velocity_gen_ = []() {
    // Random angle between 60°–120°
    float angle_deg = 60.f + static_cast<float>(std::rand() % 61);
    float angle_rad = angle_deg * 3.14159265f / 180.f;
    float speed = 450.f;
    sf::Vector2f velocity = {
        std::cos(angle_rad) * speed,
        -std::sin(angle_rad) * speed
    };
    return velocity;
};

Game::Game(sf::Vector2u window_size, const std::string& title)
: window_(sf::VideoMode(window_size), title)
, player_("Player1", 3)
, board_(sf::Vector2f(window_size) - sf::Vector2f{40.f, 40.f}) // level_num = 1
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // Start directly with GameScene
    scene_ = std::make_unique<scene::GameScene>(&board_, &player_);
}

void Game::run(int target_fps) {
    const sf::Time frame_time = sf::seconds(1.f / static_cast<float>(target_fps));
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;

    while (window_.isOpen()) {
        accumulator += clock.restart();

        process_events();
        while (accumulator >= frame_time) {
            accumulator -= frame_time;
            update(frame_time);
        }

        render();

        // // Handle scene transitions (future use)
        // if (scene_->get_next_scene() != current_scene_id_) {
        //     current_scene_id_ = scene_->get_next_scene();
        //     if (current_scene_id_ == scene::SceneID::Top10) {
        //         // TODO: replace with Top10Scene
        //         window_.close(); // temp fallback
        //     } else if (current_scene_id_ == scene::SceneID::Opening) {
        //         window_.close(); // temp fallback
        //     }
        // }
    }
}

void Game::process_events() {
    while (const std::optional event = window_.pollEvent()) {
        switch (scene_->handle_events(window_, event))
        {
        case scene::SceneEvent::QuitScene:
            window_.close();
            break;
        
        // case scene::SceneEvent::LaunchBall: {
        //     break;
        // }

        case scene::SceneEvent::PauseToggle:
            paused_ = !paused_;
            break;

        default:
            break;
        }
    }
}

void Game::update(sf::Time dt) {
    if (paused_) {
        return;
    }
    scene_->update(dt.asSeconds());
}

void Game::render() {
    window_.clear(sf::Color::Black);
    scene_->render(window_);
    window_.display();
}

} // namespace arkanoid
