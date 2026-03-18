#ifndef GAME_MODEL_FROM_LEVEL_GENERATOR_H
#define GAME_MODEL_FROM_LEVEL_GENERATOR_H

#include <memory>
#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

/**
 * @brief Generates runtime GameModel from static LevelConfig.
 */
namespace cardgame {

class GameModelFromLevelGenerator
{
public:
    static std::unique_ptr<GameModel> generate(const LevelConfig& config);
};

} // namespace cardgame

#endif // GAME_MODEL_FROM_LEVEL_GENERATOR_H
