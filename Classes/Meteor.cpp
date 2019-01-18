
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "meteor.h"
#include "Definition.h"
#include "ModelObject.h"
USING_NS_CC;
using namespace cocos2d;

Meteor::Meteor()
{
}

Meteor::Meteor(Scene *scene)
{
	mSprite = Sprite::create(__IMAGE_METEOR__);
	this->SetAlive(false);
	mSprite->setScale(random(0.2, 0.8));
	mSpeedX = random(2, 7);
	mSpeedY = random(3, 10);
	scene->addChild(mSprite);
}

void Meteor::Init()
{
	this->SetAlive(true);
	mPosX = random(- mSprite->getContentSize().width,
		__WIDTH_SIZE__ + mSprite->getContentSize().width / 2);
	mPosY = __HEIGHT__SIZE__;

	this->SetPosition(Vec2(mPosX, mPosY));
}

void Meteor::Update()
{
	if (IsAlive())
	{
		if (mPosX <= mSprite->getContentSize().width)
		{
			mSprite->setPosition(Vec2(GetPosition().x + mSpeedX, GetPosition().y - mSpeedY));
		}
		else if (mPosX >= mSprite->getContentSize().width)
		{
			mSprite->setPosition(Vec2(GetPosition().x - mSpeedX, GetPosition().y - mSpeedY));
		}
	}

	if (GetPosition().y < -mSprite->getContentSize().height)
	{
		SetAlive(false);
	}
}

cocos2d::Rect Meteor::GetBoundingBox()
{
	return mSprite->getBoundingBox();
}


