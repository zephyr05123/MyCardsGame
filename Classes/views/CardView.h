#ifndef CARD_VIEW_H
#define CARD_VIEW_H

#include <functional>
#include "cocos2d.h"
#include "models/CardModel.h"

/**
 * @brief Visual representation of a card with click handling.
 * @details Owns background, number, and suit sprites.
 */
namespace cardgame {

class CardView : public cocos2d::Node
{
public:
    /**
     * @brief Factory create method.
     * @param model Card model pointer (not owned).
     * @return New CardView instance or nullptr on failure.
     */
    static CardView* create(const CardModel* model);

    /**
     * @brief Initialize the card view with a model.
     * @param model Card model pointer (not owned).
     * @return true on success.
     */
    bool init(const CardModel* model);

    /**
     * @brief Set the click callback for this card.
     * @param callback Callback receiving the card id.
     */
    void setOnClick(const std::function<void(int)>& callback);

    /**
     * @brief Enable or disable touch interaction.
     * @param enabled True to enable input.
     */
    void setInteractive(bool enabled);

    /**
     * @brief Play a MoveTo animation to the target position.
     * @param target Target position.
     * @param duration Animation duration in seconds.
     */
    void playMoveTo(const cocos2d::Vec2& target, float duration);

    /**
     * @brief Refresh the card visuals based on model data.
     * @param model Card model pointer (not owned).
     */
    void refreshVisuals(const CardModel* model);

    /**
     * @brief Get the card id for this view.
     * @return Card id.
     */
    int getCardId() const;

private:
    /** @brief Register touch listeners for this card. */
    void _setupTouch();

    /** @brief Card id associated with this view. */
    int _cardId = -1;

    /** @brief Whether the card accepts input. */
    bool _interactive = true;

    /** @brief Card model pointer (not owned). */
    const CardModel* _model = nullptr;

    /** @brief Click callback. */
    std::function<void(int)> _onClick;

    /** @brief Background sprite. */
    cocos2d::Sprite* _background = nullptr;

    /** @brief Large number sprite. */
    cocos2d::Sprite* _numberSprite = nullptr;

    /** @brief Suit icon sprite. */
    cocos2d::Sprite* _suitSprite = nullptr;
};

} // namespace cardgame

#endif // CARD_VIEW_H
