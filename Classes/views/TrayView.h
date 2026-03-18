#ifndef TRAY_VIEW_H
#define TRAY_VIEW_H

#include "cocos2d.h"
#include "views/CardView.h"

/**
 * @brief View container for tray top card.
 */
namespace cardgame {

class TrayView : public cocos2d::Node
{
public:
    static TrayView* create();
    bool init() override;

    void setTopCardView(CardView* cardView, const cocos2d::Vec2& position);
    CardView* getTopCardView() const;

private:
    CardView* _topCardView = nullptr;
};

} // namespace cardgame

#endif // TRAY_VIEW_H
