#ifndef CARD_MODEL_H
#define CARD_MODEL_H

#include "cocos2d.h"
#include "utils/CardTypes.h"
#include "json/document.h"

/**
 * @brief Runtime card data model.
 */
namespace cardgame {

class CardModel
{
public:
    CardModel() = default;
    CardModel(int id, CardSuitType suit, CardFaceType face, CardZone zone, const cocos2d::Vec2& position);

    /**
     * @brief Serialize card to JSON value.
     */
    void toJson(rapidjson::Value& outValue, rapidjson::Document::AllocatorType& allocator) const;

    /**
     * @brief Deserialize card from JSON value.
     */
    static CardModel fromJson(const rapidjson::Value& value);

    int id = -1;
    CardSuitType suit = CST_NONE;
    CardFaceType face = CFT_NONE;
    CardZone zone = CardZone::PLAYFIELD;
    cocos2d::Vec2 position;
    cocos2d::Vec2 originalPosition;
};

} // namespace cardgame

#endif // CARD_MODEL_H

