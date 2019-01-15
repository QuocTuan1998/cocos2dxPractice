
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Birds.h"
#include "Backgrounds.h"
#include "definition.h"
USING_NS_CC;
using std::string;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
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
    if ( !Scene::init() )
    {
        return false;
    }

    mVisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	addDataImage();
	initBackground();
	this->bird = new Birds(this);
	
	////////////Enemy move////////////
	//auto enemyCache = SpriteFrameCache::getInstance();
	//enemyCache->addSpriteFramesWithFile("enemymoves.plist");
	//auto enemyBatchNode = SpriteBatchNode::create("enemymoves.png");
	//this->addChild(enemyBatchNode);
	//enemyBatchNode->setPosition(Vec2(0, 200));
	//auto enemySprite = Sprite::createWithSpriteFrameName("enemymove(1).png");
	//auto enemyAnimate = Animation::create();

	//for (int i = 1; i <= 6; i++)
	//{
	//	char name[100] = { 0 };
	//	sprintf(name, "enemymove(%d).png", i);
	//	enemyAnimate->addSpriteFrame(enemyCache->spriteFrameByName(name));
	//}
	//auto enemyMove = MoveBy::create(1, Vec2(5, 0));
	//enemyAnimate->setDelayPerUnit(0.1f);
	//auto enemyDelay = DelayTime::create(1);
	//auto enemySpawn = Spawn::create(Animate::create(enemyAnimate), enemyMove, nullptr);
	//auto seqEnemy = Sequence::create(enemySpawn, enemyDelay, nullptr);
	//enemySprite->runAction(RepeatForever::create(seqEnemy));
	//enemyBatchNode->addChild(enemySprite);

	///////////////monster move///////////////
	//auto monsterCache = SpriteFrameCache::getInstance();
	//monsterCache->addSpriteFramesWithFile("monstermoves.plist");
	//auto monsterBatchNode = SpriteBatchNode::create("monstermoves.png");
	//this->addChild(monsterBatchNode);
	//monsterBatchNode->setPosition(Vec2(0, 150));
	//auto monsterSprite = Sprite::createWithSpriteFrameName("monstermove(1).png");
	//auto monsterAnimate = Animation::create();

	//for (int i = 1; i <= 4; i++)
	//{
	//	char name[100] = { 0 };
	//	sprintf(name, "monstermove(%d).png", i);
	//	monsterAnimate->addSpriteFrame(monsterCache->spriteFrameByName(name));
	//}
	//auto monsterMove = MoveBy::create(1, Vec2(5, 0));
	//monsterAnimate->setDelayPerUnit(0.5f);
	//auto monsterDelay = DelayTime::create(1);
	//auto monsterSpawn = Spawn::create(Animate::create(monsterAnimate), monsterMove, nullptr);
	//auto seqMonster = Sequence::create(monsterSpawn, monsterDelay, nullptr);
	//monsterSprite->runAction(RepeatForever::create(seqMonster));
	//monsterBatchNode->addChild(monsterSprite);

	//////////////taurus move ////////////////////
	//auto taurusCache = SpriteFrameCache::getInstance();
	//taurusCache->addSpriteFramesWithFile("taurusmoves.plist");
	//auto taurusBatchNode = SpriteBatchNode::create("taurusmoves.png");
	//this->addChild(taurusBatchNode);
	//taurusBatchNode->setPosition(Vec2(0, 100));
	//auto taurusSprite = Sprite::createWithSpriteFrameName("taurusmove(1).png");
	//auto taurusAnimate = Animation::create();

	//for (int i = 1; i <= 4; i++)
	//{
	//	char name[100] = { 0 };
	//	sprintf(name, "taurusmove(%d).png", i);
	//	taurusAnimate->addSpriteFrame(taurusCache->spriteFrameByName(name));
	//}
	//auto taurusMove = MoveBy::create(1.5, Vec2(5, 0));
	//taurusAnimate->setDelayPerUnit(0.5f);
	//auto taurusDelay = DelayTime::create(1);
	//auto taurusSpawn = Spawn::create(Animate::create(taurusAnimate), taurusMove, nullptr);
	//auto seqtaurus = Sequence::create(taurusSpawn, taurusDelay, nullptr);
	//taurusSprite->runAction(RepeatForever::create(seqtaurus));
	//taurusBatchNode->addChild(taurusSprite);

	this->scheduleUpdate();

    return true;
}

void HelloWorld::addDataImage()
{
	frames.push_back("stone1.png");
	frames.push_back("ground3.png");
	frames.push_back("ground1.png");
	frames.push_back("wall(1).png");
	frames.push_back("wall(2).png");
}

void HelloWorld::initBackground()
{
	/***************back ground****************/
	auto bgSprite = Sprite::create("bg.png");
	//bgSprite->setScale(1.1f);
	bgSprite->setAnchorPoint(Vec2(0, 0));
	float bgY = mVisibleSize.height - bgSprite->getContentSize().height;
	bgSprite->setPosition(Vec2(0, bgY));
	this->addChild(bgSprite);

	/***************stone****************/
	Backgrounds* stone = new Backgrounds(this,
		__STONE_LIST__,
		__STONE_PNG__,
		frames[0]
	);
	int numOfStone = mVisibleSize.width / stone->getSprite()->getContentSize().width;
	for (int i = 0; i <= numOfStone; i++)
	{
		float x = stone->getSprite()->getContentSize().width * i;
		float y = bgY + stone->getBatchNode()->getContentSize().height;
		stone->getBatchNode()->addChild(stone->addSprite(frames[0],
			Vec2(x, y)));
	}

	/***************ground****************/
	Backgrounds* ground = new Backgrounds(this,
		__GROUND_LIST__,
		__GROUND_PNG__,
		frames[1]
	);
	
	int numOfRowGround = mVisibleSize.width / ground->getSprite()->getContentSize().width;
	int groundHeight = mVisibleSize.height - (bgSprite->getContentSize().height + stone->getBatchNode()->getContentSize().height);
	int numOfColGround = groundHeight / ground->getSprite()->getContentSize().height;
	for (int i = 0; i <= numOfColGround; i++)
	{
		for (int j = 0; j <= numOfRowGround; j++)
		{
			float x = ground->getSprite()->getContentSize().width * j;
			float y = ground->getSprite()->getContentSize().height * i;;
			ground->getBatchNode()->addChild(ground->addSprite(frames[1],
				Vec2(x, y)));
		}
	}

	/***************grass****************/
	Backgrounds* grass = new Backgrounds(this,
		__GROUND_LIST__,
		__GROUND_PNG__,
		frames[2]
	);

	int numOfGrass = mVisibleSize.width / grass->getSprite()->getContentSize().width;
	for (int j = 0; j <= numOfGrass; j++)
	{
		float x = grass->getSprite()->getContentSize().width * j;
		float y = -(grass->getSprite()->getContentSize().height / 2);
		grass->getBatchNode()->addChild(grass->addSprite(frames[2],
			Vec2(x, y)));
	}
	
	/***************wall****************/
	Backgrounds* wall = new Backgrounds(this,
		__WALL_LIST__,
		__WALL_PNG__,
		frames[3]
	);
	float x = mVisibleSize.width - grass->getSprite()->getContentSize().width;
	float y = grass->getSprite()->getContentSize().height;
	wall->getBatchNode()->addChild(wall->addSprite(frames[3],
		Vec2(x,y)));

}

void HelloWorld::update(float)
{
	this->bird->move();
}

