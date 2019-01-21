
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy()
{
}

Enemy::Enemy(cocos2d::Scene * scene)
{
	mSprite = Sprite::create(IMAGE_ENEMY_SHIP);
	this->SetAlive(false);
	mSpeed = random(ENEMY_SPEED_MIN, ENEMY_SPEED_MAX);
	this->mScene = scene;
	scene->addChild(mSprite, 1);
	this->GenerateBullet();
}

void Enemy::GenerateBullet()
{
	for (int i = 0; i < NUM_OF_BULLET_ENEMY; i++)
	{
		Bullet *bullet = new Bullet(mScene, BULLET_ENEMY);
		mListBullet.push_back(bullet);
	}
}

std::vector<Bullet*> Enemy::getBulletEnemy()
{
	return mListBullet;
}

void Enemy::Shoot()
{
	mCountBullet++;

	if (mCountBullet % 30 == 0)
	{
		for (int i = 0; i < mListBullet.size(); i++)
		{
			if (!mListBullet.at(i)->IsAlive())
			{
				mListBullet.at(i)->Init();
				mListBullet.at(i)->SetPosition(GetPosition() - Vec2(0, mBulletSpeed));
				break;
			}
		}
	}
}

void Enemy::ReduceHealth()
{
	mHealth--;
}

int Enemy::GetHealth()
{
	return mHealth;
}

cocos2d::Rect Enemy::GetBoundingBox()
{
	return mSprite->getBoundingBox();
}

void Enemy::Init()
{
	mSprite->setScale(random(ENEMY_SCALE_MIN, ENEMY_SCALE_MAX));
	mHealth = ENEMY_HEALTH_MAX * mSprite->getScaleX();
	mBulletSpeed = random(BULLET_ENEMY_SPEED_MIN, BULLET_ENEMY_SPEED_MAX);
	int posX = random(mSprite->getContentSize().width / 2, 
		WIDTH_SIZE - mSprite->getContentSize().width / 2
	);

	float duration = random(ENEMY_MOVE_DURATION_MIN, ENEMY_MOVE_DURATION_MAX);
	auto moveTo = MoveTo::create(duration, Vec2(posX + mSprite->getContentSize().width / 2, HEIGHT_SIZE));

	mSprite->runAction(moveTo);

	mSprite->setPosition(Vec2(posX, HEIGHT_SIZE));

	this->SetAlive(true);
}

void Enemy::Update()
{
	Shoot();

	for (int i = 0; i < mListBullet.size(); i++)
	{
		mListBullet.at(i)->Update();
	}

	if (IsAlive())
	{
		mSprite->setPosition(GetPosition() - Vec2(0, mSpeed));
	}

	if (GetPosition().y < -mSprite->getContentSize().height)
	{
		SetAlive(false);
	}

}

Enemy::~Enemy()
{
}
