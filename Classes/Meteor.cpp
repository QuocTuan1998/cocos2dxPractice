
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "meteor.h"
USING_NS_CC;
using namespace cocos2d;

Meteor::Meteor()
{
}

Meteor::Meteor(Scene *scene)
{
	mSprite = Sprite::create(IMAGE_METEOR);
	this->SetAlive(false);
	mSprite->setScale(random(METEOR_SCALE_MIN, METEOR_SCALE_MAX));
	mSpeedX = random(METEOR_SPEED_X_MIN, METEOR_SPEED_X_MAX);
	mSpeedY = random(METEOR_SPEED_Y_MIN, METEOR_SPEED_Y_MIN);
	scene->addChild(mSprite, 1);
}

void Meteor::Init()
{
	this->SetAlive(true);
	mPosX = random(- mSprite->getContentSize().width,
		WIDTH_SIZE + mSprite->getContentSize().width / 2);
	mPosY = HEIGHT_SIZE;

	float duration = random(METEOR_ROTATE_DURATION_MIN, METEOR_ROTATE_DURATION_MAX);
	int angle = random(METEOR_ROTATE_MIN, METEOR_ROTATE_MAX);
	auto rotate = RotateBy::create(duration, angle);
	mSprite->runAction(RepeatForever::create(rotate));

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


