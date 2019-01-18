
#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "ModelObject.h"
class Bullet : public ModelObject
{
public:
	Bullet();

	Bullet(cocos2d::Scene *scene);

	void Init() override;
	void Update() override;

	cocos2d::Rect GetBoundingBox();

	~Bullet() {};
};

#endif // __BULLET_H__
