#ifndef LEVEL_CONFIG_H
#define LEVEL_CONFIG_H

#include <vector>
#include "cocos2d.h"
#include "utils/CardTypes.h"

/**
 * @brief Static level config data parsed from JSON.
 */
namespace cardgame {

struct LevelCardConfig
{
    int cardFace = CFT_NONE;
    int cardSuit = CST_NONE;
    cocos2d::Vec2 position;
};

class LevelConfig
{
public:
    /**
     * @brief Playfield cards (fixed positions).
     */
    std::vector<LevelCardConfig> playfield;

    /**
     * @brief Stack cards (order as configured).
     */
    std::vector<LevelCardConfig> stack;
};

} // namespace cardgame

#endif // LEVEL_CONFIG_H
