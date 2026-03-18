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

    CardModel* card = _getPlayfieldCard(cardId);
    if (!card)
    {
        return false;
    }

    CardModel* trayCard = _getTrayTopCard();
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
    record.prevTrayCardId = trayCard->id;
    record.fromPosition = card->position;
    record.prevTrayPosition = trayCard->position;

    _pushMatchUndo(record);
    _applyMatchMove(record, card, trayCard);

    return true;
}

CardModel* PlayFieldController::_getPlayfieldCard(int cardId) const
{
    if (!_gameModel)
    {
        return nullptr;
    }

    CardModel* card = _gameModel->getCardById(cardId);
    if (!card || card->zone != CardZone::PLAYFIELD)
    {
        return nullptr;
    }

    return card;
}

CardModel* PlayFieldController::_getTrayTopCard() const
{
    if (!_gameModel)
    {
        return nullptr;
    }

    const int kTrayId = _gameModel->trayTopCardId;
    if (kTrayId == -1)
    {
        return nullptr;
    }

    return _gameModel->getCardById(kTrayId);
}

void PlayFieldController::_pushMatchUndo(const UndoRecord& record)
{
    if (_undoManager)
    {
        _undoManager->pushRecord(record);
    }
}

void PlayFieldController::_applyMatchMove(const UndoRecord& record, CardModel* card, CardModel* trayCard)
{
    if (!_gameModel || !_gameView || !card || !trayCard)
    {
        return;
    }

    // Update model state
    _gameModel->removePlayfieldCard(card->id);
    trayCard->zone = CardZone::DISCARD;
    _gameModel->discardCardIds.push_back(trayCard->id);

    card->zone = CardZone::TRAY;
    const cocos2d::Vec2 kTrayPos = _gameView->getTrayPosition();
    card->position = kTrayPos;
    _gameModel->trayTopCardId = card->id;

    // Update view
    _gameView->showCard(trayCard->id, false);
    _gameView->setCardInteractive(trayCard->id, false);

    _gameView->placeCardInZone(card->id, CardZone::TRAY, record.fromPosition);
    _gameView->moveCardTo(card->id, kTrayPos, kMoveDuration);
    _gameView->setCardInteractive(card->id, false);
    _gameView->setTrayTopCard(card->id);
}

} // namespace cardgame

