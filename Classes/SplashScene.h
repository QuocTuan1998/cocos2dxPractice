
#ifndef __SPLAH_SCENE_H__
#define __SPLAH_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void goToMenuScene(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif // __SPLAH_SCENE_H__
