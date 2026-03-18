#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <memory>
#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"
#include "models/UndoModel.h"
#include "views/GameView.h"
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
#include "managers/UndoManager.h"

/**
 * @brief Coordinates game initialization and high-level flow.
 */
namespace cardgame {

class GameController
{
public:
    bool init(cocos2d::Node* parent);

private:
    void handleUndo();
    void initTrayAndStack();
    void removeDiscardId(int cardId);
    void removeStackId(int cardId);

    std::unique_ptr<GameModel> _gameModel;
    std::unique_ptr<UndoModel> _undoModel;
    std::unique_ptr<UndoManager> _undoManager;

    std::unique_ptr<PlayFieldController> _playFieldController;
    std::unique_ptr<StackController> _stackController;

    GameView* _gameView = nullptr;
};

} // namespace cardgame

#endif // GAME_CONTROLLER_H
