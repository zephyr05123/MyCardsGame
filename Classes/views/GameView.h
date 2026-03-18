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
 * @brief Root view for the game.
 * @details Manages playfield, stack, tray, and UI controls.
 */
namespace cardgame {

class GameView : public cocos2d::Node
{
public:
    /**
     * @brief Factory create method.
     * @param model Game model pointer (not owned).
     * @return New GameView instance or nullptr on failure.
     */
    static GameView* create(const GameModel* model);

    /**
     * @brief Initialize the game view.
     * @param model Game model pointer (not owned).
     * @return true on success.
     */
    bool init(const GameModel* model);

    /**
     * @brief Set callback for playfield card clicks.
     * @param callback Callback receiving card id.
     */
    void setOnPlayFieldCardClick(const std::function<void(int)>& callback);

    /**
     * @brief Set callback for stack click.
     * @param callback Callback invoked on stack click.
     */
    void setOnStackClick(const std::function<void()>& callback);

    /**
     * @brief Set callback for undo button.
     * @param callback Callback invoked on undo click.
     */
    void setOnUndoClick(const std::function<void()>& callback);

    /**
     * @brief Get a card view by id.
     * @param cardId Card id.
     * @return Card view pointer or nullptr.
     */
    CardView* getCardView(int cardId) const;

    /**
     * @brief Show or hide a card view.
     * @param cardId Card id.
     * @param visible Visibility flag.
     */
    void showCard(int cardId, bool visible);

    /**
     * @brief Enable or disable card interaction.
     * @param cardId Card id.
     * @param interactive True to enable input.
     */
    void setCardInteractive(int cardId, bool interactive);

    /**
     * @brief Bind playfield click handling for a specific card.
     * @param cardId Card id.
     */
    void bindPlayFieldCard(int cardId);

    /**
     * @brief Animate a card view to a target position.
     * @param cardId Card id.
     * @param target Target position.
     * @param duration Animation duration in seconds.
     */
    void moveCardTo(int cardId, const cocos2d::Vec2& target, float duration);

    /**
     * @brief Place a card view into a specific zone parent and position.
     * @param cardId Card id.
     * @param zone Target zone.
     * @param position Target position.
     */
    void placeCardInZone(int cardId, CardZone zone, const cocos2d::Vec2& position);

    /**
     * @brief Set which card is the visible stack top.
     * @param cardId Card id.
     */
    void setStackTopCard(int cardId);

    /**
     * @brief Set which card is the visible tray top.
     * @param cardId Card id.
     */
    void setTrayTopCard(int cardId);

    /**
     * @brief Get the tray top position.
     * @return Tray position.
     */
    cocos2d::Vec2 getTrayPosition() const;

    /**
     * @brief Get the stack top position.
     * @return Stack position.
     */
    cocos2d::Vec2 getStackPosition() const;

private:
    /** @brief Build background layers and container layout. */
    void _createLayout();

    /** @brief Instantiate card views for all cards in the model. */
    void _createCardViews(const GameModel* model);

    /** @brief Attach a card view to the correct zone parent. */
    void _attachCardToZone(const CardModel& card, CardView* cardView);

    /** @brief Refresh playfield callbacks after changes. */
    void _refreshPlayFieldCallbacks();

    /** @brief Create background color layers. */
    void _createBackgroundLayers();

    /** @brief Create playfield, stack, and tray subviews. */
    void _createZoneViews();

    /** @brief Create undo UI button. */
    void _createUndoButton();

    /** @brief Playfield container view. */
    PlayFieldView* _playFieldView = nullptr;

    /** @brief Stack container view. */
    StackView* _stackView = nullptr;

    /** @brief Tray container view. */
    TrayView* _trayView = nullptr;

    /** @brief Menu node for UI buttons. */
    cocos2d::Menu* _menu = nullptr;

    /** @brief Card id to view map. */
    std::unordered_map<int, CardView*> _cardViews;

    /** @brief Playfield click callback. */
    std::function<void(int)> _onPlayFieldCardClick;

    /** @brief Stack click callback. */
    std::function<void()> _onStackClick;

    /** @brief Undo click callback. */
    std::function<void()> _onUndoClick;

    /** @brief Current stack top card id. */
    int _stackTopCardId = -1;

    /** @brief Current tray top card id. */
    int _trayTopCardId = -1;

    /** @brief Tray position in world space. */
    cocos2d::Vec2 _trayPosition;

    /** @brief Stack position in world space. */
    cocos2d::Vec2 _stackPosition;
};

} // namespace cardgame

#endif // GAME_VIEW_H

