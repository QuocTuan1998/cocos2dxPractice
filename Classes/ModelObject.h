
#ifndef __OBJECT_MODEL_H__
#define __OBJECT_MODEL_H__

#include "cocos2d.h"

class ModelObject 
{
protected:
	cocos2d::Sprite *mSprite;
private:
	bool mIsAlive;
public:
	ModelObject();
	
	virtual void Init() = 0;
	virtual void Update() = 0;

	cocos2d::Vec2 GetPosition();
	void SetPosition(cocos2d::Vec2 position);

	bool IsAlive();
	void SetAlive(bool isAlive);

	~ModelObject();
};

#endif // __OBJECT_MODEL_H__
