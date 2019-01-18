
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"
#include "Definition.h"
USING_NS_CC;
using namespace cocos2d;

Bullet::Bullet()
{

}

Bullet::Bullet(cocos2d::Scene *scene)
{
	mSprite = Sprite::create(__IMAGE_BULLET__);
	this->SetAlive(false);
	scene->addChild(mSprite, 0);
}

void Bullet::Init()
{
	this->SetAlive(true);
}

void Bullet::Update()
{
	if (IsAlive())
	{
		this->SetPosition(this->GetPosition() + Vec2(0, __BULLET_SPEED__));
	}

	if (this->GetPosition().y >= __HEIGHT__SIZE__)
	{
		this->SetAlive(false);
	}
}

Rect Bullet::GetBoundingBox()
{
	return mSprite->getBoundingBox();
}
