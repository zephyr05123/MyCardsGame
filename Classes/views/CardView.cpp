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
    _setupTouch();

    return true;
}

void CardView::_setupTouch()
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
        const cocos2d::Vec2 kLocation = this->getParent()->convertToNodeSpace(touch->getLocation());
        if (this->getBoundingBox().containsPoint(kLocation))
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

    const cocos2d::Size kCardSize = _background ? _background->getContentSize() : this->getContentSize();

    const std::string kNumberFile = CardResConfig::getBigNumberFile(model->suit, model->face);
    if (!kNumberFile.empty())
    {
        _numberSprite = cocos2d::Sprite::create(kNumberFile);
        if (_numberSprite)
        {
            const cocos2d::Size kNumSize = _numberSprite->getContentSize();
            const float kTargetW = kCardSize.width * 0.5f;
            const float kTargetH = kCardSize.height * 0.5f;
            const float kScaleW = kTargetW / kNumSize.width;
            const float kScaleH = kTargetH / kNumSize.height;
            _numberSprite->setScale(std::min(kScaleW, kScaleH));
            _numberSprite->setPosition(cocos2d::Vec2(kCardSize.width * 0.00f, kCardSize.height * 0.00f));
            this->addChild(_numberSprite);
        }
    }

    const std::string kSuitFile = CardResConfig::getSuitIconFile(model->suit);
    if (!kSuitFile.empty())
    {
        _suitSprite = cocos2d::Sprite::create(kSuitFile);
        if (_suitSprite)
        {
            const cocos2d::Size kSuitSize = _suitSprite->getContentSize();
            const float kTargetW = kCardSize.width * 0.22f;
            const float kTargetH = kCardSize.height * 0.22f;
            const float kScaleW = kTargetW / kSuitSize.width;
            const float kScaleH = kTargetH / kSuitSize.height;
            _suitSprite->setScale(std::min(kScaleW, kScaleH));
            _suitSprite->setPosition(cocos2d::Vec2(kCardSize.width * 0.27f, kCardSize.height * 0.27f));
            this->addChild(_suitSprite);
        }
    }
}

int CardView::getCardId() const
{
    return _cardId;
}

} // namespace cardgame
