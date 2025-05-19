#pragma once

#include "arkanoid/player.hpp"
#include "arkanoid/game_board.hpp"
#include "arkanoid/scene.hpp"

namespace arkanoid {

enum class GameStatus {
    NoChange,
    BallFell,
    BrickHit,
    LevelComplete,
};

class GameLogic {
public:
    GameLogic(Player* player, GameBoard* board, int num_level = 1);

    GameStatus update(float dt); //void

    // Logic for level completion (advance level or trigger scene change)
    void level_complete();

    int get_current_level() const;

    scene::SceneID get_next_scene(GameStatus status);

    float elapsed_time() const;

    void reset_time();


private:
    Player* player_;
    GameBoard* board_;
    int current_level_;
    float elapsed_time_;
};

} // namespace arkanoid
