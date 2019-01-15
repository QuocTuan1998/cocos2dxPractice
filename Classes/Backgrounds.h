

#ifndef __BACKGROUNDS_H__
#define __BACKGROUNDS_H__

#include "cocos2d.h"
#include <string>
using namespace cocos2d;
using namespace std;

class Backgrounds
{
private:
	Sprite * mSprite;
	SpriteFrameCache * mFrame;
	SpriteBatchNode * mBatchNode;
	Backgrounds();
public:
	Backgrounds(Scene *scene, string frameName, string nodeName, string spriteName);

	SpriteBatchNode* getBatchNode();

	Sprite * getSprite();

	Sprite * addSprite(string spriteName, Vec2 vec);

	~Backgrounds();

};

#endif // __BIRDS_H__
