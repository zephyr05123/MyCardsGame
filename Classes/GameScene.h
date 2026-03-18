#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <memory>
#include "cocos2d.h"
#include "controllers/GameController.h"

/**
 * @brief Main game scene.
 */
class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

private:
    std::unique_ptr<cardgame::GameController> _gameController;
};

#endif // GAME_SCENE_H

