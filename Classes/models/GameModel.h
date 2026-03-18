#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <unordered_map>
#include <vector>
#include <string>
#include "models/CardModel.h"
#include "json/document.h"

/**
 * @brief Runtime game model for the current level.
 */
namespace cardgame {

class GameModel
{
public:
    GameModel() = default;

    /**
     * @brief Add a card and return its assigned id.
     */
    int addCard(const CardModel& card);

    /**
     * @brief Access card by id.
     */
    CardModel* getCardById(int id);
    const CardModel* getCardById(int id) const;

    /**
     * @brief Remove a card id from the playfield list.
     */
    void removePlayfieldCard(int cardId);

    /**
     * @brief Add a card id to the playfield list if not present.
     */
    void addPlayfieldCard(int cardId);

    /**
     * @brief Serialize game model to JSON string.
     */
    std::string serializeToJsonString() const;

    /**
     * @brief Deserialize game model from JSON string.
     */
    bool deserializeFromJsonString(const std::string& jsonText);

    std::vector<CardModel> cards;
    std::vector<int> playfieldCardIds;
    std::vector<int> stackCardIds;
    std::vector<int> discardCardIds;

    int trayTopCardId = -1;

private:
    void rebuildIdMap();
    std::unordered_map<int, size_t> _idToIndex;
};

} // namespace cardgame

#endif // GAME_MODEL_H

