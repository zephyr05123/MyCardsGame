#include "configs/loaders/LevelConfigLoader.h"

#include "cocos2d.h"
#include "json/document.h"

namespace cardgame {

namespace {

bool parseCardArray(const rapidjson::Value& arrayValue, std::vector<LevelCardConfig>& outCards)
{
    if (!arrayValue.IsArray())
    {
        return false;
    }

    outCards.clear();
    for (rapidjson::SizeType i = 0; i < arrayValue.Size(); ++i)
    {
        const rapidjson::Value& cardValue = arrayValue[i];
        if (!cardValue.IsObject())
        {
            return false;
        }

        if (!cardValue.HasMember("CardFace") || !cardValue.HasMember("CardSuit") || !cardValue.HasMember("Position"))
        {
            return false;
        }

        const rapidjson::Value& positionValue = cardValue["Position"];
        if (!positionValue.IsObject() || !positionValue.HasMember("x") || !positionValue.HasMember("y"))
        {
            return false;
        }

        LevelCardConfig cfg;
        cfg.cardFace = cardValue["CardFace"].GetInt();
        cfg.cardSuit = cardValue["CardSuit"].GetInt();
        cfg.position = cocos2d::Vec2(positionValue["x"].GetFloat(), positionValue["y"].GetFloat());
        outCards.push_back(cfg);
    }

    return true;
}

} // namespace

bool LevelConfigLoader::loadFromFile(const std::string& filePath, LevelConfig& outConfig)
{
    std::string jsonText = cocos2d::FileUtils::getInstance()->getStringFromFile(filePath);
    if (jsonText.empty())
    {
        return false;
    }

    rapidjson::Document doc;
    doc.Parse(jsonText.c_str());
    if (doc.HasParseError() || !doc.IsObject())
    {
        return false;
    }

    if (!doc.HasMember("Playfield") || !doc.HasMember("Stack"))
    {
        return false;
    }

    if (!parseCardArray(doc["Playfield"], outConfig.playfield))
    {
        return false;
    }

    if (!parseCardArray(doc["Stack"], outConfig.stack))
    {
        return false;
    }

    return true;
}

} // namespace cardgame

