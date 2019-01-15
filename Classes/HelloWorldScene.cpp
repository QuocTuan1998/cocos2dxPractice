
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
	Scene *scene = Scene::create();

	HelloWorld *layer = HelloWorld::create();

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
    if ( !Scene::init() )
    {
        return false;
    }

	mVisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	this->mTileMap = new TMXTiledMap();
	this->mTileMap->initWithTMXFile("map.tmx");
	this->mTileMap->setAnchorPoint(Point::ZERO);
	this->mTileMap->setPosition(0, 0);
	this->mBackground = this->mTileMap->layerNamed("background");
	this->addChild(this->mTileMap);
	
	this->mMeta = mTileMap->layerNamed("meta");
	this->mMeta->setVisible(false);
	this->mMeta->setVisible(false);
	auto tmxObjGroup = this->mTileMap->objectGroupNamed("Objects");

	if (tmxObjGroup == NULL)
	{
		CCLOG("wrong name !!");
		return false;
	}

	auto spawnPoint = tmxObjGroup->objectNamed("SpawnTest");
	
	float x = spawnPoint.at("x").asFloat();
	float y = spawnPoint.at("y").asFloat();

	mPlayer = new Sprite();
	mPlayer->initWithFile("Player.png");
	mPlayer->setPosition(Vec2(x, y));

	this->addChild(mPlayer);
	this->setViewPointCenter(mPlayer->getPosition());
	this->registerWithTouchDispatcher();

    return true;
}

void HelloWorld::setViewPointCenter(Point position)
{
	int x = MAX(position.x, mVisibleSize.width / 2);
	int y = MAX(position.y, mVisibleSize.height / 2);

	x = MIN(x, (mTileMap->getMapSize().width * this->mTileMap->getTileSize().width) - mVisibleSize.width / 2);
	y = MIN(y, (mTileMap->getMapSize().height * this->mTileMap->getTileSize().height) - mVisibleSize.height / 2);

	Point actualPosition = Vec2(x, y);

	Point centerOfView = Vec2(mVisibleSize.width / 2, mVisibleSize.height / 2);
	Point viewpoint = Vec2(centerOfView, actualPosition);
	this->setPosition(viewpoint);
}

void HelloWorld::registerWithTouchDispatcher()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchEnded, this);
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void HelloWorld::setPlayerPosition(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
	int tileGid = mMeta->tileGIDAt(tileCoord);
	CCLOG("coll1 -- %d", tileGid);
	if (tileGid)
	{
		ValueMap properties = mTileMap->propertiesForGID(tileGid).asValueMap();

		if (properties.size() > 0)
		{
			String collision = properties.at("Collidable").asString();
			if (collision.boolValue() && collision.compare("true") == 0)
			{
				CCLOG("coll1");
				return;
			}
		}
		else
		{
			CCLOG("coll2");
			return;
		}
	}

	mPlayer->setPosition(position);
}

bool HelloWorld::touchBegan(Touch * touch, Event * event)
{
	return true;
}

void HelloWorld::touchEnded(Touch * touch, Event * event)
{
	Point touchLocation = touch->getLocation(); // get touch Position
	Point playerPosition = mPlayer->getPosition(); // get player position

	float subX = touchLocation.x - playerPosition.x; // get distance between touch and player
	float subY = touchLocation.y - playerPosition.y;
	Point diff = Vec2(subX, subY);

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPosition.x += mTileMap->getTileSize().width;
		}
		else {
			playerPosition.x -= mTileMap->getTileSize().width;
		}
	}
	else {
		if (diff.y > 0) {
			playerPosition.y += mTileMap->getTileSize().height;
		}
		else {
			playerPosition.y -= mTileMap->getTileSize().height;
		}
	}

	if (playerPosition.x <= (mTileMap->getMapSize().width * mTileMap->getTileSize().width) &&
		playerPosition.y <= (mTileMap->getMapSize().height * mTileMap->getTileSize().height) &&
		playerPosition.y >= 0 &&
		playerPosition.x >= 0)
	{
		this->setPlayerPosition(playerPosition);
	}

	this->setViewPointCenter(mPlayer->getPosition());
}

Point HelloWorld::tileCoordForPosition(Point position)
{
	int x = position.x / mTileMap->getTileSize().width;
	int y = ((mTileMap->getMapSize().height * mTileMap->getTileSize().height) - position.y) / 
			mTileMap->getTileSize().height;

	return Vec2(x, y);
}

