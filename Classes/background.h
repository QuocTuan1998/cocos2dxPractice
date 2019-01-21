
#ifndef __BACK_GROUND_H__
#define __BACK_GROUND_H__

#include "cocos2d.h"
#include "ModelObject.h"
#include "Definition.h"

class Background : ModelObject
{
private:
	cocos2d::Sprite *mBackgroundAbove;
public:
	Background();
	Background(cocos2d::Scene * scene);
	void Init() override;
	void Update() override;

	~Background();
};

#endif // __BACK_GROUND_H__
