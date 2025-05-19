#include "arkanoid/game.hpp"
#include <ctime>
#include <iostream>

namespace arkanoid {

Game::Game(sf::Vector2u window_size, const std::string& title)
: window_(sf::VideoMode(window_size), title)
, scene_{}
, top_scores_{}
//, ui_{}
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Start at the Opening Scene
    scene_ = std::make_unique<scene::OpeningScene>(window_);
    scene_->subscribe_to_scene_change([this](scene::SceneID id) {
        switch_scene(id);
    });
}

void Game::run(int target_fps)
{
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
    }
    resources::clear();
}

void Game::process_events()
{
    while (const std::optional event = window_.pollEvent()) {
        if(scene_->handle_events(window_, event) == scene::SceneEvent::QuitScene) {
            window_.close();
            break;
        }
    }
}

void Game::update(sf::Time dt)
{
    scene_->update(dt.asSeconds());
}

void Game::render()
{
    window_.clear(sf::Color::Black);
    scene_->render(window_);
    window_.display();
}

void Game::switch_scene(scene::SceneID id) {
    switch (id) {
        case scene::SceneID::Game:
            scene_ = std::make_unique<scene::GameScene>(&top_scores_, 1);
            break;
        case scene::SceneID::Opening:
        std::cout << top_scores_.display();
            scene_ = std::make_unique<scene::OpeningScene>(window_);
            top_scores_.display();
            break;
        default:
            scene_.reset();
            break;
    }

    if (scene_) {
        scene_->subscribe_to_scene_change([this](scene::SceneID next_id) {
            switch_scene(next_id);
        });
    }
}

} // namespace arkanoid