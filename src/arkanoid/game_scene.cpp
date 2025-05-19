#include "arkanoid/game_scene.hpp"
#include "arkanoid/collision_detector.hpp"
#include "arkanoid/resources_and_consts.hpp"
#include "arkanoid/input_name.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

namespace arkanoid {
namespace scene {

GameScene::GameScene(HighScoreTable* high_scores, int num_level, const std::string& font_path)
: board_(consts::ArkanoidBoxSize)//(sf::Vector2f{760.f, 560.f})// adjust as needed for your board size
, player_("Player1", 3)
, num_level_{num_level}
, font_([&font_path]() {
      sf::Font f{};
      if (!f.openFromFile(font_path)) {
          throw std::runtime_error("Failed to load font from " + font_path);
      }
      return f;
  }())
, input_controller_{}
, ui_(consts::FontArial)
, logic_(&player_, &board_, num_level)
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
        if (started_ && !paused_) {
            board_.move_paddle_left();
        }
    });

    input_controller_.bind_key(sf::Keyboard::Key::Right, [this]() {
        if (started_ && !paused_) {
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
                num_level_ = 1;  // Reset to level 1 if quitting
                reset_level();
                notify_scene_change(SceneID::Opening);
            } else if (key == sf::Keyboard::Key::N) {
                overlay_.cancel();
            }
        }
        return SceneEvent::None;
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
                //std::cout << "max score reached: " << player_.max_score() << '\n';
                size_t score = player_.max_score();
                if (high_scores_ && high_scores_->qualifies(score, logic_.elapsed_time())) {
                    name_input_.show("New High Score! Enter your name:", [this, score](const std::string& name) {
                        high_scores_->add_score(name, score, logic_.elapsed_time());
                        finish_scene(); // return to opening
                    });
                    return; // Delay finish until name entered
                }

                // num_level_ = 1;
                // reset_level();
                // notify_scene_change(SceneID::Opening);
                finish_scene();

            } else if (overlay_.type() == OverlayType::Win) {
                if (num_level_ < consts::MaxLevels) {
                    ++num_level_;
                    reset_level();

                } else {

                    player_.update_max_score();
                    //std::cout << "max score reached: " << player_.max_score() << '\n';

                    size_t score = player_.max_score();
                    if (high_scores_ && high_scores_->qualifies(score, logic_.elapsed_time())) {
                        name_input_.show("New High Score! Enter your name:", [this, score](const std::string& name) {
                            high_scores_->add_score(name, score, logic_.elapsed_time());
                            finish_scene(); // return to opening
                        });
                        return; // Delay finish until name entered
                    }

                    reset_level();
                    notify_scene_change(SceneID::Opening);
                }
            }
        }
        return;
    }

    input_controller_.poll();

    if (!started_ || paused_) {
        return;
    }

    GameStatus status = logic_.update(dt);

    switch (status) {
        case GameStatus::BallFell:
            started_ = false;
            ball_fell_down_ = true;
            if (player_.get_lives() == 0) {
                overlay_.show(OverlayType::GameOver);
            }
            break;
        case GameStatus::BrickHit:
            break;
        case GameStatus::LevelComplete:
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
    ui_.draw_level(window, num_level_);

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
    board_.reset(num_level_);
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
void GameScene::finish_scene()
{
    num_level_ = 1;
    reset_level();
    notify_scene_change(SceneID::Opening);
}

} // namespace scene
} // namespace arkanoid
