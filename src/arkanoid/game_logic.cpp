#include "arkanoid/game_logic.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid {

GameLogic::GameLogic(Player* player, GameBoard* board, int num_level)
: player_(player)
, board_(board)
, current_level_(num_level)
, elapsed_time_{0.f}
{
}

GameStatus GameLogic::update(float dt)
{
    elapsed_time_ += dt;
    board_->update(dt);
    auto result = board_->handle_collision();

    switch (result) {
        case collision_detector::CollisionResult::NoChange:
            return GameStatus::NoChange;
        case collision_detector::CollisionResult::BallFell:
            player_->decrease_life();
            if (player_->get_lives() == 0) {
                return GameStatus::BallFell;
            }
            return GameStatus::BallFell;
        case collision_detector::CollisionResult::BrickHit:
            player_->add_score(40);
            return GameStatus::BrickHit;
        case collision_detector::CollisionResult::LevelComplete:
            return GameStatus::LevelComplete;
        default:
            return GameStatus::NoChange;
    }
}

void GameLogic::level_complete()
{
    if (current_level_ < 4) {
        current_level_++;
    }
}

// Logic for game over
int GameLogic::get_current_level() const
{
    return current_level_;
}

scene::SceneID GameLogic::get_next_scene(GameStatus status)
{
    if (status == GameStatus::LevelComplete) {
        if (current_level_ == consts::MaxLevels) {
            return scene::SceneID::Opening;  // All levels complete, return to opening
        }
        return scene::SceneID::Game; // Proceed to next level
    }
    return scene::SceneID::Opening;  // Return to OpeningScene if the player loses
}

float GameLogic::elapsed_time() const
{ 
    return elapsed_time_;
}

void GameLogic::reset_time()
{ 
    elapsed_time_ = 0.f;
}

} // namespace arkanoid
