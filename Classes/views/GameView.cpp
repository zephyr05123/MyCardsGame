#include "views/GameView.h"

#include "views/CardView.h"

namespace cardgame {

namespace {

const float kDesignWidth = 1080.0f;
const float kDesignHeight = 2080.0f;
const float kStackHeight = 580.0f;
const float kPlayfieldHeight = 1500.0f;

} // namespace

GameView* GameView::create(const GameModel* model)
{
    GameView* ret = new (std::nothrow) GameView();
    if (ret && ret->init(model))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GameView::init(const GameModel* model)
{
    if (!Node::init())
    {
        return false;
    }

    _createLayout();
    _createCardViews(model);

    return true;
}

void GameView::_createLayout()
{
    _createBackgroundLayers();
    _createZoneViews();
    _createUndoButton();
}

void GameView::_createBackgroundLayers()
{
    // Background (dark gray, not pure black)
    auto background = cocos2d::LayerColor::create(cocos2d::Color4B(20, 20, 20, 255), kDesignWidth, kDesignHeight);
    this->addChild(background, 0);

    // Playfield area (brown)
    auto playfieldBg = cocos2d::LayerColor::create(cocos2d::Color4B(120, 80, 40, 255), kDesignWidth, kPlayfieldHeight);
    playfieldBg->setPosition(cocos2d::Vec2(0, kStackHeight));
    this->addChild(playfieldBg, 0);

    // Hand area (purple)
    auto handBg = cocos2d::LayerColor::create(cocos2d::Color4B(90, 60, 140, 255), kDesignWidth, kStackHeight);
    handBg->setPosition(cocos2d::Vec2(0, 0));
    this->addChild(handBg, 0);
}

void GameView::_createZoneViews()
{
    _playFieldView = PlayFieldView::create();
    _stackView = StackView::create();
    _trayView = TrayView::create();

    if (_playFieldView)
    {
        _playFieldView->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(_playFieldView, 1);
    }

    if (_stackView)
    {
        _stackView->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(_stackView, 2);
    }

    if (_trayView)
    {
        _trayView->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(_trayView, 2);
    }

    _stackPosition = cocos2d::Vec2(kDesignWidth * 0.25f, kStackHeight * 0.5f);
    _trayPosition = cocos2d::Vec2(kDesignWidth * 0.75f, kStackHeight * 0.5f);
}

void GameView::_createUndoButton()
{
    auto undoLabel = cocos2d::Label::createWithTTF("Undo", "fonts/Marker Felt.ttf", 32);
    auto undoItem = cocos2d::MenuItemLabel::create(undoLabel, [this](cocos2d::Ref*) {
        if (_onUndoClick)
        {
            _onUndoClick();
        }
    });
    undoItem->setPosition(cocos2d::Vec2(kDesignWidth * 0.92f, kStackHeight * 0.5f));

    _menu = cocos2d::Menu::create(undoItem, nullptr);
    _menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(_menu, 3);
}

void GameView::_createCardViews(const GameModel* model)
{
    if (!model)
    {
        return;
    }

    for (const CardModel& kCard : model->cards)
    {
        CardView* cardView = CardView::create(&kCard);
        if (!cardView)
        {
            continue;
        }

        cardView->setPosition(kCard.position);
        _cardViews[kCard.id] = cardView;
        _attachCardToZone(kCard, cardView);
    }
}

void GameView::_attachCardToZone(const CardModel& card, CardView* cardView)
{
    if (!cardView)
    {
        return;
    }

    switch (card.zone)
    {
    case CardZone::PLAYFIELD:
        if (_playFieldView)
        {
            _playFieldView->addCardView(cardView);
        }
        break;
    case CardZone::STACK:
        if (_stackView)
        {
            _stackView->addChild(cardView);
        }
        cardView->setVisible(false);
        cardView->setInteractive(false);
        break;
    case CardZone::TRAY:
        if (_trayView)
        {
            _trayView->addChild(cardView);
        }
        cardView->setInteractive(false);
        break;
    case CardZone::DISCARD:
        this->addChild(cardView);
        cardView->setVisible(false);
        cardView->setInteractive(false);
        break;
    }
}

void GameView::setOnPlayFieldCardClick(const std::function<void(int)>& callback)
{
    _onPlayFieldCardClick = callback;
    _refreshPlayFieldCallbacks();
}

void GameView::setOnStackClick(const std::function<void()>& callback)
{
    _onStackClick = callback;
    if (_stackTopCardId != -1)
    {
        CardView* cardView = getCardView(_stackTopCardId);
        if (cardView)
        {
            cardView->setOnClick([this](int) {
                if (_onStackClick)
                {
                    _onStackClick();
                }
            });
        }
    }
}

void GameView::setOnUndoClick(const std::function<void()>& callback)
{
    _onUndoClick = callback;
}

CardView* GameView::getCardView(int cardId) const
{
    auto it = _cardViews.find(cardId);
    if (it == _cardViews.end())
    {
        return nullptr;
    }
    return it->second;
}

void GameView::showCard(int cardId, bool visible)
{
    CardView* cardView = getCardView(cardId);
    if (cardView)
    {
        cardView->setVisible(visible);
    }
}

void GameView::setCardInteractive(int cardId, bool interactive)
{
    CardView* cardView = getCardView(cardId);
    if (cardView)
    {
        cardView->setInteractive(interactive);
    }
}

void GameView::bindPlayFieldCard(int cardId)
{
    CardView* cardView = getCardView(cardId);
    if (!cardView)
    {
        return;
    }

    cardView->setInteractive(true);
    cardView->setOnClick([this](int cardIdValue) {
        if (_onPlayFieldCardClick)
        {
            _onPlayFieldCardClick(cardIdValue);
        }
    });
}

void GameView::moveCardTo(int cardId, const cocos2d::Vec2& target, float duration)
{
    CardView* cardView = getCardView(cardId);
    if (cardView)
    {
        cardView->playMoveTo(target, duration);
    }
}

void GameView::placeCardInZone(int cardId, CardZone zone, const cocos2d::Vec2& position)
{
    CardView* cardView = getCardView(cardId);
    if (!cardView)
    {
        return;
    }

    cocos2d::Node* targetParent = this;
    if (zone == CardZone::PLAYFIELD)
    {
        targetParent = _playFieldView;
    }
    else if (zone == CardZone::STACK)
    {
        targetParent = _stackView;
    }
    else if (zone == CardZone::TRAY)
    {
        targetParent = _trayView;
    }

    if (!targetParent)
    {
        return;
    }

    if (cardView->getParent() != targetParent)
    {
        cardView->retain();
        cardView->removeFromParent();
        targetParent->addChild(cardView);
        cardView->release();
    }

    cardView->setPosition(position);
}

void GameView::setStackTopCard(int cardId)
{
    _stackTopCardId = cardId;

    if (_stackView)
    {
        auto children = _stackView->getChildren();
        for (cocos2d::Node* child : children)
        {
            auto cardView = dynamic_cast<CardView*>(child);
            if (cardView)
            {
                cardView->setVisible(false);
                cardView->setInteractive(false);
                cardView->setOnClick(std::function<void(int)>());
            }
        }
    }

    CardView* cardView = getCardView(cardId);
    if (cardView)
    {
        cardView->setVisible(true);
        cardView->setInteractive(true);
        cardView->setOnClick([this](int) {
            if (_onStackClick)
            {
                _onStackClick();
            }
        });
    }
}

void GameView::setTrayTopCard(int cardId)
{
    _trayTopCardId = cardId;
    CardView* cardView = getCardView(cardId);
    if (cardView)
    {
        cardView->setInteractive(false);
    }
}

cocos2d::Vec2 GameView::getTrayPosition() const
{
    return _trayPosition;
}

cocos2d::Vec2 GameView::getStackPosition() const
{
    return _stackPosition;
}

void GameView::_refreshPlayFieldCallbacks()
{
    if (!_playFieldView)
    {
        return;
    }

    auto children = _playFieldView->getChildren();
    for (cocos2d::Node* child : children)
    {
        auto cardView = dynamic_cast<CardView*>(child);
        if (cardView)
        {
            cardView->setInteractive(true);
            cardView->setOnClick([this](int cardId) {
                if (_onPlayFieldCardClick)
                {
                    _onPlayFieldCardClick(cardId);
                }
            });
        }
    }
}

} // namespace cardgame


