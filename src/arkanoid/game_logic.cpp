#include "arkanoid/game_logic.hpp"
#include "arkanoid/resources_and_consts.hpp"

namespace arkanoid {

GameLogic::GameLogic(Player* player, GameBoard* board, size_t total_levels, size_t num_level)
: player_(player)
, board_(board)
, current_level_(num_level)
, elapsed_time_{0.f}
, total_levels_{total_levels}
{
}

GameStatus GameLogic::update(float dt)
{
    elapsed_time_ += dt;
    board_->update(dt);
    auto result_info = board_->handle_collision(current_level_);
    auto result = result_info.result;

    switch (result) {
        case collision_detector::CollisionResult::NoChange:
            return GameStatus::NoChange;
        case collision_detector::CollisionResult::BallFell:
            player_->decrease_life();
            if (player_->get_lives() == 0) {
                return GameStatus::LevelLoss;
            }
            return GameStatus::BallFell;
        case collision_detector::CollisionResult::BrickHit:
            //player_->add_score(40);
            player_->add_score(result_info.score_gained);
            return GameStatus::BrickHit;
        case collision_detector::CollisionResult::LevelComplete:
            return GameStatus::LevelWin;
        default:
            return GameStatus::NoChange;
    }
}

void GameLogic::level_complete()
{
    if (current_level_ < total_levels_) {
        current_level_++;
    }
}

// Logic for game over
int GameLogic::get_current_level() const
{
    return current_level_;
}

// scene::SceneID GameLogic::get_next_scene(GameStatus status)
// {
//     if (status == GameStatus::LevelWin) {
//         if (current_level_ == total_levels_) {
//             return scene::SceneID::Top10;  // All levels complete, return to opening
//         }
//         return scene::SceneID::Game; // Proceed to next level
//     }
//     return scene::SceneID::Top10;  // Return to OpeningScene if the player loses
// }
scene::SceneID GameLogic::get_next_scene(GameStatus status)
{
    if (status == GameStatus::LevelWin) {
        if (current_level_ == total_levels_) {
            return scene::SceneID::Top10;  // All levels complete, return to opening
        }
        return scene::SceneID::Game; // Proceed to next level
    }
    //if (status == GameStatus::LevelLoss) {
        return scene::SceneID::Top10;  // Return to OpeningScene if the player loses
    //}
    //return scene::SceneID::None;
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
