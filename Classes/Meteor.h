
#ifndef __METEOR_H__
#define __METEOR_H__

#include "ModelObject.h"
#include "cocos2d.h"

class Meteor : public ModelObject
{
private:
	int mSpeedX;
	int mSpeedY;
	float mPosX;
	float mPosY;
public:
	Meteor();

	Meteor(cocos2d::Scene *scene);

	void Init() override;
	void Update() override;
	cocos2d::Rect GetBoundingBox();
};

#endif // __METEOR_H__
