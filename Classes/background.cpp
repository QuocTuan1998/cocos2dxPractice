
#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "ModelObject.h"
#include "background.h"
USING_NS_CC;

using namespace cocos2d;

Background::Background()
{

}

Background::Background(cocos2d::Scene * scene)
{
	mBackgroundAbove = Sprite::create(IMAGE_BACKGROUND_STAR);
	mBackgroundAbove->setAnchorPoint(Vec2(0, 0));
	mSprite = Sprite::create(IMAGE_BACKGROUND_STAR);
	mSprite->setAnchorPoint(Vec2(0, 0));
	mSprite->setPosition(Vec2(0, HEIGHT_SIZE));

	scene->addChild(mBackgroundAbove, 0);
	scene->addChild(mSprite, 0);
}

void Background::Init()
{
	auto backgroundAction = MoveBy::create(TIME_SCROLL_BACKGROUND, Vec2(0, -HEIGHT_SIZE));
	auto backgroundAction2 = MoveBy::create(TIME_SCROLL_BACKGROUND, Vec2(0, -HEIGHT_SIZE));
	
	mBackgroundAbove->runAction(RepeatForever::create(backgroundAction));
	mSprite->runAction(RepeatForever::create(backgroundAction2));
}

void Background::Update()
{
	if (mBackgroundAbove->getPosition().y <= -HEIGHT_SIZE)
	{
		mBackgroundAbove->setPosition(0, HEIGHT_SIZE);
	}

	if (mSprite->getPosition().y <= -HEIGHT_SIZE)
	{
		mSprite->setPosition(0, HEIGHT_SIZE);
	}
}

Background::~Background()
{
}
