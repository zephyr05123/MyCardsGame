#include "controllers/GameController.h"

#include "configs/loaders/LevelConfigLoader.h"
#include "services/GameModelFromLevelGenerator.h"

namespace cardgame {

namespace {

const float kMoveDuration = 0.2f;

} // namespace

bool GameController::init(cocos2d::Node* parent)
{
    if (!parent)
    {
        return false;
    }

    LevelConfig levelConfig;
    if (!LevelConfigLoader::loadFromFile("level_1.json", levelConfig))
    {
        return false;
    }

    _gameModel = GameModelFromLevelGenerator::generate(levelConfig);
    _undoModel.reset(new UndoModel());
    _undoManager.reset(new UndoManager(_undoModel.get()));

    _gameView = GameView::create(_gameModel.get());
    if (!_gameView)
    {
        return false;
    }
    parent->addChild(_gameView, 1);

    _playFieldController.reset(new PlayFieldController());
    _playFieldController->init(_gameModel.get(), _gameView, _undoManager.get());

    _stackController.reset(new StackController());
    _stackController->init(_gameModel.get(), _gameView, _undoManager.get());

    _gameView->setOnPlayFieldCardClick([this](int cardId) {
        if (_playFieldController)
        {
            _playFieldController->handleCardClick(cardId);
        }
    });

    _gameView->setOnStackClick([this]() {
        if (_stackController)
        {
            _stackController->handleStackClick();
        }
    });

    _gameView->setOnUndoClick([this]() {
        _handleUndo();
    });

    _initTrayAndStack();

    return true;
}

void GameController::_initTrayAndStack()
{
    if (!_gameModel || !_gameView)
    {
        return;
    }

    if (!_gameModel->stackCardIds.empty())
    {
        const int kTrayId = _gameModel->stackCardIds.back();
        _gameModel->stackCardIds.pop_back();
        CardModel* trayCard = _gameModel->getCardById(kTrayId);
        if (trayCard)
        {
            trayCard->zone = CardZone::TRAY;
            trayCard->position = _gameView->getTrayPosition();
            _gameModel->trayTopCardId = kTrayId;

            _gameView->placeCardInZone(kTrayId, CardZone::TRAY, trayCard->position);
            _gameView->showCard(kTrayId, true);
            _gameView->setTrayTopCard(kTrayId);
        }
    }

    if (!_gameModel->stackCardIds.empty())
    {
        const int kTopId = _gameModel->stackCardIds.back();
        CardModel* topCard = _gameModel->getCardById(kTopId);
        if (topCard)
        {
            topCard->zone = CardZone::STACK;
            topCard->position = _gameView->getStackPosition();
            _gameView->placeCardInZone(kTopId, CardZone::STACK, topCard->position);
            _gameView->showCard(kTopId, true);
            _gameView->setStackTopCard(kTopId);
        }
    }
    else
    {
        _gameView->setStackTopCard(-1);
    }
}

void GameController::_removeDiscardId(int cardId)
{
    if (!_gameModel)
    {
        return;
    }

    auto& list = _gameModel->discardCardIds;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        if (*it == cardId)
        {
            list.erase(it);
            return;
        }
    }
}

void GameController::_removeStackId(int cardId)
{
    if (!_gameModel)
    {
        return;
    }

    auto& list = _gameModel->stackCardIds;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        if (*it == cardId)
        {
            list.erase(it);
            return;
        }
    }
}

void GameController::_handleUndo()
{
    if (!_undoManager || !_undoManager->canUndo() || !_gameModel || !_gameView)
    {
        return;
    }

    UndoRecord record;
    if (!_undoManager->popRecord(record))
    {
        return;
    }

    CardModel* movedCard = _gameModel->getCardById(record.movedCardId);
    CardModel* prevTrayCard = _gameModel->getCardById(record.prevTrayCardId);
    if (!movedCard)
    {
        return;
    }

    if (record.type == UndoType::MATCH)
    {
        if (!prevTrayCard)
        {
            return;
        }
        _applyMatchUndo(record, movedCard, prevTrayCard);
    }
    else if (record.type == UndoType::STACK_FLIP)
    {
        _applyStackFlipUndo(record, movedCard, prevTrayCard);
    }

    _rebindPlayFieldCallbacks();
}

void GameController::_applyMatchUndo(const UndoRecord& record, CardModel* movedCard, CardModel* prevTrayCard)
{
    if (!_gameModel || !_gameView || !movedCard || !prevTrayCard)
    {
        return;
    }

    const cocos2d::Vec2 kFromPos = record.fromPosition;
    const cocos2d::Vec2 kTrayPos = _gameView->getTrayPosition();

    movedCard->zone = CardZone::PLAYFIELD;
    movedCard->position = kFromPos;
    _gameModel->addPlayfieldCard(movedCard->id);

    prevTrayCard->zone = CardZone::TRAY;
    prevTrayCard->position = record.prevTrayPosition;
    _gameModel->trayTopCardId = prevTrayCard->id;
    _removeDiscardId(prevTrayCard->id);

    _gameView->placeCardInZone(movedCard->id, CardZone::PLAYFIELD, kTrayPos);
    _gameView->showCard(movedCard->id, true);
    _gameView->moveCardTo(movedCard->id, kFromPos, kMoveDuration);
    _gameView->setCardInteractive(movedCard->id, true);

    _gameView->placeCardInZone(prevTrayCard->id, CardZone::TRAY, prevTrayCard->position);
    _gameView->showCard(prevTrayCard->id, true);
    _gameView->moveCardTo(prevTrayCard->id, prevTrayCard->position, kMoveDuration);
    _gameView->setTrayTopCard(prevTrayCard->id);
}

void GameController::_applyStackFlipUndo(const UndoRecord& record, CardModel* movedCard, CardModel* prevTrayCard)
{
    if (!_gameModel || !_gameView || !movedCard)
    {
        return;
    }

    if (movedCard->zone != CardZone::TRAY)
    {
        return;
    }

    const cocos2d::Vec2 kFromPos = record.fromPosition;
    const cocos2d::Vec2 kTrayPos = _gameView->getTrayPosition();

    movedCard->zone = CardZone::STACK;
    movedCard->position = kFromPos;
    _gameModel->stackCardIds.push_back(movedCard->id);

    _gameView->placeCardInZone(movedCard->id, CardZone::STACK, kTrayPos);
    _gameView->showCard(movedCard->id, true);
    _gameView->moveCardTo(movedCard->id, kFromPos, kMoveDuration);
    _gameView->setStackTopCard(movedCard->id);

    if (prevTrayCard)
    {
        prevTrayCard->zone = CardZone::TRAY;
        prevTrayCard->position = record.prevTrayPosition;
        _gameModel->trayTopCardId = prevTrayCard->id;
        _removeDiscardId(prevTrayCard->id);

        _gameView->placeCardInZone(prevTrayCard->id, CardZone::TRAY, prevTrayCard->position);
        _gameView->showCard(prevTrayCard->id, true);
        _gameView->setTrayTopCard(prevTrayCard->id);
    }
    else
    {
        _gameModel->trayTopCardId = -1;
    }
}

void GameController::_rebindPlayFieldCallbacks()
{
    if (!_gameView || !_playFieldController)
    {
        return;
    }

    _gameView->setOnPlayFieldCardClick([this](int cardId) {
        if (_playFieldController)
        {
            _playFieldController->handleCardClick(cardId);
        }
    });
}

} // namespace cardgame

