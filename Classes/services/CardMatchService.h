#ifndef CARD_MATCH_SERVICE_H
#define CARD_MATCH_SERVICE_H

#include "utils/CardTypes.h"

/**
 * @brief Stateless service that checks card match rules.
 */
namespace cardgame {

class CardMatchService
{
public:
    /**
     * @brief Check if two faces match with A-K wrap.
     */
    static bool isMatch(CardFaceType a, CardFaceType b);
};

} // namespace cardgame

#endif // CARD_MATCH_SERVICE_H
