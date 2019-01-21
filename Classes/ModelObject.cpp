#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "ModelObject.h"
USING_NS_CC;

ModelObject::ModelObject()
{
}

cocos2d::Vec2 ModelObject::GetPosition()
{
	return mSprite->getPosition();
}

void ModelObject::SetPosition(cocos2d::Vec2 position)
{
	mSprite->setPosition(position);
}

bool ModelObject::IsAlive()
{
	return mIsAlive;
}

void ModelObject::SetAlive(bool isAlive)
{
	mIsAlive = isAlive;
	mSprite->setVisible(mIsAlive);
}


ModelObject::~ModelObject()
{
}
