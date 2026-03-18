#ifndef PLAYFIELD_VIEW_H
#define PLAYFIELD_VIEW_H

#include <unordered_map>
#include "cocos2d.h"
#include "views/CardView.h"

/**
 * @brief View container for playfield cards.
 * @details Owns CardView instances placed on the table.
 */
namespace cardgame {

class PlayFieldView : public cocos2d::Node
{
public:
    /**
     * @brief Factory create method.
     * @return New PlayFieldView instance or nullptr on failure.
     */
    static PlayFieldView* create();

    /**
     * @brief Initialize the view.
     * @return true on success.
     */
    bool init() override;

    /**
     * @brief Add a card view to the playfield.
     * @param cardView Card view pointer (not owned).
     */
    void addCardView(CardView* cardView);

    /**
     * @brief Remove a card view by id.
     * @param cardId Card id to remove.
     */
    void removeCardView(int cardId);

    /**
     * @brief Get a card view by id.
     * @param cardId Card id.
     * @return Card view pointer or nullptr.
     */
    CardView* getCardView(int cardId) const;

private:
    /** @brief Map from card id to card view. */
    std::unordered_map<int, CardView*> _cardViews;
};

} // namespace cardgame

#endif // PLAYFIELD_VIEW_H
