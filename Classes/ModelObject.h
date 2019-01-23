
#pragma once

#include "cocos2d.h"

class ModelObject 
{
private:
	bool mIsAlive;
protected:
	cocos2d::Sprite *mSprite;
	cocos2d::PhysicsBody *mBody;
public:
	ModelObject();

	void SetPosition(cocos2d::Vec2 pos);
	cocos2d::Vec2 GetPosition();

	void setAlive(bool isAlive);
	bool IsAlive();

	virtual void Init() = 0;
	virtual void Update() = 0;

	~ModelObject();
};
