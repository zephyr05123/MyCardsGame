#ifndef LEVEL_CONFIG_H
#define LEVEL_CONFIG_H

#include <vector>
#include "cocos2d.h"
#include "utils/CardTypes.h"

/**
 * @brief Static level configuration data parsed from JSON.
 * @details Used to build the initial GameModel state for a level.
 */
namespace cardgame {

/**
 * @brief Static card config entry in a level file.
 */
struct LevelCardConfig
{
    /** @brief Card face value (0..12). */
    int cardFace = CFT_NONE;

    /** @brief Card suit value (0..3). */
    int cardSuit = CST_NONE;

    /** @brief Absolute position for this card in level space. */
    cocos2d::Vec2 position;
};

/**
 * @brief Container for playfield and stack card configs.
 * @details Playfield cards are placed on the table; stack cards form the draw pile.
 */
class LevelConfig
{
public:
    /** @brief Playfield cards (fixed positions). */
    std::vector<LevelCardConfig> playfield;

    /** @brief Stack cards (draw order as configured). */
    std::vector<LevelCardConfig> stack;
};

} // namespace cardgame

#endif // LEVEL_CONFIG_H
