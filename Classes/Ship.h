
#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"
#include "ModelObject.h"
#include "Bullet.h"
#include "Meteor.h"
using namespace cocos2d;

class Ship : public ModelObject
{
private:
	Scene *mLayer;
	int mCountBullet = 0;
	EventListenerTouchOneByOne *mTouch;
	std::vector<Bullet*> mListBullet;
	Vec2 mOldTouchLocation;
	int mScore;
public:
	Ship();

	Ship(Scene * scene);
	
	void initEvent(Scene *scene);
	
	void generateBullet();

	void Init() override;

	void Update() override;

	void shoot();
	
	void Shipdamaged();

	void HandleCollision(std::vector<Meteor*> meteors);

	int GetScore();
	void SetScore(int score);

	bool onTouchBegan(Touch * touch, Event * event);

	void onTouchMoved(Touch * touch, Event * event);

	void onTouchEnded(Touch * touch, Event * event);
	
};

#endif // __SHIP_H__
