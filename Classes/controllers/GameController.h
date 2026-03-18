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
 * @details Owns the model, view, and sub-controllers.
 */
namespace cardgame {

class GameController
{
public:
    /**
     * @brief Initialize the game and attach to the parent node.
     * @param parent Parent node that owns the game view.
     * @return true when initialization succeeds.
     */
    bool init(cocos2d::Node* parent);

private:
    /** @brief Handle undo button click. */
    void _handleUndo();

    /** @brief Initialize the tray top and stack top cards. */
    void _initTrayAndStack();

    /** @brief Remove a card id from the discard list. */
    void _removeDiscardId(int cardId);

    /** @brief Remove a card id from the stack list. */
    void _removeStackId(int cardId);

    /** @brief Apply a match-type undo record. */
    void _applyMatchUndo(const UndoRecord& record, CardModel* movedCard, CardModel* prevTrayCard);

    /** @brief Apply a stack-flip undo record. */
    void _applyStackFlipUndo(const UndoRecord& record, CardModel* movedCard, CardModel* prevTrayCard);

    /** @brief Rebind playfield card callbacks after model changes. */
    void _rebindPlayFieldCallbacks();

    /** @brief Runtime game state. */
    std::unique_ptr<GameModel> _gameModel;

    /** @brief Undo model storage. */
    std::unique_ptr<UndoModel> _undoModel;

    /** @brief Undo stack manager. */
    std::unique_ptr<UndoManager> _undoManager;

    /** @brief Playfield logic controller. */
    std::unique_ptr<PlayFieldController> _playFieldController;

    /** @brief Stack logic controller. */
    std::unique_ptr<StackController> _stackController;

    /** @brief Root game view. */
    GameView* _gameView = nullptr;
};

} // namespace cardgame

#endif // GAME_CONTROLLER_H
