
#ifndef __GAMPLAY_SCENE_H__
#define __GAMPLAY_SCENE_H__

#include "cocos2d.h"
#include "Ship.h"
#include "Meteor.h"
#include "Bullet.h"
#include "ModelObject.h"

class GamePlay : public cocos2d::Scene
{
private:
	Ship *mShip;
	std::vector<Meteor*> mListMeteor;
	int mCountMetoer = 0;
	cocos2d::Label *mScoreLable;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void GenerateMeteor();

	void InitValue();

	float RandomValueBetween(float low, float hight);

	float GetTime();

	void update(float);

	void MeteorFall();

    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);
};

#endif // __GAMPLAY_SCENE_H__
