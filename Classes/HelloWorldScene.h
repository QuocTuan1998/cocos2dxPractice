

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include <vector>
#include "cocos2d.h"
#include "Birds.h"
using namespace std;

class HelloWorld : public cocos2d::Scene
{
private:
	Size mVisibleSize;
	std::vector<string> frames;
	Birds * bird;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void addDataImage();

	void initBackground();

	void update(float);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
