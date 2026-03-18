#ifndef CARD_MODEL_H
#define CARD_MODEL_H

#include "cocos2d.h"
#include "utils/CardTypes.h"
#include "json/document.h"

/**
 * @brief Runtime card data model.
 * @details Stores identity, suit/face, zone, and position for a single card.
 */
namespace cardgame {

class CardModel
{
public:
    /** @brief Default constructor. */
    CardModel() = default;

    /**
     * @brief Construct a card model with the given properties.
     * @param id Unique card id.
     * @param suit Suit enum value.
     * @param face Face enum value.
     * @param zone Card zone (playfield/stack/tray/discard).
     * @param position Current position in world space.
     */
    CardModel(int id, CardSuitType suit, CardFaceType face, CardZone zone, const cocos2d::Vec2& position);

    /**
     * @brief Serialize card to JSON value.
     * @param outValue Output JSON value.
     * @param allocator JSON allocator.
     */
    void toJson(rapidjson::Value& outValue, rapidjson::Document::AllocatorType& allocator) const;

    /**
     * @brief Deserialize card from JSON value.
     * @param value JSON value.
     * @return Parsed card model.
     */
    static CardModel fromJson(const rapidjson::Value& value);

    /** @brief Unique card id. */
    int id = -1;

    /** @brief Card suit (clubs/diamonds/hearts/spades). */
    CardSuitType suit = CST_NONE;

    /** @brief Card face (A..K). */
    CardFaceType face = CFT_NONE;

    /** @brief Current zone where the card resides. */
    CardZone zone = CardZone::PLAYFIELD;

    /** @brief Current position in world space. */
    cocos2d::Vec2 position;

    /** @brief Initial position for restoring the card on undo. */
    cocos2d::Vec2 originalPosition;
};

} // namespace cardgame

#endif // CARD_MODEL_H
