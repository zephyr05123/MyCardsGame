#ifndef GAME_MODEL_FROM_LEVEL_GENERATOR_H
#define GAME_MODEL_FROM_LEVEL_GENERATOR_H

#include <memory>
#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

/**
 * @brief Generates a runtime GameModel from static LevelConfig.
 * @details Assigns ids and initializes card zones and positions.
 */
namespace cardgame {

class GameModelFromLevelGenerator
{
public:
    /**
     * @brief Build a GameModel from level configuration.
     * @param config Level configuration.
     * @return Unique pointer to a populated GameModel.
     */
    static std::unique_ptr<GameModel> generate(const LevelConfig& config);
};

} // namespace cardgame

#endif // GAME_MODEL_FROM_LEVEL_GENERATOR_H
