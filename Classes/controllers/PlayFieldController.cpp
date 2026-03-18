#include "controllers/PlayFieldController.h"

#include "services/CardMatchService.h"

namespace cardgame {

namespace {

const float kMoveDuration = 0.2f;

} // namespace

void PlayFieldController::init(GameModel* model, GameView* view, UndoManager* undoManager)
{
    _gameModel = model;
    _gameView = view;
    _undoManager = undoManager;
}

bool PlayFieldController::handleCardClick(int cardId)
{
    if (!_gameModel || !_gameView)
    {
        return false;
    }

    CardModel* card = _gameModel->getCardById(cardId);
    if (!card || card->zone != CardZone::PLAYFIELD)
    {
        return false;
    }

    const int trayId = _gameModel->trayTopCardId;
    if (trayId == -1)
    {
        return false;
    }

    CardModel* trayCard = _gameModel->getCardById(trayId);
    if (!trayCard)
    {
        return false;
    }

    if (!CardMatchService::isMatch(card->face, trayCard->face))
    {
        return false;
    }

    UndoRecord record;
    record.type = UndoType::MATCH;
    record.movedCardId = cardId;
    record.prevTrayCardId = trayId;
    record.fromPosition = card->position;
    record.prevTrayPosition = trayCard->position;
    if (_undoManager)
    {
        _undoManager->pushRecord(record);
    }

    // Update model state
    _gameModel->removePlayfieldCard(cardId);
    trayCard->zone = CardZone::DISCARD;
    _gameModel->discardCardIds.push_back(trayId);

    card->zone = CardZone::TRAY;
    const cocos2d::Vec2 trayPos = _gameView->getTrayPosition();
    card->position = trayPos;
    _gameModel->trayTopCardId = cardId;

    // Update view
    _gameView->showCard(trayId, false);
    _gameView->setCardInteractive(trayId, false);

    _gameView->placeCardInZone(cardId, CardZone::TRAY, record.fromPosition);
    _gameView->moveCardTo(cardId, trayPos, kMoveDuration);
    _gameView->setCardInteractive(cardId, false);
    _gameView->setTrayTopCard(cardId);

    return true;
}

} // namespace cardgame


