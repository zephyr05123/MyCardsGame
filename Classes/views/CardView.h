#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#include <functional>
#include "cocos2d.h"
#include "models/CardModel.h"

/**
 * @brief Visual representation of a card, with click handling.
 */
namespace cardgame {

class CardView : public cocos2d::Node
{
public:
    static CardView* create(const CardModel* model);

    bool init(const CardModel* model);

    void setOnClick(const std::function<void(int)>& callback);
    void setInteractive(bool enabled);

    void playMoveTo(const cocos2d::Vec2& target, float duration);

    void refreshVisuals(const CardModel* model);

    int getCardId() const;

private:
    void setupTouch();

    int _cardId = -1;
    bool _interactive = true;
    const CardModel* _model = nullptr;
    std::function<void(int)> _onClick;

    cocos2d::Sprite* _background = nullptr;
    cocos2d::Sprite* _numberSprite = nullptr;
    cocos2d::Sprite* _suitSprite = nullptr;
};

} // namespace cardgame

#endif // CARD_VIEW_H
