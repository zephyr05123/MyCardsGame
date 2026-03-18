#include "views/CardView.h"

#include "configs/models/CardResConfig.h"

namespace cardgame {

CardView* CardView::create(const CardModel* model)
{
    CardView* ret = new (std::nothrow) CardView();
    if (ret && ret->init(model))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool CardView::init(const CardModel* model)
{
    if (!Node::init())
    {
        return false;
    }

    _model = model;
    _cardId = model ? model->id : -1;

    _background = cocos2d::Sprite::create(CardResConfig::getCardBackgroundFile());
    if (_background)
    {
        this->addChild(_background);
        this->setContentSize(_background->getContentSize());
    }

    refreshVisuals(model);
    setupTouch();

    return true;
}

void CardView::setupTouch()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (!_interactive || !this->isVisible())
        {
            return false;
        }
        if (!this->getParent())
        {
            return false;
        }
        const cocos2d::Vec2 location = this->getParent()->convertToNodeSpace(touch->getLocation());
        if (this->getBoundingBox().containsPoint(location))
        {
            if (_onClick)
            {
                _onClick(_cardId);
            }
            return true;
        }
        return false;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void CardView::setOnClick(const std::function<void(int)>& callback)
{
    _onClick = callback;
}

void CardView::setInteractive(bool enabled)
{
    _interactive = enabled;
}

void CardView::playMoveTo(const cocos2d::Vec2& target, float duration)
{
    this->stopAllActions();
    auto move = cocos2d::MoveTo::create(duration, target);
    this->runAction(move);
}

void CardView::refreshVisuals(const CardModel* model)
{
    if (!model)
    {
        return;
    }

    if (_numberSprite)
    {
        _numberSprite->removeFromParent();
        _numberSprite = nullptr;
    }

    if (_suitSprite)
    {
        _suitSprite->removeFromParent();
        _suitSprite = nullptr;
    }

    const cocos2d::Size cardSize = _background ? _background->getContentSize() : this->getContentSize();

    const std::string numberFile = CardResConfig::getBigNumberFile(model->suit, model->face);
    if (!numberFile.empty())
    {
        _numberSprite = cocos2d::Sprite::create(numberFile);
        if (_numberSprite)
        {
            const cocos2d::Size numSize = _numberSprite->getContentSize();
            const float targetW = cardSize.width * 0.5f;
            const float targetH = cardSize.height * 0.5f;
            const float scaleW = targetW / numSize.width;
            const float scaleH = targetH / numSize.height;
            _numberSprite->setScale(std::min(scaleW, scaleH));
            _numberSprite->setPosition(cocos2d::Vec2(cardSize.width * 0.00f, cardSize.height * 0.00f));
            this->addChild(_numberSprite);
        }
    }

    const std::string suitFile = CardResConfig::getSuitIconFile(model->suit);
    if (!suitFile.empty())
    {
        _suitSprite = cocos2d::Sprite::create(suitFile);
        if (_suitSprite)
        {
            const cocos2d::Size suitSize = _suitSprite->getContentSize();
            const float targetW = cardSize.width * 0.22f;
            const float targetH = cardSize.height * 0.22f;
            const float scaleW = targetW / suitSize.width;
            const float scaleH = targetH / suitSize.height;
            _suitSprite->setScale(std::min(scaleW, scaleH));
            _suitSprite->setPosition(cocos2d::Vec2(cardSize.width * 0.27f, cardSize.height * 0.27f));
            this->addChild(_suitSprite);
        }
    }
}

int CardView::getCardId() const
{
    return _cardId;
}

} // namespace cardgame





