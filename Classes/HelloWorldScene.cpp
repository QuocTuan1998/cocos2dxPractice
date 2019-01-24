
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	// draw mask
	scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -980 / 2));

	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = HelloWorld::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	mBackGround = Sprite::create("bg.png");
	mBackGround->setAnchorPoint(Vec2(0, 0));
	//mBackGround->setPosition(Vec2(WIDTH_SIZE / 2, HEIGHT_SIZE / 2));


	this->addChild(mBackGround);

	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//// create node
	//auto edgeNode = Node::create();
	//edgeNode->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
	//edgeNode->setPhysicsBody(edgeBody);
	
	//this->addChild(edgeNode);

	mCamera = Camera::createPerspective(60, (GLfloat)100 / 100, 1, 1000);

	mDoodle = new Doodle(this);
	//mCamera->setPosition(mDoodle->GetPosition());
	mDoodle->Init();
	this->GenarateLand();
	mMaxY = mListLand.at(0)->GetPosition().y;
	mMinY = mListLand.at(0)->GetPosition().y;
	this->scheduleUpdate();
	//mBackGround->runAction(MoveTo::create(1, Vec2(0, 200)));
	return true;
}

void HelloWorld::GenarateLand()
{
	for (int i = 0; i <= NUM_OF_LAND; i++)
	{
		Land *land = new Land(this);
		land->Init();
		mListLand.push_back(land);
	}
}

void HelloWorld::update(float dt)
{
	mDoodle->Update();
	
	//float centerPos = (mMaxY + mMinY) / 2;
	//if (mDoodle->GetPosition().y >= HEIGHT_SIZE / 2)
	//{
		//log(" pos land %f ", mListLand.at(1));
		//log("pos scene %f ", Director::getInstance()->getRunningScene()->getPositionY());
		Director::getInstance()->getRunningScene()->setPositionY(Director::getInstance()->getRunningScene()->getPositionY() - SCENE_SPEED);
		mBackGround->setPositionY(mBackGround->getPositionY() + BACKGROUND_SPEED);
		log("bg pos Y : %f", mBackGround->getPositionY());
		for (int i = 0; i < mListLand.size(); i++)
		{
			Land *land = mListLand.at(i);
			if (mBackGround->getPositionY() > land->GetPosition().y)
			{
				land->setAlive(false);
			}
		}
	//}
	SpawnLand();
}

void HelloWorld::SpawnLand()
{
	for (int i = 0; i < mListLand.size(); i++)
	{
		Land *land = mListLand.at(i);
		if (!land->IsAlive())
		{
			land->Init();
			break;
		}
	}
}
	
