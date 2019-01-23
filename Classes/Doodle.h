
#pragma once

#include "cocos2d.h"
#include "ModelObject.h"
#include "Land.h"
class Doodle : public ModelObject
{
private:
	int mSpeed;
	cocos2d::EventListenerTouchOneByOne *mTouchEvent;
	cocos2d::Scene *mScene;
	std::vector<Land*> mLands;
	cocos2d::Vec2 mTouchLocation;
	cocos2d::Vec2 mCurrentPosition;
	bool mIsCollision;
	float mOldPosY;
public:
	Doodle();
	Doodle(cocos2d::Scene *scene);
	void Init() override;
	void Update() override;
	cocos2d::Vec2 GetCurrentPosition();
	void RemoveFirstLand();
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	~Doodle();
};
