#include "views/StackView.h"

namespace cardgame {

StackView* StackView::create()
{
    StackView* ret = new (std::nothrow) StackView();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool StackView::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
}

void StackView::setTopCardView(CardView* cardView, const cocos2d::Vec2& position)
{
    if (!cardView)
    {
        _topCardView = nullptr;
        return;
    }

    _topCardView = cardView;
    if (cardView->getParent() != this)
    {
        cardView->retain();
        cardView->removeFromParent();
        this->addChild(cardView);
        cardView->release();
    }
    cardView->setPosition(position);
}

CardView* StackView::getTopCardView() const
{
    return _topCardView;
}

} // namespace cardgame
