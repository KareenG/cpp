#include <ctime>
#include <iostream>

#include "arkanoid/game.hpp"
#include "arkanoid/binary_file_high_score_storage.hpp"
#include "arkanoid/high_score_entry.hpp"

namespace arkanoid {

Game::Game(sf::Vector2u window_size, const std::string& title)
: window_(sf::VideoMode(window_size), title)
, scene_{}
, ui_{}
, music_muted_{false}
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    load_and_play_music();

    auto storage = std::make_unique<BinaryFileHighScoreStorage>(consts::Top10FileName);
    top_scores_ = std::make_unique<HighScoreTable>(std::move(storage));

    // Start at the Opening Scene
    scene_ = std::make_unique<scene::OpeningScene>(window_, ui_);
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

        // M key: toggle mute
        if (event->is<sf::Event::KeyPressed>()) {
            auto key_code = event->getIf<sf::Event::KeyPressed>()->code;
            if (key_code == sf::Keyboard::Key::M) {
                music_muted_ = !music_muted_;
                background_music_.setVolume(music_muted_ ? 0.f : 50.f);
                std::cout << (music_muted_ ? "Music muted\n" : "Music unmuted\n");
            }
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
            //std::cout << "GameScene" << '\n';
            scene_ = std::make_unique<scene::GameScene>(top_scores_.get(), ui_);
            break;
        case scene::SceneID::Top10:
            //std::cout << "Top10Scene" << '\n';
            scene_ = std::make_unique<scene::Top10Scene>(window_, top_scores_.get(), ui_);
            break;
        case scene::SceneID::Opening:
            //std::cout << '\n' << top_scores_->display();
            //std::cout << "OpeningScene" << '\n';
            scene_ = std::make_unique<scene::OpeningScene>(window_, ui_);
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

    // --- Flush lingering SFML events to prevent accidental scene double-jump ---
    while (window_.pollEvent()) { /* discard all */ }
}

void Game::load_and_play_music()
{
    if (!background_music_.openFromFile(consts::BackgroundMusic)) {
        throw std::runtime_error("Failed to load music.");
    }

    background_music_.setLooping(true);
    background_music_.setVolume(50.f); // 0 to 100
    background_music_.play();
}

} // namespace arkanoid