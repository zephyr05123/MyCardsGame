#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include <string>
#include "utils/CardTypes.h"

/**
 * @brief Maps card suits/faces to resource filenames used by the UI.
 * @details Centralizes card asset paths for CardView rendering.
 */
namespace cardgame {

class CardResConfig
{
public:
    /**
     * @brief Get the background sprite file name for a card.
     * @return Relative path to the background image.
     */
    static std::string getCardBackgroundFile();

    /**
     * @brief Get the suit icon file name.
     * @param suit Suit enum value.
     * @return Relative path to the suit icon image.
     */
    static std::string getSuitIconFile(CardSuitType suit);

    /**
     * @brief Get the big number image file name for a suit/face.
     * @param suit Suit enum value.
     * @param face Face enum value.
     * @return Relative path to the big number image.
     */
    static std::string getBigNumberFile(CardSuitType suit, CardFaceType face);

private:
    /**
     * @brief Convert a face enum to its filename token.
     * @param face Face enum value.
     * @return Filename token string.
     */
    static std::string _getFaceToken(CardFaceType face);
};

} // namespace cardgame

#endif // CARD_RES_CONFIG_H
