#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    _gameController.reset(new cardgame::GameController());
    if (!_gameController->init(this))
    {
        return false;
    }

    return true;
}
