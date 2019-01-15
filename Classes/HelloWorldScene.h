
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d; // do not forget  namespace and library

class HelloWorld : public cocos2d::Scene
{
private:
	Size mVisibleSize;
	TMXTiledMap *mTileMap;
	TMXLayer *mBackground;
	Sprite *mPlayer;
	TMXLayer *mMeta;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void setViewPointCenter(Point point);

	// player move in direction the user taps
	void registerWithTouchDispatcher();

	void setPlayerPosition(Point position);

	bool touchBegan(Touch *touch, Event *event);

	void touchEnded(Touch *touch, Event *event);

	Point tileCoordForPosition(Point position);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
