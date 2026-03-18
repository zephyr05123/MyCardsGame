#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include <string>
#include "utils/CardTypes.h"

/**
 * @brief Maps card suits/faces to resource filenames.
 */
namespace cardgame {

class CardResConfig
{
public:
    static std::string getCardBackgroundFile();
    static std::string getSuitIconFile(CardSuitType suit);
    static std::string getBigNumberFile(CardSuitType suit, CardFaceType face);

private:
    static std::string getFaceToken(CardFaceType face);
};

} // namespace cardgame

#endif // CARD_RES_CONFIG_H
