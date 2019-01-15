

#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"

class Home : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    



    // implement the "static create()" method manually
    CREATE_FUNC(Home);
};

#endif // __HOME_SCENE_H__
