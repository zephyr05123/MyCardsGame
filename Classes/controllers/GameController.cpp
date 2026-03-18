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
        handleUndo();
    });

    initTrayAndStack();

    return true;
}

void GameController::initTrayAndStack()
{
    if (!_gameModel || !_gameView)
    {
        return;
    }

    if (!_gameModel->stackCardIds.empty())
    {
        const int trayId = _gameModel->stackCardIds.back();
        _gameModel->stackCardIds.pop_back();
        CardModel* trayCard = _gameModel->getCardById(trayId);
        if (trayCard)
        {
            trayCard->zone = CardZone::TRAY;
            trayCard->position = _gameView->getTrayPosition();
            _gameModel->trayTopCardId = trayId;

            _gameView->placeCardInZone(trayId, CardZone::TRAY, trayCard->position);
            _gameView->showCard(trayId, true);
            _gameView->setTrayTopCard(trayId);
        }
    }

    if (!_gameModel->stackCardIds.empty())
    {
        const int topId = _gameModel->stackCardIds.back();
        CardModel* topCard = _gameModel->getCardById(topId);
        if (topCard)
        {
            topCard->zone = CardZone::STACK;
            topCard->position = _gameView->getStackPosition();
            _gameView->placeCardInZone(topId, CardZone::STACK, topCard->position);
            _gameView->showCard(topId, true);
            _gameView->setStackTopCard(topId);
        }
    }
    else
    {
        _gameView->setStackTopCard(-1);
    }
}

void GameController::removeDiscardId(int cardId)
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

void GameController::removeStackId(int cardId)
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

void GameController::handleUndo()
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

    const cocos2d::Vec2 fromPos = record.fromPosition;
    const cocos2d::Vec2 trayPos = _gameView->getTrayPosition();

    if (record.type == UndoType::MATCH)
    {
        if (!prevTrayCard)
        {
            return;
        }

        movedCard->zone = CardZone::PLAYFIELD;
        movedCard->position = fromPos;
        _gameModel->addPlayfieldCard(movedCard->id);

        prevTrayCard->zone = CardZone::TRAY;
        prevTrayCard->position = record.prevTrayPosition;
        _gameModel->trayTopCardId = prevTrayCard->id;
        removeDiscardId(prevTrayCard->id);

        _gameView->placeCardInZone(movedCard->id, CardZone::PLAYFIELD, trayPos);
        _gameView->showCard(movedCard->id, true);
        _gameView->moveCardTo(movedCard->id, fromPos, kMoveDuration);
        _gameView->setCardInteractive(movedCard->id, true);

        _gameView->placeCardInZone(prevTrayCard->id, CardZone::TRAY, prevTrayCard->position);
        _gameView->showCard(prevTrayCard->id, true);
        _gameView->moveCardTo(prevTrayCard->id, prevTrayCard->position, kMoveDuration);
        _gameView->setTrayTopCard(prevTrayCard->id);
    }
    else if (record.type == UndoType::STACK_FLIP)
    {
        // Move current tray card back to stack top.
        if (movedCard->zone != CardZone::TRAY)
        {
            return;
        }

        movedCard->zone = CardZone::STACK;
        movedCard->position = fromPos;
        _gameModel->stackCardIds.push_back(movedCard->id);

        _gameView->placeCardInZone(movedCard->id, CardZone::STACK, trayPos);
        _gameView->showCard(movedCard->id, true);
        _gameView->moveCardTo(movedCard->id, fromPos, kMoveDuration);
        _gameView->setStackTopCard(movedCard->id);

        if (prevTrayCard)
        {
            prevTrayCard->zone = CardZone::TRAY;
            prevTrayCard->position = record.prevTrayPosition;
            _gameModel->trayTopCardId = prevTrayCard->id;
            removeDiscardId(prevTrayCard->id);

            _gameView->placeCardInZone(prevTrayCard->id, CardZone::TRAY, prevTrayCard->position);
            _gameView->showCard(prevTrayCard->id, true);
            _gameView->setTrayTopCard(prevTrayCard->id);
        }
        else
        {
            _gameModel->trayTopCardId = -1;
        }
    }

    // Re-bind callbacks for playfield cards.
    _gameView->setOnPlayFieldCardClick([this](int cardId) {
        if (_playFieldController)
        {
            _playFieldController->handleCardClick(cardId);
        }
    });
}

} // namespace cardgame







