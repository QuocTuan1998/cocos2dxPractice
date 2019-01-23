
#pragma once

#include "cocos2d.h"
#include "ModelObject.h"
class Land : public ModelObject
{
private:
	bool mIsCollision;
public:
	Land();
	Land(cocos2d::Scene *scene);
	void Init() override;
	void Update() override;
	~Land();
};
