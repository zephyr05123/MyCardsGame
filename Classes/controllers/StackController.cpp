#include "controllers/StackController.h"

namespace cardgame {

namespace {

const float kMoveDuration = 0.2f;

} // namespace

void StackController::init(GameModel* model, GameView* view, UndoManager* undoManager)
{
    _gameModel = model;
    _gameView = view;
    _undoManager = undoManager;
}

bool StackController::handleStackClick()
{
    if (!_gameModel || !_gameView)
    {
        return false;
    }

    if (_gameModel->stackCardIds.empty())
    {
        return false;
    }

    const int cardId = _gameModel->stackCardIds.back();
    _gameModel->stackCardIds.pop_back();

    CardModel* card = _gameModel->getCardById(cardId);
    if (!card)
    {
        return false;
    }

    const int prevTrayId = _gameModel->trayTopCardId;
    cocos2d::Vec2 prevTrayPos = cocos2d::Vec2::ZERO;
    if (prevTrayId != -1)
    {
        CardModel* prevTray = _gameModel->getCardById(prevTrayId);
        if (prevTray)
        {
            prevTrayPos = prevTray->position;
            prevTray->zone = CardZone::DISCARD;
            _gameModel->discardCardIds.push_back(prevTrayId);
            _gameView->showCard(prevTrayId, false);
            _gameView->setCardInteractive(prevTrayId, false);
        }
    }

    UndoRecord record;
    record.type = UndoType::STACK_FLIP;
    record.movedCardId = cardId;
    record.prevTrayCardId = prevTrayId;
    record.fromPosition = _gameView->getStackPosition();
    record.prevTrayPosition = prevTrayPos;
    if (_undoManager)
    {
        _undoManager->pushRecord(record);
    }

    const cocos2d::Vec2 trayPos = _gameView->getTrayPosition();
    card->zone = CardZone::TRAY;
    card->position = trayPos;
    _gameModel->trayTopCardId = cardId;

    _gameView->placeCardInZone(cardId, CardZone::TRAY, _gameView->getStackPosition());
    _gameView->showCard(cardId, true);
    _gameView->moveCardTo(cardId, trayPos, kMoveDuration);
    _gameView->setCardInteractive(cardId, false);
    _gameView->setTrayTopCard(cardId);

    if (!_gameModel->stackCardIds.empty())
    {
        const int newTopId = _gameModel->stackCardIds.back();
        CardModel* newTopCard = _gameModel->getCardById(newTopId);
        if (newTopCard)
        {
            _gameView->placeCardInZone(newTopId, CardZone::STACK, _gameView->getStackPosition());
            _gameView->showCard(newTopId, true);
            _gameView->setStackTopCard(newTopId);
        }
    }
    else
    {
        _gameView->setStackTopCard(-1);
    }

    return true;
}

} // namespace cardgame
