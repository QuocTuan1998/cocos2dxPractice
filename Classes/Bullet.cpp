
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"
USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;
Bullet::Bullet()
{

}

Bullet::Bullet(cocos2d::Scene *scene, int who)
{
	mSprite = Sprite::create();
	this->SetAlive(false);
	mWho = who;
	
	if (who == BULLET_SHIP)
	{
		mSprite->setTexture(IMAGE_BULLET_SHIP);
	}
	else if (who == BULLET_ENEMY)
	{
		mSprite->setTexture(IMAGE_BULLET_ENEMY);
	}

	scene->addChild(mSprite, 1);

	//mAudio = SimpleAudioEngine::getInstance();

}

void Bullet::Init()
{
	this->SetAlive(true);
	//mAudio->playEffect(SOUND_BULLET_SHIP, false, 1.0f, 1.0f, 1.0f);
	mBulletSpeed = random(BULLET_ENEMY_SPEED_MIN, BULLET_ENEMY_SPEED_MAX);
}

void Bullet::Update()
{
	if (mWho == BULLET_SHIP) 
	{
		if (IsAlive())
		{
			
			this->SetPosition(this->GetPosition() + Vec2(0, BULLET_SHIP_SPEED));

		}

		if (this->GetPosition().y >= HEIGHT_SIZE)
		{
			
			this->SetAlive(false);
		}
	}
	else if(mWho == BULLET_ENEMY)
	{
		if (IsAlive())
		{
			this->SetPosition(this->GetPosition() - Vec2(0, mBulletSpeed));
		}

		if (this->GetPosition().y <= 0)
		{
			this->SetAlive(false);
		}
	}
}

Rect Bullet::GetBoundingBox()
{
	return mSprite->getBoundingBox();
}
