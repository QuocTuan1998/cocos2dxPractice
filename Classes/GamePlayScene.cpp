
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "Ship.h"
#include "Meteor.h"
#include "Bullet.h"
#include "ModelObject.h"
USING_NS_CC;

using namespace std;

Scene* GamePlay::createScene()
{
    return GamePlay::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
Bullet *bullet;

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bgSprite = Sprite::create(__BG_URL__);
	bgSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgSprite);

	mShip = new Ship(this);

	mScoreLable = Label::createWithTTF(to_string(mShip->GetScore()), "fonts/Marker Felt.ttf", 40);
	mScoreLable->setPosition(Vec2(__WIDTH_SIZE__ / 2, __HEIGHT__SIZE__ / 1.3));
	this->addChild(mScoreLable);

	this->GenerateMeteor();
	
	this->scheduleUpdate();

    return true;
}

void GamePlay::GenerateMeteor()
{
	for (int i = 0; i < __NUM_OF_METEOR__; i++)
	{
		Meteor *met = new Meteor(this);
		mListMeteor.push_back(met);
	}
}

void GamePlay::InitValue()
{
	/*mPosX = this->randomValueBetween(30,
		__WIDTH_SIZE__ - mListMeteor[mCountMetoer]->getSpriteSize().width);

	mPosY = __HEIGHT__SIZE__ + mListMeteor[mCountMetoer]->getSpriteSize().height;
	mSpeed = this->randomValueBetween(2, 7);
	mRotateDuration = this->randomValueBetween(0.5, 2);
	mAngle = this->randomValueBetween(30, 180);
	mScale = this->randomValueBetween(0.4, 1.2);*/
}

float GamePlay::RandomValueBetween(float low, float hight)
{
	return RandomHelper::random_real(low, hight);
}

float GamePlay::GetTime()
{
	timeval time;
	gettimeofday(&time, NULL);
	long milles = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	
	return (float)milles;
}

void GamePlay::update(float)
{	
	mScoreLable->setString(to_string(mShip->GetScore()));

	mShip->Update();

	MeteorFall();

	for (int i = 0; i < mListMeteor.size(); i++)
	{
		mListMeteor.at(i)->Update();
	}

	mShip->HandleCollision(mListMeteor);
}

void GamePlay::MeteorFall()
{
	mCountMetoer++;
	if (mCountMetoer % __NUM_OF_METEOR_FRAME__ == 0)
	{
		for (int i = 0; i < mListMeteor.size(); i++)
		{
			if (!mListMeteor.at(i)->IsAlive())
			{
				mListMeteor.at(i)->Init();
				break;
			}
		}
	}
}

