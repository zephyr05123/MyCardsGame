#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <unordered_map>
#include <vector>
#include <string>
#include "models/CardModel.h"
#include "json/document.h"

/**
 * @brief Runtime game model for the current level.
 * @details Owns all card data and zone lists.
 */
namespace cardgame {

class GameModel
{
public:
    /** @brief Default constructor. */
    GameModel() = default;

    /**
     * @brief Add a card to the model and return its assigned id.
     * @param card Card to add.
     * @return Assigned card id.
     */
    int addCard(const CardModel& card);

    /**
     * @brief Get a mutable card by id.
     * @param id Card id.
     * @return Pointer to card or nullptr if missing.
     */
    CardModel* getCardById(int id);

    /**
     * @brief Get a const card by id.
     * @param id Card id.
     * @return Pointer to card or nullptr if missing.
     */
    const CardModel* getCardById(int id) const;

    /**
     * @brief Remove a card id from the playfield list.
     * @param cardId Card id to remove.
     */
    void removePlayfieldCard(int cardId);

    /**
     * @brief Add a card id to the playfield list if not present.
     * @param cardId Card id to add.
     */
    void addPlayfieldCard(int cardId);

    /**
     * @brief Serialize the model to a JSON string.
     * @return JSON text representing the model.
     */
    std::string serializeToJsonString() const;

    /**
     * @brief Deserialize model state from JSON.
     * @param jsonText JSON text.
     * @return true if parsing succeeds.
     */
    bool deserializeFromJsonString(const std::string& jsonText);

    /** @brief All cards in the level. */
    std::vector<CardModel> cards;

    /** @brief Card ids currently on the playfield. */
    std::vector<int> playfieldCardIds;

    /** @brief Card ids remaining in the stack. */
    std::vector<int> stackCardIds;

    /** @brief Card ids moved to discard. */
    std::vector<int> discardCardIds;

    /** @brief Current tray top card id. */
    int trayTopCardId = -1;

private:
    /** @brief Rebuild the id-to-index map after mutations. */
    void _rebuildIdMap();

    /** @brief Map from card id to index in cards vector. */
    std::unordered_map<int, size_t> _idToIndex;
};

} // namespace cardgame

#endif // GAME_MODEL_H
