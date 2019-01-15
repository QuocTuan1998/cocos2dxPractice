
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Sprite * mySprite;

Scene* MenuScene::createScene()
{
	auto scene = MenuScene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = MenuScene::create();
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
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sceneSprite = Sprite::create();
	sceneSprite->setContentSize(Size(visibleSize.width, 1));
	sceneSprite->setAnchorPoint(Vec2(0, 0));
	sceneSprite->setPosition(origin);
	auto sceneBody = PhysicsBody::createBox(sceneSprite->getContentSize());
	sceneBody->setDynamic(false);
	sceneSprite->addComponent(sceneBody);
	this->addChild(sceneSprite);

	auto lbTitle = Label::createWithTTF("Menu Game", "fonts/Marker Felt.ttf", 30);
	lbTitle->setTextColor(Color4B::RED);
	lbTitle->setPosition(Vec2(visibleSize.width / 2, 250));
	this->addChild(lbTitle);

	auto spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("dogsprites.plist");
	auto dogBatchNode = SpriteBatchNode::create("dogsprite.png");
	this->addChild(dogBatchNode);
	mySprite = Sprite::createWithSpriteFrameName("dog1.png");
	dogBatchNode->setPosition(Vec2(origin.x + 10, origin.y + 10));
	auto animation = Animation::create();
	
	for (int i = 1; i <= 7; i++)
	{
		char str[100] = { 0 };
		sprintf(str, "dog%d.png", i);
		animation->addSpriteFrame(spriteCache->spriteFrameByName(str));
		CCLOG("string : %s", str);
	}
	
	animation->setDelayPerUnit(0.1f);
	mySprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	auto myspriteBody = PhysicsBody::createBox(mySprite->getContentSize());
	mySprite->addComponent(myspriteBody);
	dogBatchNode->addChild(mySprite);

	this->scheduleUpdate();
    return true;
}

void MenuScene::update(float)
{
	mySprite->setPosition(Vec2(mySprite->getPositionX() + 0.5, mySprite->getPositionY()));
}

//
//

//
//return animFrames;