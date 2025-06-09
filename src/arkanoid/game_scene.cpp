#include "arkanoid/game_scene.hpp"
#include "arkanoid/collision_detector.hpp"
#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/input_name.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

namespace arkanoid {

namespace scene {

GameScene::GameScene(HighScoreTable* high_scores, const UI& ui)
: level_loader_{}
, board_(consts::ArkanoidBoxSize)
, player_{}
, num_level_{1}
, ui_(ui)
, input_controller_{}
, logic_(&player_, &board_, level_loader_.num_levels(), num_level_)
, overlay_()
, name_input_{}
, high_scores_{high_scores}
{
    setup_input_bindings();
    reset_level();
}

void GameScene::setup_input_bindings() {
    input_controller_.clear();

    input_controller_.bind_key(sf::Keyboard::Key::Escape, [this]() {
        // Instead of instant quit, show confirmation overlay
        overlay_.show(OverlayType::QuitConfirm);
    });

    input_controller_.bind_key(sf::Keyboard::Key::Space, [this]() {
        if (!started_) {
            board_.launch_ball();
            started_ = true;
            paused_ = false;
            ball_fell_down_ = false;
        } else {
            paused_ = !paused_;
        }
    });

    input_controller_.bind_key(sf::Keyboard::Key::Left, [this]() {
        if (!paused_) {
            board_.move_paddle_left();
        }
    });

    input_controller_.bind_key(sf::Keyboard::Key::Right, [this]() {
        if (!paused_) {
            board_.move_paddle_right();
        }
    });
}

SceneEvent GameScene::handle_events(sf::RenderWindow& window, std::optional<sf::Event> const& event)
{
    (void)window;

    if (name_input_.is_active() && event.has_value()) {
        if (event->is<sf::Event::TextEntered>()) {
            name_input_.handle_text(event->getIf<sf::Event::TextEntered>()->unicode);
        } else if (event->is<sf::Event::KeyPressed>()) {
            name_input_.handle_key(event->getIf<sf::Event::KeyPressed>()->code);
        }
        return SceneEvent::None;
    }

    // Overlay gets priority (e.g., confirmation needs Y/N input)
    if (overlay_.is_active()) {
        if (overlay_.is_confirmation() && event && event->is<sf::Event::KeyPressed>()) {
        auto key = event->getIf<sf::Event::KeyPressed>()->code;
        if (key == sf::Keyboard::Key::Y) {
            overlay_.confirm();
            finish_scene(SceneID::Opening);
        } else if (key == sf::Keyboard::Key::N) {
            overlay_.cancel();
        }
        return SceneEvent::None;
}
    }

    if (!event.has_value())
        return SceneEvent::None;

    if (event->is<sf::Event::Closed>())
        return SceneEvent::QuitScene;

    if (event->is<sf::Event::KeyPressed>())
        input_controller_.handle_event(*event);

    if (event->is<sf::Event::KeyReleased>())
        input_controller_.handle_key_released(*event);

    return SceneEvent::None;
}

void GameScene::update(float dt)
{
    // input_controller_.poll();
    if (name_input_.is_active()) {
        name_input_.update(dt);
        return;
    }

    // If overlay is active, only update overlay and handle completion
    if (overlay_.is_active()) {
        overlay_.update(dt);
        if (overlay_.finished()) {
            if (overlay_.type() == OverlayType::GameOver) {
                player_.update_max_score();
                size_t score = player_.max_score();
                if (high_scores_ && high_scores_->qualifies(score, logic_.elapsed_time())) {
                    name_input_.show(consts::NewTop10PromptText, [this, score](const std::string& name) {
                        high_scores_->add_score(name, score, logic_.elapsed_time());
                        finish_scene(SceneID::Top10); // return to opening
                    });
                    return; // Delay finish until name entered
                }
                finish_scene(SceneID::Top10);

            } else if (overlay_.type() == OverlayType::Win) {
                if (num_level_ < level_loader_.num_levels()) {
                    ++num_level_;
                    reset_level();
                } else {
                    player_.update_max_score();
                    size_t score = player_.max_score();
                    if (high_scores_ && high_scores_->qualifies(score, logic_.elapsed_time())) {
                        name_input_.show(consts::NewTop10PromptText, [this, score](const std::string& name) {
                            high_scores_->add_score(name, score, logic_.elapsed_time());
                            finish_scene(SceneID::Top10); // return to opening
                        });
                        return; // Delay finish until name entered
                    }
                    reset_level();
                    notify_scene_change(SceneID::Top10);
                }
            }
        }
        return;
    }

    input_controller_.poll();

    if (paused_) { // !started_ || 
        return;
    }

    GameStatus status = logic_.update(dt);

    switch (status) {
        case GameStatus::BallFell:
            started_ = false;
            ball_fell_down_ = true;
            board_.reset_ball_paddle();
            break;
        case GameStatus::LevelLoss:
            overlay_.show(OverlayType::GameOver);
            break;
        case GameStatus::BrickHit:
            break;
        case GameStatus::LevelWin:
            overlay_.show(OverlayType::Win);
            break;
        default:
            break;
    }
}

void GameScene::render(sf::RenderWindow& window) const
{
    board_.draw(window);
    ui_.draw_score(window, player_.get_score());
    ui_.draw_lives(window, player_.get_lives());
    ui_.draw_level(window, num_level_, level_loader_.num_levels());

    if (overlay_.is_active()) {
        overlay_.render(window, ui_);
    }
    if (name_input_.is_active()) {
        ui_.draw_name_input(window, name_input_.prompt(), name_input_.input());
    }

}

SceneID GameScene::get_next_scene() const
{
    return next_scene_;
}

void GameScene::reset_level()
{
    player_.reset();

    // Get the current level data (adjust if your levels are 1-based)
    const auto& level_data = level_loader_.get_level(num_level_ - 1);

    // Reset the board with the new level data
    board_.reset(level_data);

    // Reset scene state
    started_ = false;
    paused_ = false;
    ball_fell_down_ = false;
}


int GameScene::get_level() const
{
    return num_level_;
}

void GameScene::set_name_input_callback(NameInputCallback cb)
{
    on_name_input_requested_ = std::move(cb);
}

void GameScene::finish_scene(SceneID next)
{ 
    num_level_ = 1;
    reset_level();
    notify_scene_change(next);
}

} // namespace scene

} // namespace arkanoid
