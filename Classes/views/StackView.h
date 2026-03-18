#ifndef STACK_VIEW_H
#define STACK_VIEW_H

#include "cocos2d.h"
#include "views/CardView.h"

/**
 * @brief View container for stack top card.
 */
namespace cardgame {

class StackView : public cocos2d::Node
{
public:
    static StackView* create();
    bool init() override;

    void setTopCardView(CardView* cardView, const cocos2d::Vec2& position);
    CardView* getTopCardView() const;

private:
    CardView* _topCardView = nullptr;
};

} // namespace cardgame

#endif // STACK_VIEW_H
