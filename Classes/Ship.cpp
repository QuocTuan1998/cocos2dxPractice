
#include "GamePlayScene.h"
#include "Definition.h"
#include "Ship.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace cocos2d;

Ship::Ship()
{

}

Ship::Ship(Scene *scene)
{
	mSprite = Sprite::create(IMAGE_SPACE_SHIP);
	this->SetAlive(true);
	mSprite->setPositionX(WIDTH_SIZE / 2);
	mScore = 0;
	mHealth = HEALTH_PLAYER_SHIP;
	this->mScene = scene;
	scene->addChild(mSprite, 1);
	this->GenerateBullet();
	InitEvent(scene);
}

void Ship::GenerateBullet()
{
	for (int i = 0; i < NUM_OF_BULLET_SHIP; i++)
	{
		Bullet *bullet = new Bullet(mScene, BULLET_SHIP);
		mListBullet.push_back(bullet);
	}
}

void Ship::Init()
{
	auto moveTo = MoveTo::create(PLAYER_SHIP_DURATION, 
		Vec2(WIDTH_SIZE / 2, HEIGHT_SIZE / 3));
	mSprite->runAction(moveTo);

	mBGAttacked = Sprite::create(IMAGE_BACKGROUND_ATTACKED);
	mBGAttacked->setAnchorPoint(Vec2(0, 0));
	mScene->addChild(mBGAttacked);
	mBGAttacked->setVisible(false);
}

void Ship::Update()
{
	Shoot();
	for (int i = 0; i < mListBullet.size(); i++)
	{
		mListBullet.at(i)->Update();
	}

	GameOver();
}

void Ship::Shoot()
{
	mCountBullet++;
	if (mCountBullet % NUM_OF_BULLET_FRAME_SHIP == 0)
	{
		for (int i = 0; i < mListBullet.size(); i++)
		{
			if (!mListBullet.at(i)->IsAlive())
			{
				mListBullet.at(i)->Init();
				mListBullet.at(i)->SetPosition(GetPosition() + Vec2(0, mSprite->getContentSize().height / 2));
				break;
			}
		}
	}
}

void Ship::ShipAttacked()
{
	auto callbackAttacked = CallFunc::create([=]() {
		mBGAttacked->setVisible(true);
	});
	
	auto callbackRemove = CallFunc::create([=]() {
		mBGAttacked->setVisible(false);
	});

	auto attackedTime = DelayTime::create(TIME_DELAY_SHIP_ATTACKED);
	auto seqDamaged = Sequence::create(callbackAttacked, attackedTime, callbackRemove, nullptr);
	mSprite->runAction(seqDamaged);
	mHealth--;
}

cocos2d::Vector<cocos2d::SpriteFrame*> Ship::GetAnimFrames(const char * format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	cocos2d::Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}

void Ship::HandleCollisionWithMeteor(std::vector<Meteor*> meteors)
{
	/*	Collision bullet ship --- meteor	*/
	for (int i = 0; i < NUM_OF_BULLET_SHIP; i++)
	{
		for (int j = 0; j < NUM_OF_METEOR; j++)
		{
			Bullet *bullet = mListBullet.at(i);
			Meteor *meteor = meteors.at(j);
			if (meteor->IsAlive() && bullet->IsAlive())
			{
				if (bullet->GetBoundingBox().intersectsRect(meteor->GetBoundingBox()))
				{
					bullet->SetAlive(false);
					meteor->SetAlive(false);
				}
			}
		}
	}

	/*	Collision ship---meteor	*/
	for (int i = 0; i < NUM_OF_METEOR; i++)
	{
		Meteor *meteor = meteors.at(i);
		if (meteor->IsAlive() && IsAlive())
		{
			if (meteor->GetBoundingBox().intersectsRect(mSprite->getBoundingBox()))
			{
				ShipAttacked();
				meteor->SetAlive(false);
			}
		}
	}
}

void Ship::HandleCollisionWithEnemy(std::vector<Enemy*> enemies)
{
	/*	bullet ship		----	enemy*/
	for (int i = 0; i < NUM_OF_BULLET_SHIP; i++)
	{
		for (int j = 0; j < NUM_OF_ENEMY; j++)
		{
			Bullet *bullet = mListBullet.at(i);
			Enemy *enemy = enemies.at(j);
			if (enemy->IsAlive() && bullet->IsAlive())
			{
				if (bullet->GetBoundingBox().intersectsRect(enemy->GetBoundingBox()))
				{
					bullet->SetAlive(false);
					enemy->ReduceHealth();

					if (enemy->GetHealth() <= 0)
					{
						enemy->SetAlive(false);
						EnemyExplosion(enemy->GetPosition());
					}
					
					mScore++;
				}
			}
		}
	}
	/*	player ship		----	enemy ship*/
	for (int j = 0; j < NUM_OF_ENEMY; j++)
	{
		Enemy *enemy = enemies.at(j);
		if (enemy->IsAlive() && IsAlive())
		{
			if (enemy->GetBoundingBox().intersectsRect(mSprite->getBoundingBox()))
			{
				ShipAttacked();
				enemy->SetAlive(false);
				EnemyExplosion(enemy->GetPosition());
				mHealth -= enemy->GetHealth();
			}
		}
	}
}

