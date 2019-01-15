
#include "Birds.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "definition.h"

USING_NS_CC;
using std::string;
using namespace cocos2d;

Birds::Birds()
{

}

Birds::Birds(Scene *scene)
{
	mFrame = SpriteFrameCache::getInstance();
	mFrame->addSpriteFramesWithFile(__BIRD_LIST__);
	mBatchNode = SpriteBatchNode::create(__BIRD_PNG__);

	mBatchNode->setPosition(Vec2(0, 250));
	mBird = Sprite::createWithSpriteFrameName("bird(1).png");
	mAnimate = Animation::create();
	this->setAnimation();
	
	mSpawn = Spawn::create(Animate::create(mAnimate), nullptr);	
	mBird->runAction(RepeatForever::create(mSpawn));
	mBatchNode->addChild(mBird);

	scene->addChild(mBatchNode);
}

void Birds::setAnimation()
{
	for (int i = 1; i <= 5; i++)
	{
		char name[100] = { 0 };
		sprintf(name, "bird(%d).png", i);
		mAnimate->addSpriteFrame(mFrame->spriteFrameByName(name));
	}
	mAnimate->setDelayPerUnit(0.1f);
}

void Birds::move()
{
	mBird->setPosition(Vec2(mBird->getPositionX() + 0.1, mBird->getPositionY()));
}

Birds::~Birds()
{
}

