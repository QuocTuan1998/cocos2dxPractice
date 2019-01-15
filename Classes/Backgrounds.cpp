
#include "Backgrounds.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "definition.h"
#include <string>

USING_NS_CC;
using namespace std;
using namespace cocos2d;

Backgrounds::Backgrounds()
{

}

Backgrounds::Backgrounds(Scene * scene, string frameName, string nodeName, string spriteName)
{
	mFrame = SpriteFrameCache::getInstance();
	mFrame->addSpriteFramesWithFile(frameName);
	mBatchNode = SpriteBatchNode::create(nodeName);
	mSprite = Sprite::createWithSpriteFrameName(spriteName);
	scene->addChild(mBatchNode);
}

SpriteBatchNode * Backgrounds::getBatchNode()
{
	return this->mBatchNode;
}

Sprite * Backgrounds::getSprite()
{
	return this->mSprite;
}

Sprite * Backgrounds::addSprite(string spriteName, Vec2 vec)
{
	auto tmpSprite = Sprite::createWithSpriteFrameName(spriteName);
	tmpSprite->setAnchorPoint(Vec2(0, 0));
	tmpSprite->setPosition(vec);

	return tmpSprite;
}



Backgrounds::~Backgrounds()
{

}
