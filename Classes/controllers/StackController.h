#ifndef STACK_CONTROLLER_H
#define STACK_CONTROLLER_H

#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

/**
 * @brief Handles stack flip interactions.
 */
namespace cardgame {

class StackController
{
public:
    void init(GameModel* model, GameView* view, UndoManager* undoManager);
    bool handleStackClick();

private:
    GameModel* _gameModel = nullptr;
    GameView* _gameView = nullptr;
    UndoManager* _undoManager = nullptr;
};

} // namespace cardgame

#endif // STACK_CONTROLLER_H
