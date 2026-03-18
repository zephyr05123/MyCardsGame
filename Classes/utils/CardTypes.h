#ifndef CARD_TYPES_H
#define CARD_TYPES_H

/**
 * @brief Card enums and helpers shared across models/services/views.
 */
namespace cardgame {

/** @brief Suit enum values used by card assets and rules. */
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS = 0,     // Clubs
    CST_DIAMONDS = 1,  // Diamonds
    CST_HEARTS = 2,    // Hearts
    CST_SPADES = 3,    // Spades
    CST_NUM_CARD_SUIT_TYPES
};

/** @brief Face enum values from Ace to King. */
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

/** @brief Logical zone for where a card currently resides. */
enum class CardZone
{
    PLAYFIELD = 0,
    STACK,
    TRAY,
    DISCARD
};

/**
 * @brief Check whether a suit is red.
 * @param suit Suit enum value.
 * @return true if the suit is diamonds or hearts.
 */
inline bool isRedSuit(CardSuitType suit)
{
    return suit == CST_DIAMONDS || suit == CST_HEARTS;
}

} // namespace cardgame

#endif // CARD_TYPES_H
