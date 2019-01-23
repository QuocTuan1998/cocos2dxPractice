
#include "SimpleAudioEngine.h"
#include "ModelObject.h"

USING_NS_CC;

ModelObject::ModelObject()
{
}

void ModelObject::SetPosition(cocos2d::Vec2 pos)
{
	mSprite->setPosition(pos);
}

cocos2d::Vec2 ModelObject::GetPosition()
{
	return mSprite->getPosition();
}

void ModelObject::setAlive(bool isAlive)
{
	mIsAlive = isAlive;
//	mSprite->removeComponent(mSprite->getPhysicsBody());
//	mSprite->getPhysicsBody()->
	mSprite->setVisible(mIsAlive);
}

bool ModelObject::IsAlive()
{
	return mIsAlive;
}

ModelObject::~ModelObject()
{
}
