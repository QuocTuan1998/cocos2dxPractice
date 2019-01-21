
#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "Item.h"
USING_NS_CC;

Item::Item()
{
}

Item::Item(cocos2d::Scene *scene)
{
	mSprite = Sprite::create();
	SetAlive(false);
	scene->addChild(mSprite);
}

void Item::Init()
{
	SetAlive(true);
	mType = random(1, 2);
	if (mType == 1)
	{
		mSprite->setTexture(IMAGE_HEALTH);
	}
	else if (mType == 2)
	{
		mSprite->setTexture(IMAGE_SHEILD);
	}

	int posX = random(mSprite->getContentSize().width, WIDTH_SIZE - mSprite->getContentSize().width);
	SetPosition(Vec2(posX, HEIGHT_SIZE));	


}

void Item::Update()
{
	//auto action = MoveTo::create(3, Vec2())
}

Item::~Item()
{
}
