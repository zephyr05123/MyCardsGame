#include "views/PlayFieldView.h"

namespace cardgame {

PlayFieldView* PlayFieldView::create()
{
    PlayFieldView* ret = new (std::nothrow) PlayFieldView();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool PlayFieldView::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
}

void PlayFieldView::addCardView(CardView* cardView)
{
    if (!cardView)
    {
        return;
    }
    const int cardId = cardView->getCardId();
    _cardViews[cardId] = cardView;
    this->addChild(cardView);
}

void PlayFieldView::removeCardView(int cardId)
{
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end())
    {
        it->second->removeFromParent();
        _cardViews.erase(it);
    }
}

CardView* PlayFieldView::getCardView(int cardId) const
{
    auto it = _cardViews.find(cardId);
    if (it == _cardViews.end())
    {
        return nullptr;
    }
    return it->second;
}

} // namespace cardgame
