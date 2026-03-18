#include "services/GameModelFromLevelGenerator.h"

namespace cardgame {

std::unique_ptr<GameModel> GameModelFromLevelGenerator::generate(const LevelConfig& config)
{
    std::unique_ptr<GameModel> model(new GameModel());

    const float kPlayFieldOffsetY = 580.0f;

    int nextId = 1;
    // Playfield cards
    for (const LevelCardConfig& cardCfg : config.playfield)
    {
        cocos2d::Vec2 pos = cardCfg.position;
        pos.y += kPlayFieldOffsetY;
        CardModel card(nextId++, static_cast<CardSuitType>(cardCfg.cardSuit),
            static_cast<CardFaceType>(cardCfg.cardFace), CardZone::PLAYFIELD, pos);
        model->addCard(card);
        model->playfieldCardIds.push_back(card.id);
    }

    // Stack cards
    for (const LevelCardConfig& cardCfg : config.stack)
    {
        CardModel card(nextId++, static_cast<CardSuitType>(cardCfg.cardSuit),
            static_cast<CardFaceType>(cardCfg.cardFace), CardZone::STACK, cardCfg.position);
        model->addCard(card);
        model->stackCardIds.push_back(card.id);
    }

    return model;
}

} // namespace cardgame
