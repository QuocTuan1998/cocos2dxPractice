
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "ModelObject.h"
class Item : public ModelObject
{
private:
	int mType;
public:
	Item();
	Item(cocos2d::Scene *scene);
	void Init() override;
	void Update() override;

	~Item();
};

#endif // __ITEM_H__
