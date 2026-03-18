#ifndef CARD_TYPES_H
#define CARD_TYPES_H

/**
 * @brief Card enums and helpers shared across models/services/views.
 */
namespace cardgame {

enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS = 0,     // Clubs
    CST_DIAMONDS = 1,  // Diamonds
    CST_HEARTS = 2,    // Hearts
    CST_SPADES = 3,    // Spades
    CST_NUM_CARD_SUIT_TYPES
};

enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE = 0,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

enum class CardZone
{
    PLAYFIELD = 0,
    STACK,
    TRAY,
    DISCARD
};

inline bool isRedSuit(CardSuitType suit)
{
    return suit == CST_DIAMONDS || suit == CST_HEARTS;
}

} // namespace cardgame

#endif // CARD_TYPES_H
