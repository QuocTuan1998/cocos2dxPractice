

#ifndef __BIRDS_H__
#define __BIRDS_H__

#include "cocos2d.h"

using namespace cocos2d;
class Birds 
{
private:
	Sprite * mBird;
	SpriteFrameCache * mFrame;
	SpriteBatchNode * mBatchNode;
	Animation * mAnimate;
	Spawn * mSpawn;
	Birds();
public:
	Birds(Scene *scene);
	
	void setAnimation();
	void move();

	~Birds();

};

#endif // __BIRDS_H__
