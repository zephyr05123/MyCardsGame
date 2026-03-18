#include "models/CardModel.h"

namespace cardgame {

CardModel::CardModel(int idValue, CardSuitType suitValue, CardFaceType faceValue, CardZone zoneValue, const cocos2d::Vec2& positionValue)
    : id(idValue)
    , suit(suitValue)
    , face(faceValue)
    , zone(zoneValue)
    , position(positionValue)
    , originalPosition(positionValue)
{
}

void CardModel::toJson(rapidjson::Value& outValue, rapidjson::Document::AllocatorType& allocator) const
{
    outValue.SetObject();
    outValue.AddMember("id", id, allocator);
    outValue.AddMember("suit", static_cast<int>(suit), allocator);
    outValue.AddMember("face", static_cast<int>(face), allocator);
    outValue.AddMember("zone", static_cast<int>(zone), allocator);

    rapidjson::Value posValue(rapidjson::kObjectType);
    posValue.AddMember("x", position.x, allocator);
    posValue.AddMember("y", position.y, allocator);
    outValue.AddMember("position", posValue, allocator);

    rapidjson::Value originValue(rapidjson::kObjectType);
    originValue.AddMember("x", originalPosition.x, allocator);
    originValue.AddMember("y", originalPosition.y, allocator);
    outValue.AddMember("origin", originValue, allocator);
}

CardModel CardModel::fromJson(const rapidjson::Value& value)
{
    CardModel model;
    model.id = value["id"].GetInt();
    model.suit = static_cast<CardSuitType>(value["suit"].GetInt());
    model.face = static_cast<CardFaceType>(value["face"].GetInt());
    model.zone = static_cast<CardZone>(value["zone"].GetInt());

    const rapidjson::Value& kPosValue = value["position"];
    model.position = cocos2d::Vec2(kPosValue["x"].GetFloat(), kPosValue["y"].GetFloat());

    const rapidjson::Value& kOriginValue = value["origin"];
    model.originalPosition = cocos2d::Vec2(kOriginValue["x"].GetFloat(), kOriginValue["y"].GetFloat());

    return model;
}

} // namespace cardgame
