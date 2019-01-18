
#include "GamePlayScene.h"
#include "Definition.h"
#include "Ship.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace cocos2d;
using namespace std;
Ship::Ship()
{

}

Ship::Ship(Scene *scene)
{
	mSprite = Sprite::create(__IMAGE_SPACE_SHIP__);
	mSprite->setPosition(Vec2(__WIDTH_SIZE__ / 2, __PADDING_MENU_ITEM__));
	this->SetAlive(true);
	mScore = 0;
	this->mLayer = scene;
	scene->addChild(mSprite);
	this->generateBullet();
	initEvent(scene);
}

void Ship::generateBullet()
{
	for (int i = 0; i < __NUM_OF_BULLET__; i++)
	{
		Bullet *bullet = new Bullet(mLayer);
		mListBullet.push_back(bullet);
	}
}

void Ship::Init()
{

}

void Ship::Update()
{
	shoot();
	
	for (int i = 0; i < mListBullet.size(); i++)
	{
		mListBullet.at(i)->Update();
	}
	
}

void Ship::shoot()
{
	mCountBullet++;
	if (mCountBullet % __NUM_OF_BULLET_FRAME__ == 0)
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

void Ship::Shipdamaged()
{
	auto callbackShipDamaged = CallFunc::create([=]() {
		mSprite->setTexture(__IMAGE_SPACE_SHIP_DAMAGED__);
	});
	auto callbackShipNormal = CallFunc::create([=]() {
		mSprite->setTexture(__IMAGE_SPACE_SHIP__);
	});

	auto damgedTime = DelayTime::create(__TIME_DELAY_SHIP_DAMAGED__);
	auto seqDamaged = Sequence::create(callbackShipDamaged, damgedTime, callbackShipNormal,nullptr);
	mSprite->runAction(seqDamaged);
}

void Ship::HandleCollision(vector<Meteor*> meteors)
{
	/*	Collision bullet---meteor	*/
	for (int i = 0; i < __NUM_OF_BULLET__; i++)
	{
		for (int j = 0; j < __NUM_OF_METEOR__; j++)
		{
			Bullet *bullet = mListBullet.at(i);
			Meteor *meteor = meteors.at(j);
			if (meteor->IsAlive() && bullet->IsAlive())
			{
				if (bullet->GetBoundingBox().intersectsRect(meteor->GetBoundingBox()))
				{
					bullet->SetAlive(false);
					meteor->SetAlive(false);
					SetScore(GetScore() + 1);
					//log("score : %d", GetScore());
				}
			}
		}
	}

	/*	Collision ship---meteor	*/
	for (int i = 0; i < __NUM_OF_METEOR__; i++)
	{
		Meteor *meteor = meteors.at(i);
		if (meteor->IsAlive() && IsAlive())
		{
			if (meteor->GetBoundingBox().intersectsRect(mSprite->getBoundingBox()))
			{
				Shipdamaged();
				SetScore(GetScore() - 1);
				meteor->SetAlive(false);
				if (GetScore() <= 0)
				{
					SetScore(0);
				}
			}
		}
	}
}

int Ship::GetScore()
{
	return mScore;
}

void Ship::SetScore(int score)
{
	mScore = score;
}

void Ship::initEvent(Scene *layer)
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
		mSprite->setTexture(__IMAGE_SPACE_SHIP__);
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
	mSprite->setPosition(posX, posY);
	if (shipLocation.x > posX)
	{
		mSprite->setTexture(__IMAGE_SPACE_SHIP_LEFT__);
	}
	else if(shipLocation.x < posX)
	{
		mSprite->setTexture(__IMAGE_SPACE_SHIP_RIGHT__);
	}
	
	mOldTouchLocation = newtouchLocation;
}

void Ship::onTouchEnded(Touch * touch, Event * event)
{
	mSprite->setTexture(__IMAGE_SPACE_SHIP__);
}

