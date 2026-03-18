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

    const int kCardId = _gameModel->stackCardIds.back();
    _gameModel->stackCardIds.pop_back();

    CardModel* card = _gameModel->getCardById(kCardId);
    if (!card)
    {
        return false;
    }

    const int kPrevTrayId = _gameModel->trayTopCardId;
    const cocos2d::Vec2 kPrevTrayPos = _discardPrevTray(kPrevTrayId);

    _recordStackFlipUndo(kCardId, kPrevTrayId, kPrevTrayPos);
    _applyTrayFlip(kCardId, card);
    _refreshStackTop();

    return true;
}

cocos2d::Vec2 StackController::_discardPrevTray(int prevTrayId)
{
    if (!_gameModel || !_gameView || prevTrayId == -1)
    {
        return cocos2d::Vec2::ZERO;
    }

    CardModel* prevTray = _gameModel->getCardById(prevTrayId);
    if (!prevTray)
    {
        return cocos2d::Vec2::ZERO;
    }

    const cocos2d::Vec2 kPrevTrayPos = prevTray->position;
    prevTray->zone = CardZone::DISCARD;
    _gameModel->discardCardIds.push_back(prevTrayId);
    _gameView->showCard(prevTrayId, false);
    _gameView->setCardInteractive(prevTrayId, false);

    return kPrevTrayPos;
}

void StackController::_recordStackFlipUndo(int movedCardId, int prevTrayId, const cocos2d::Vec2& prevTrayPos)
{
    UndoRecord record;
    record.type = UndoType::STACK_FLIP;
    record.movedCardId = movedCardId;
    record.prevTrayCardId = prevTrayId;
    record.fromPosition = _gameView ? _gameView->getStackPosition() : cocos2d::Vec2::ZERO;
    record.prevTrayPosition = prevTrayPos;

    if (_undoManager)
    {
        _undoManager->pushRecord(record);
    }
}

void StackController::_applyTrayFlip(int cardId, CardModel* card)
{
    if (!_gameModel || !_gameView || !card)
    {
        return;
    }

    const cocos2d::Vec2 kTrayPos = _gameView->getTrayPosition();
    card->zone = CardZone::TRAY;
    card->position = kTrayPos;
    _gameModel->trayTopCardId = cardId;

    _gameView->placeCardInZone(cardId, CardZone::TRAY, _gameView->getStackPosition());
    _gameView->showCard(cardId, true);
    _gameView->moveCardTo(cardId, kTrayPos, kMoveDuration);
    _gameView->setCardInteractive(cardId, false);
    _gameView->setTrayTopCard(cardId);
}

void StackController::_refreshStackTop()
{
    if (!_gameModel || !_gameView)
    {
        return;
    }

    if (!_gameModel->stackCardIds.empty())
    {
        const int kNewTopId = _gameModel->stackCardIds.back();
        CardModel* newTopCard = _gameModel->getCardById(kNewTopId);
        if (newTopCard)
        {
            _gameView->placeCardInZone(kNewTopId, CardZone::STACK, _gameView->getStackPosition());
            _gameView->showCard(kNewTopId, true);
            _gameView->setStackTopCard(kNewTopId);
        }
    }
    else
    {
        _gameView->setStackTopCard(-1);
    }
}

} // namespace cardgame
