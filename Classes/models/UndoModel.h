#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H

#include <vector>
#include "cocos2d.h"

/**
 * @brief Undo record definitions and storage.
 * @details Records all reversible actions for controller-level undo.
 */
namespace cardgame {

/**
 * @brief Undo record type.
 */
enum class UndoType
{
    MATCH = 0,
    STACK_FLIP
};

/**
 * @brief Single undo record storing all data needed to reverse an action.
 */
struct UndoRecord
{
    /** @brief Undo record type. */
    UndoType type = UndoType::MATCH;

    /** @brief The card id moved by the action. */
    int movedCardId = -1;

    /** @brief Previous tray top card id before the action. */
    int prevTrayCardId = -1;

    /** @brief Original position of the moved card. */
    cocos2d::Vec2 fromPosition;

    /** @brief Original position of the previous tray card. */
    cocos2d::Vec2 prevTrayPosition;
};

/**
 * @brief Stack of undo records.
 */
class UndoModel
{
public:
    /** @brief Undo record stack (last-in, first-out). */
    std::vector<UndoRecord> records;
};

} // namespace cardgame

#endif // UNDO_MODEL_H
