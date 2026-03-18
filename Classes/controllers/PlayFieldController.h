#ifndef PLAY_FIELD_CONTROLLER_H
#define PLAY_FIELD_CONTROLLER_H

#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

/**
 * @brief Handles playfield card interactions.
 */
namespace cardgame {

class PlayFieldController
{
public:
    void init(GameModel* model, GameView* view, UndoManager* undoManager);
    bool handleCardClick(int cardId);

private:
    GameModel* _gameModel = nullptr;
    GameView* _gameView = nullptr;
    UndoManager* _undoManager = nullptr;
};

} // namespace cardgame

#endif // PLAY_FIELD_CONTROLLER_H
