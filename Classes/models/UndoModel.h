#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H

#include <vector>
#include "cocos2d.h"

/**
 * @brief Undo record and stack for playfield matches and stack flips.
 */
namespace cardgame {

enum class UndoType
{
    MATCH = 0,
    STACK_FLIP
};

struct UndoRecord
{
    UndoType type = UndoType::MATCH;
    int movedCardId = -1;
    int prevTrayCardId = -1;
    cocos2d::Vec2 fromPosition;
    cocos2d::Vec2 prevTrayPosition;
};

class UndoModel
{
public:
    std::vector<UndoRecord> records;
};

} // namespace cardgame

#endif // UNDO_MODEL_H
