#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "arkanoid/game_scene.hpp"
#include "arkanoid/input_controller.hpp"
#include "arkanoid/collision_detector.hpp"
#include "arkanoid/brick.hpp"
#include "arkanoid/heart_shape.hpp"

namespace arkanoid {
namespace scene {

GameScene::GameScene(GameBoard* board, Player* player, const std::string& font_path)
: board_(board)
, player_(player)
, font_([&font_path]() {
    sf::Font f{};
    if (!f.openFromFile(font_path)) {
        throw std::runtime_error("Failed to load font from " + font_path);
    }
    return f;
    }())
, score_text_{font_, "Score: 0", 24}
, lives_text_{font_, "Lives: 3", 20}
{
    score_text_.setFillColor(sf::Color::White);
    score_text_.setPosition({12.f, 12.f});
    setup_input_bindings();
}

void GameScene::setup_input_bindings() {
    input_controller::clear();

    input_controller::bind_key(sf::Keyboard::Key::Escape, [this]() {
        next_scene_ = SceneID::Opening;
    });

    input_controller::bind_key(sf::Keyboard::Key::Space, [this]() {
        if (!game_started_) {
            board_->launch_ball();  // Centralized launch
            game_started_ = true;
            paused_ = false;
            ball_fell_down_ = false;
        } else {
            paused_ = !paused_;
        }
    });
    
    input_controller::bind_key(sf::Keyboard::Key::Left, [this]() {
        if (game_started_ && !paused_) {
            board_->move_paddle_left();
        }
    });

    input_controller::bind_key(sf::Keyboard::Key::Right, [this]() {
        if (game_started_ && !paused_) {
            board_->move_paddle_right();
        }
    });
}

SceneEvent GameScene::handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event) {
    (void)window; // Unused parameter
    
    if (!event.has_value()) {
        return SceneEvent::None;
    }
    
    if (event->is<sf::Event::Closed>()) {
        return SceneEvent::QuitScene;
    }
    
    // Handle key press events through the input controller
    if (event->is<sf::Event::KeyPressed>()) {
        input_controller::handle_event(*event);
        
        // Special handling for Space and Escape keys
        auto key = event->getIf<sf::Event::KeyPressed>();
        switch (key->code) {
            // case sf::Keyboard::Key::Space:
            //     if (paused_){//} && !ball_fell_down_) {
            //         return SceneEvent::PauseToggle;
            //     }
            //     return SceneEvent::None;
                
            case sf::Keyboard::Key::Escape:
                return SceneEvent::QuitScene;
                
            default:
                return SceneEvent::None;
        }
    }
    
    // Handle key release events
    if (event->is<sf::Event::KeyReleased>()) {
        input_controller::handle_key_released(*event);
    }
    
    return SceneEvent::None;
}

void GameScene::update(float dt) {
    if (show_game_over_text_) {
        game_over_timer_ += dt;
        if (game_over_timer_ > 20.f) std::exit(0);
        return;
    }

    if (show_win_text_) {
        win_timer_ += dt;
        if (win_timer_ > 15.f) {
            player_->reset();
            board_->reset();
            score_text_.setString("Score: " + std::to_string(player_->get_score()));
            game_started_ = false;
            paused_ = false;
            ball_fell_down_ = false;
            show_game_over_text_ = false;
            game_over_timer_ = 0.f;
            show_win_text_ = false;
            win_timer_ = 0.f;
        }
        return;
    }

       // NEW: poll keyboard input for continuous keys (e.g. arrows)
    input_controller::poll();

    if (!game_started_ || paused_) return;



    board_->update(dt);
    auto result = board_->handle_collision();
    switch (result) {
        case collision_detector::CollisionResult::NoChange:
            break;
        case collision_detector::CollisionResult::BallFell: {
            player_->decrease_life();
            game_started_ = false;
            ball_fell_down_ = true;
            if (player_->get_lives() == 0) {
                show_game_over_text_ = true;
                game_over_timer_ = 0.f;
            }
            break;
        }
            
        case collision_detector::CollisionResult::BrickHit: {
            player_->add_score(40);
            score_text_.setString("Score: " + std::to_string(player_->get_score()));
            break;
        }
            
        case collision_detector::CollisionResult::LevelComplete: {
            show_win_text_ = true;
            win_timer_ = 0.f;
            break;
        }
    }       
}

void GameScene::render(sf::RenderWindow& window) const {
    board_->draw(window);

    sf::RectangleShape bg{{160.f, 40.f}};
    bg.setPosition( {8.f, 8.f} );
    bg.setFillColor(sf::Color::Black);
    window.draw(bg);
    window.draw(score_text_);
    draw_lives(window);

    if (show_game_over_text_) {
        sf::Text game_over(font_, "Game Over");
        game_over.setCharacterSize(48);
        game_over.setFillColor(sf::Color::Red);
        game_over.setPosition( {200.f, 300.f} );
        window.draw(game_over);
    }

    if (show_win_text_) {
        board_->reset_ball_paddle();
        sf::Text win(font_, "You Win");
        
        win.setCharacterSize(48);
        win.setFillColor(sf::Color::Green);
        win.setPosition( {220.f, 300.f} );
        window.draw(win);
    }
}

SceneID GameScene::get_next_scene() const {
    return next_scene_;
}

void GameScene::draw_lives(sf::RenderWindow& window) const
{
    // === HEART CONFIGURATION ===
        // Constants
    // ❤️ Draw Hearts at {window_width - 12 - total_heart_width, 12}
    if(player_->get_lives() == 0) return;
    const float heart_size = 24.f;
    const float padding = 4.f;
    std::size_t lives = player_->get_lives();
    float total_width = heart_size * lives + padding * (lives - 1);

    float x_right = static_cast<float>(window.getSize().x) - 12.f;
    float x_start = x_right - total_width;
    float y_start = 24.f;

    sf::Vector2f bg_size{total_width + 8.f, heart_size + 8.f};
    sf::Vector2f bg_position{x_start - 4.f, y_start - (bg_size.y - heart_size) / 2.f};

    sf::RectangleShape heart_bg(bg_size);
    heart_bg.setPosition(bg_position);
    heart_bg.setFillColor(sf::Color::Black);
    window.draw(heart_bg);

    HeartShape::draw(window, {x_start + 18.f, y_start}, lives, heart_size);
}

} // namespace scene
} // namespace arkanoid