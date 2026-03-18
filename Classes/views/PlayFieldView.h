#ifndef PLAYFIELD_VIEW_H
#define PLAYFIELD_VIEW_H

#include <unordered_map>
#include "cocos2d.h"
#include "views/CardView.h"

/**
 * @brief View container for playfield cards.
 */
namespace cardgame {

class PlayFieldView : public cocos2d::Node
{
public:
    static PlayFieldView* create();
    bool init() override;

    void addCardView(CardView* cardView);
    void removeCardView(int cardId);
    CardView* getCardView(int cardId) const;

private:
    std::unordered_map<int, CardView*> _cardViews;
};

} // namespace cardgame

#endif // PLAYFIELD_VIEW_H
