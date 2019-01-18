
#ifndef __GAMOVER_SCENE_H__
#define __GAMOVER_SCENE_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
};

#endif // __GAMOVER_SCENE_H__
