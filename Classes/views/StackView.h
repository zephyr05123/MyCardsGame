#ifndef STACK_VIEW_H
#define STACK_VIEW_H

#include "cocos2d.h"
#include "views/CardView.h"

/**
 * @brief View container for the stack top card.
 * @details Holds the visible draw pile card.
 */
namespace cardgame {

class StackView : public cocos2d::Node
{
public:
    /**
     * @brief Factory create method.
     * @return New StackView instance or nullptr on failure.
     */
    static StackView* create();

    /**
     * @brief Initialize the view.
     * @return true on success.
     */
    bool init() override;

    /**
     * @brief Set the top card view and position.
     * @param cardView Card view pointer (not owned).
     * @param position Desired position.
     */
    void setTopCardView(CardView* cardView, const cocos2d::Vec2& position);

    /**
     * @brief Get the current top card view.
     * @return Card view pointer or nullptr.
     */
    CardView* getTopCardView() const;

private:
    /** @brief Currently visible top card view. */
    CardView* _topCardView = nullptr;
};

} // namespace cardgame

#endif // STACK_VIEW_H
