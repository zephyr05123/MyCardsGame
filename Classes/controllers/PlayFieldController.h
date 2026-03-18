#ifndef PLAY_FIELD_CONTROLLER_H
#define PLAY_FIELD_CONTROLLER_H

#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

/**
 * @brief Handles playfield card interactions.
 * @details Validates matches and moves playfield cards to the tray.
 */
namespace cardgame {

class PlayFieldController
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
     * @brief Handle a playfield card click.
     * @param cardId Clicked card id.
     * @return true when a valid match was processed.
     */
    bool handleCardClick(int cardId);

private:
    /** @brief Get a playfield card by id. */
    CardModel* _getPlayfieldCard(int cardId) const;

    /** @brief Get the current tray top card. */
    CardModel* _getTrayTopCard() const;

    /** @brief Push a match undo record. */
    void _pushMatchUndo(const UndoRecord& record);

    /** @brief Apply model and view updates for a match. */
    void _applyMatchMove(const UndoRecord& record, CardModel* card, CardModel* trayCard);

    /** @brief Game model pointer (not owned). */
    GameModel* _gameModel = nullptr;

    /** @brief Game view pointer (not owned). */
    GameView* _gameView = nullptr;

    /** @brief Undo manager pointer (not owned). */
    UndoManager* _undoManager = nullptr;
};

} // namespace cardgame

#endif // PLAY_FIELD_CONTROLLER_H
