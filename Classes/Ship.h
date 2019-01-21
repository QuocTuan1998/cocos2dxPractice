
#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"
#include "ModelObject.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Enemy.h"

class Ship : public ModelObject
{
private:
	cocos2d::Scene *mScene;
	int mCountBullet = 0;
	int mHealth;
	cocos2d::EventListenerTouchOneByOne *mTouch;
	std::vector<Bullet*> mListBullet;
	cocos2d::Vec2 mOldTouchLocation;
	cocos2d::Sprite *mBGAttacked;
	int mScore;
public:
	Ship();

	Ship(cocos2d::Scene * scene);
	
	void InitEvent(cocos2d::Scene *scene);
	
	void GenerateBullet();

	void Init() override;

	void Update() override;

	void Shoot();
	
	void ShipAttacked();

	cocos2d::Vector<cocos2d::SpriteFrame*> GetAnimFrames(const char *format, int count);

	void HandleCollisionWithMeteor(std::vector<Meteor*> meteors);

	void HandleCollisionWithEnemy(std::vector<Enemy*> enemies);

	void HandleCollisionWithBulletEnemy(std::vector<Bullet*> bullets);

	void EnemyExplosion(cocos2d::Vec2 pos);

	int GetScore();

	int GetHealth();

	void GameOver();

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);

	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);

	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
	
};

#endif // __SHIP_H__
