#include "configs/models/CardResConfig.h"

namespace cardgame {

std::string CardResConfig::getCardBackgroundFile()
{
    return "card_general.png";
}

std::string CardResConfig::getSuitIconFile(CardSuitType suit)
{
    switch (suit)
    {
    case CST_CLUBS:
        return "suits/club.png";
    case CST_DIAMONDS:
        return "suits/diamond.png";
    case CST_HEARTS:
        return "suits/heart.png";
    case CST_SPADES:
        return "suits/spade.png";
    default:
        return "";
    }
}

std::string CardResConfig::getBigNumberFile(CardSuitType suit, CardFaceType face)
{
    const bool kIsRed = isRedSuit(suit);
    const std::string kColor = kIsRed ? "red" : "black";
    return "number/big_" + kColor + "_" + _getFaceToken(face) + ".png";
}

std::string CardResConfig::_getFaceToken(CardFaceType face)
{
    switch (face)
    {
    case CFT_ACE:
        return "A";
    case CFT_TWO:
        return "2";
    case CFT_THREE:
        return "3";
    case CFT_FOUR:
        return "4";
    case CFT_FIVE:
        return "5";
    case CFT_SIX:
        return "6";
    case CFT_SEVEN:
        return "7";
    case CFT_EIGHT:
        return "8";
    case CFT_NINE:
        return "9";
    case CFT_TEN:
        return "10";
    case CFT_JACK:
        return "J";
    case CFT_QUEEN:
        return "Q";
    case CFT_KING:
        return "K";
    default:
        return "";
    }
}

} // namespace cardgame

