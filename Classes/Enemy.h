
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "ModelObject.h"
#include "Bullet.h"
#include "Definition.h"

class Enemy : public ModelObject
{
private:
	cocos2d::Scene *mScene;
	int mHealth;
	int mShootSpeed;
	int mSpeed;
	int mBulletSpeed;
	int mCountBullet = 0;
	std::vector<Bullet*> mListBullet;
public:
	Enemy();

	Enemy(cocos2d::Scene *scene);

	void GenerateBullet();

	std::vector<Bullet*> getBulletEnemy();

	void Shoot();

	void ReduceHealth();

	int GetHealth();

	cocos2d::Rect GetBoundingBox();

	void Init() override;
	void Update() override;

	~Enemy();
};

#endif // __ENEMY_H__
