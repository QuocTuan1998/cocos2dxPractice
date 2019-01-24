
#include "SimpleAudioEngine.h"
#include "Land.h"
#include "Definition.h"
USING_NS_CC;
using namespace cocos2d;
Land::Land()
{
	
}

Land::Land(cocos2d::Scene * scene)
{
	mSprite = Sprite::create(IMAGE_LAND);
	setAlive(false);
	mCountLand = 0;
	mBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(0, 1, 0));
	mBody->setCollisionBitmask(2);
	mBody->setContactTestBitmask(true);
	mBody->setGravityEnable(false);
	mBody->setDynamic(false);

	mSprite->setPhysicsBody(mBody);
	scene->addChild(mSprite);
}


void Land::Init()
{
	setAlive(true);
	mCountLand ++;
	float posX = random(0, WIDTH_SIZE) + mSprite->getContentSize().width / 2;
	float posy = random(100, HEIGHT_SIZE) + (mSprite->getContentSize().height) * mCountLand + HEIGHT_SIZE;
	SetPosition(Vec2(posX, posy));
}

void Land::Update()
{
	if (mSprite->getPosition().y <= 0)
	{
		setAlive(false);
	}
	else
	{
		mSprite->setPositionY(GetPosition().y - 1);
	}

}

Land::~Land()
{
}
