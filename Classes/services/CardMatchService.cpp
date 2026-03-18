#include "services/CardMatchService.h"

namespace cardgame {

bool CardMatchService::isMatch(CardFaceType a, CardFaceType b)
{
    if (a == CFT_NONE || b == CFT_NONE)
    {
        return false;
    }

    const int ia = static_cast<int>(a);
    const int ib = static_cast<int>(b);
    const int diff = ia - ib;
    if (diff == 1 || diff == -1)
    {
        return true;
    }

    // A-K wrap around
    if ((a == CFT_ACE && b == CFT_KING) || (a == CFT_KING && b == CFT_ACE))
    {
        return true;
    }

    return false;
}

} // namespace cardgame