void Ship::HandleCollisionWithBulletEnemy(std::vector<Bullet*> bullets)
{
	/*	bullet enemy ----	ship*/
	for (int j = 0; j < NUM_OF_BULLET_ENEMY; j++)
	{
		Bullet *bullet = bullets.at(j);
		if (IsAlive() && bullet->IsAlive())
		{
			if (bullet->GetBoundingBox().intersectsRect(mSprite->getBoundingBox()))
			{
				ShipAttacked();
				bullet->SetAlive(false);
				mHealth--;
				mScore--;
			}
		}
	}
}

void Ship::EnemyExplosion(cocos2d::Vec2 pos)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ENEMY_EXPLOSION_PLIST);
	cocos2d::Vector<SpriteFrame*> frames = GetAnimFrames("explosion(%d).png", NUM_OF_ANIMATION_FRAME_ENEMY);
	auto sprite = Sprite::createWithSpriteFrame(frames.front());
	mScene->addChild(sprite);
	sprite->setPosition(pos);
	
	auto callbackRemoveSprite = CallFunc::create([=]() {
		sprite->setVisible(false);
		mScene->removeChild(sprite);
	});
	
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	auto seqRemove = Sequence::create(Animate::create(animation), callbackRemoveSprite, nullptr);
	sprite->runAction(seqRemove);
}

int Ship::GetScore()
{
	return mScore;
}

int Ship::GetHealth()
{
	return mHealth;
}

void Ship::GameOver()
{
	if (mHealth <= 0)
	{
		SetAlive(false);

		for (int i = 0; i < mListBullet.size(); i++)
		{
			if (mListBullet.at(i)->IsAlive())
			{
				mListBullet.at(i)->SetAlive(false);
			}
		}

		auto callbackExplosion = CallFunc::create([=]() {
			EnemyExplosion(GetPosition());
		});

		auto callbackGameOver = CallFunc::create([=]() {
			auto scene = GameOver::create();
			Director::getInstance()->replaceScene(TransitionFade::create(TIME_TRASITION, scene));
		});

		auto seq = Sequence::create(callbackExplosion, DelayTime::create(TIME_SPLASH), callbackGameOver, nullptr);
		mScene->runAction(seq);
	}
}

void Ship::InitEvent(Scene *layer)
{
	mTouch = EventListenerTouchOneByOne::create();
	mTouch->setSwallowTouches(true);

	mTouch->onTouchBegan = CC_CALLBACK_2(Ship::onTouchBegan, this);
	mTouch->onTouchMoved = CC_CALLBACK_2(Ship::onTouchMoved, this);
	mTouch->onTouchEnded = CC_CALLBACK_2(Ship::onTouchEnded, this);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mTouch, layer);

}

bool Ship::onTouchBegan(Touch * touch, Event * event)
{
	Vec2 touchLocation = touch->getLocation();
	Node *node = dynamic_cast<Node*>(mSprite);

	Rect rect = node->getBoundingBox();

	if (rect.containsPoint(touchLocation))
	{
		mOldTouchLocation = touchLocation;
		mSprite->setTexture(IMAGE_SPACE_SHIP);
		return true;
	}

	return false;
}

void Ship::onTouchMoved(Touch * touch, Event * event)
{
	Vec2 newtouchLocation = touch->getLocation();
	Vec2 shipLocation = mSprite->getPosition();
	float posX = shipLocation.x - (mOldTouchLocation.x - newtouchLocation.x);
	float posY = shipLocation.y - (mOldTouchLocation.y - newtouchLocation.y);

	if (posX >= mSprite->getContentSize().width / 4 && posX <= WIDTH_SIZE - mSprite->getContentSize().width / 4 && 
		posY >= mSprite->getContentSize().width / 3 && posY <= HEIGHT_SIZE - mSprite->getContentSize().width / 3)
	{
		
		mSprite->setPosition(posX, posY);
	}

	mOldTouchLocation = newtouchLocation;
}

void Ship::onTouchEnded(Touch * touch, Event * event)
{
	mSprite->setTexture(IMAGE_SPACE_SHIP);
}

