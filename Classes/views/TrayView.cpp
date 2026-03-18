#include "views/TrayView.h"

namespace cardgame {

TrayView* TrayView::create()
{
    TrayView* ret = new (std::nothrow) TrayView();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool TrayView::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
}

void TrayView::setTopCardView(CardView* cardView, const cocos2d::Vec2& position)
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

CardView* TrayView::getTopCardView() const
{
    return _topCardView;
}

} // namespace cardgame
