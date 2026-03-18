#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <memory>
#include "cocos2d.h"
#include "controllers/GameController.h"

/**
 * @brief Main game scene.
 * @details Owns the GameController and hosts the GameView.
 */
class GameScene : public cocos2d::Scene
{
public:
    /**
     * @brief Create the game scene.
     * @return New scene instance.
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief Initialize the scene.
     * @return true on success.
     */
    virtual bool init();

    CREATE_FUNC(GameScene);

private:
    /** @brief Game controller instance. */
    std::unique_ptr<cardgame::GameController> _gameController;
};

#endif // GAME_SCENE_H
