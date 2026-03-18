#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <functional>
#include <unordered_map>
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/PlayFieldView.h"
#include "views/StackView.h"
#include "views/TrayView.h"

/**
 * @brief Root view for the game, holds playfield/stack/tray views.
 */
namespace cardgame {

class GameView : public cocos2d::Node
{
public:
    static GameView* create(const GameModel* model);
    bool init(const GameModel* model);

    void setOnPlayFieldCardClick(const std::function<void(int)>& callback);
    void setOnStackClick(const std::function<void()>& callback);
    void setOnUndoClick(const std::function<void()>& callback);

    CardView* getCardView(int cardId) const;
    void showCard(int cardId, bool visible);
    void setCardInteractive(int cardId, bool interactive);
    void bindPlayFieldCard(int cardId);

    void moveCardTo(int cardId, const cocos2d::Vec2& target, float duration);

    void placeCardInZone(int cardId, CardZone zone, const cocos2d::Vec2& position);

    void setStackTopCard(int cardId);
    void setTrayTopCard(int cardId);
    cocos2d::Vec2 getTrayPosition() const;
    cocos2d::Vec2 getStackPosition() const;

private:
    void createLayout();
    void createCardViews(const GameModel* model);
    void refreshPlayFieldCallbacks();

    PlayFieldView* _playFieldView = nullptr;
    StackView* _stackView = nullptr;
    TrayView* _trayView = nullptr;

    cocos2d::Menu* _menu = nullptr;
    std::unordered_map<int, CardView*> _cardViews;
    std::function<void(int)> _onPlayFieldCardClick;
    std::function<void()> _onStackClick;
    std::function<void()> _onUndoClick;

    int _stackTopCardId = -1;
    int _trayTopCardId = -1;

    cocos2d::Vec2 _trayPosition;
    cocos2d::Vec2 _stackPosition;
};

} // namespace cardgame

#endif // GAME_VIEW_H

