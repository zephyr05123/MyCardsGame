#ifndef STACK_CONTROLLER_H
#define STACK_CONTROLLER_H

#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

/**
 * @brief Handles stack flip interactions.
 * @details Moves the top stack card to the tray.
 */
namespace cardgame {

class StackController
{
public:
    /**
     * @brief Initialize the controller with model/view dependencies.
     * @param model Game model pointer.
     * @param view Game view pointer.
     * @param undoManager Undo manager pointer.
     */
    void init(GameModel* model, GameView* view, UndoManager* undoManager);

    /**
     * @brief Handle a stack click and flip the top card.
     * @return true when a card was flipped.
     */
    bool handleStackClick();

private:
    /** @brief Discard the previous tray card and return its position. */
    cocos2d::Vec2 _discardPrevTray(int prevTrayId);

    /** @brief Record a stack-flip undo entry. */
    void _recordStackFlipUndo(int movedCardId, int prevTrayId, const cocos2d::Vec2& prevTrayPos);

    /** @brief Move a card to the tray and update model/view. */
    void _applyTrayFlip(int cardId, CardModel* card);

    /** @brief Update the visible stack top after a flip. */
    void _refreshStackTop();

    /** @brief Game model pointer (not owned). */
    GameModel* _gameModel = nullptr;

    /** @brief Game view pointer (not owned). */
    GameView* _gameView = nullptr;

    /** @brief Undo manager pointer (not owned). */
    UndoManager* _undoManager = nullptr;
};

} // namespace cardgame

#endif // STACK_CONTROLLER_H
