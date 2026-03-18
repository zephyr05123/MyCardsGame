#include "models/GameModel.h"

#include "json/stringbuffer.h"
#include "json/writer.h"

namespace cardgame {

int GameModel::addCard(const CardModel& card)
{
    cards.push_back(card);
    _idToIndex[card.id] = cards.size() - 1;
    return card.id;
}

CardModel* GameModel::getCardById(int id)
{
    auto it = _idToIndex.find(id);
    if (it == _idToIndex.end())
    {
        return nullptr;
    }
    return &cards[it->second];
}

const CardModel* GameModel::getCardById(int id) const
{
    auto it = _idToIndex.find(id);
    if (it == _idToIndex.end())
    {
        return nullptr;
    }
    return &cards.at(it->second);
}

void GameModel::removePlayfieldCard(int cardId)
{
    for (auto it = playfieldCardIds.begin(); it != playfieldCardIds.end(); ++it)
    {
        if (*it == cardId)
        {
            playfieldCardIds.erase(it);
            return;
        }
    }
}

void GameModel::addPlayfieldCard(int cardId)
{
    for (int existingId : playfieldCardIds)
    {
        if (existingId == cardId)
        {
            return;
        }
    }
    playfieldCardIds.push_back(cardId);
}

std::string GameModel::serializeToJsonString() const
{
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("trayTopCardId", trayTopCardId, allocator);

    rapidjson::Value cardsValue(rapidjson::kArrayType);
    for (const CardModel& card : cards)
    {
        rapidjson::Value cardValue;
        card.toJson(cardValue, allocator);
        cardsValue.PushBack(cardValue, allocator);
    }
    doc.AddMember("cards", cardsValue, allocator);

    rapidjson::Value playfieldValue(rapidjson::kArrayType);
    for (int id : playfieldCardIds)
    {
        playfieldValue.PushBack(id, allocator);
    }
    doc.AddMember("playfield", playfieldValue, allocator);

    rapidjson::Value stackValue(rapidjson::kArrayType);
    for (int id : stackCardIds)
    {
        stackValue.PushBack(id, allocator);
    }
    doc.AddMember("stack", stackValue, allocator);

    rapidjson::Value discardValue(rapidjson::kArrayType);
    for (int id : discardCardIds)
    {
        discardValue.PushBack(id, allocator);
    }
    doc.AddMember("discard", discardValue, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    return buffer.GetString();
}

bool GameModel::deserializeFromJsonString(const std::string& jsonText)
{
    rapidjson::Document doc;
    doc.Parse(jsonText.c_str());
    if (doc.HasParseError() || !doc.IsObject())
    {
        return false;
    }

    if (!doc.HasMember("cards") || !doc["cards"].IsArray())
    {
        return false;
    }

    cards.clear();
    playfieldCardIds.clear();
    stackCardIds.clear();
    discardCardIds.clear();
    _idToIndex.clear();

    trayTopCardId = doc.HasMember("trayTopCardId") ? doc["trayTopCardId"].GetInt() : -1;

    const rapidjson::Value& cardsValue = doc["cards"];
    for (rapidjson::SizeType i = 0; i < cardsValue.Size(); ++i)
    {
        CardModel card = CardModel::fromJson(cardsValue[i]);
        addCard(card);
    }

    if (doc.HasMember("playfield") && doc["playfield"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < doc["playfield"].Size(); ++i)
        {
            playfieldCardIds.push_back(doc["playfield"][i].GetInt());
        }
    }

    if (doc.HasMember("stack") && doc["stack"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < doc["stack"].Size(); ++i)
        {
            stackCardIds.push_back(doc["stack"][i].GetInt());
        }
    }

    if (doc.HasMember("discard") && doc["discard"].IsArray())
    {
        for (rapidjson::SizeType i = 0; i < doc["discard"].Size(); ++i)
        {
            discardCardIds.push_back(doc["discard"][i].GetInt());
        }
    }

    return true;
}

void GameModel::rebuildIdMap()
{
    _idToIndex.clear();
    for (size_t i = 0; i < cards.size(); ++i)
    {
        _idToIndex[cards[i].id] = i;
    }
}

} // namespace cardgame

