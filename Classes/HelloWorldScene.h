
#pragma once

#include "cocos2d.h"
#include "Doodle.h"
#include "Land.h"

class HelloWorld : public cocos2d::Scene
{
private:
	cocos2d::Sprite * mBackGround;
	float mMaxY;
	cocos2d::Camera *mCamera;
	Doodle *mDoodle;
	std::vector<Land*> mListLand;
	cocos2d::PhysicsWorld *sceneWorld;
	void setPhysicWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void GenarateLand();

	void update(float dt);
    
	void setViewPointCenter(cocos2d::Vec2 position);
	
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};


