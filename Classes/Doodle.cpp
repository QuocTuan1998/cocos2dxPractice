
#include "SimpleAudioEngine.h"
#include "Doodle.h"
#include "Definition.h"
USING_NS_CC;
using namespace cocos2d;
Doodle::Doodle()
{
}

Doodle::Doodle(cocos2d::Scene * scene)
{
	mSprite = Sprite::create(IMAGE_DOODLE);
	setAlive(true);
	mSpeed = DOO_SPEED_Y;
	mScene = scene;
	mBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(0, 1, 0));
	mBody->setRotationEnable(false);
	mBody->setCollisionBitmask(1);
	mBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mBody);
	mIsCollision = false;
	scene->addChild(mSprite);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Doodle::onContactBegin, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, scene);
	
	
	mTouchEvent = EventListenerTouchOneByOne::create();
	mTouchEvent->setSwallowTouches(true);
	mTouchEvent->onTouchBegan = [](Touch* touch, Event* event) { return true; };

	mTouchEvent->onTouchBegan = CC_CALLBACK_2(Doodle::onTouchBegan, this);
	mTouchEvent->onTouchMoved = CC_CALLBACK_2(Doodle::onTouchMoved, this);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mTouchEvent, scene);
}

void Doodle::Init()
{
	for (int i = 0; i < 5; i++)
	{
		Land *land = new Land(mScene);
		land->setAlive(true);
		land->SetPosition(Vec2(100 * i, 90));
		mLands.push_back(land);
	}
	SetPosition(Vec2(WIDTH_SIZE / 2, 200));
	
}

void Doodle::Update()
{
	if (IsAlive())
	{	
		//mBody->setPositionOffset(mSprite->getPosition());
		//mBody->setVelocity(Vec2(0, -DOO_SPEED_Y));
		//mOldPosY = mSprite->getPosition().y;
		
		if (GetPosition().y >= HEIGHT_SIZE/2)
		{
			//log("%f", mSprite->getPosition().y);
			//SetPosition(Vec2(GetPosition().x, 0));
		}
	}

	
}

cocos2d::Vec2 Doodle::GetCurrentPosition()
{
	return mCurrentPosition;
}

void Doodle::RemoveFirstLand()
{
	for (int i = 0; i < mLands.size(); i++)
	{
		mLands.at(i)->setAlive(false);
	}
}

bool Doodle::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	mTouchLocation = touch->getLocation();
	return true;
}

void Doodle::onTouchMoved(Touch * touch, Event * event)
{
	Vec2 newLocation = touch->getLocation();
	Vec2 dooPosMax = GetPosition() + Vec2(mSprite->getContentSize().width / 2, 0);
	Vec2 dooPosMin = GetPosition() -Vec2(mSprite->getContentSize().width / 2, 0);
	
	if (newLocation.x > dooPosMax.x || newLocation.x < dooPosMin.x)
	{
		Vec2 distance = newLocation - mTouchLocation;
		mBody->setVelocity(Vec2(distance.x, mBody->getVelocity().y));
	}
}

bool Doodle::onContactBegin(cocos2d::PhysicsContact & contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	if (a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 2 ||
		a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 1
		)
	{
		mCurrentPosition.y = b->getPosition().y + DOO_SPEED_Y;
		mBody->setVelocity(Vec2(0, DOO_SPEED_Y));
		return false;
	}
}

Doodle::~Doodle()
{
}
