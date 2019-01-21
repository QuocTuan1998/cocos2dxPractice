
#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "ModelObject.h"
#include "Definition.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class Bullet : public ModelObject
{
private:
	int mWho; // 1 : play ship ---- 2 : enemy ship
	//SimpleAudioEngine *mAudio;
	int mBulletSpeed;
public:
	Bullet();

	Bullet(cocos2d::Scene *scene, int who);

	void Init() override;
	void Update() override;

	cocos2d::Rect GetBoundingBox();

	~Bullet() {};
};

#endif // __BULLET_H__
