
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
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

	auto background = Sprite::create(IMAGE_BACKGROUND_GAME_PLAY);
	background->setAnchorPoint(Vec2(0, 0));
	this->addChild(background);

	mBackground = new Background(this);
	mBackground->Init();
	
	mHealthBar = ui::LoadingBar::create(IMAGE_HEALTH_BAR);
	mHealthBar->setPercent(HEALTH_PLAYER_SHIP);
	mHealthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	mHealthBar->setPosition(Vec2(visibleSize.width / 2, 50));
	addChild(mHealthBar, 2);

	mShip = new Ship(this);
	mShip->Init();

	mScoreLable = Label::createWithTTF(to_string(mShip->GetScore()), "fonts/Marker Felt.ttf", 40);
	mScoreLable->setPosition(Vec2(WIDTH_SIZE / 2, HEIGHT_SIZE / 1.3));
	this->addChild(mScoreLable);

	this->GenerateMeteor();
	this->GenerateEnemy();

	this->scheduleUpdate();
	
    return true;
}

void GamePlay::GenerateMeteor()
{
	for (int i = 0; i < NUM_OF_METEOR; i++)
	{
		Meteor *met = new Meteor(this);
		mListMeteor.push_back(met);
	}
}

void GamePlay::GenerateEnemy()
{
	for (int i = 0; i < NUM_OF_ENEMY; i++)
	{
		Enemy *enemy = new Enemy(this);
		mListEnemy.push_back(enemy);
	}
}

void GamePlay::update(float)
{

	mBackground->Update();
	mScoreLable->setString(to_string(mShip->GetScore()));
	mHealthBar->setPercent(mShip->GetHealth());

	mShip->Update();
	MeteorFall();
	EnemyFall();

	/* update position meteor*/
	for (int i = 0; i < mListMeteor.size(); i++)
	{
		mListMeteor.at(i)->Update();
	}
	
	/*update position enemy*/
	for (int i = 0; i < mListEnemy.size(); i++)
	{
		mListEnemy.at(i)->Update();
	}

	/*collision*/
	mShip->HandleCollisionWithMeteor(mListMeteor);
	mShip->HandleCollisionWithEnemy(mListEnemy);
	
	for (int i = 0; i < mListEnemy.size(); i++)
	{
		mShip->HandleCollisionWithBulletEnemy(mListEnemy.at(i)->getBulletEnemy());
	}
	
	if (mShip->GetHealth() <= 0)
	{
		mHealthBar->setPercent(0);
	}
	
}

void GamePlay::MeteorFall()
{
	mCountMetoer++;
	if (mCountMetoer % NUM_OF_METEOR_FRAME == 0)
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

void GamePlay::EnemyFall()
{
	mCountEnemy++;
	if (mCountMetoer % NUM_OF_ENEMY_FRAME == 0)
	{
		for (int i = 0; i < mListEnemy.size(); i++)
		{
			if (!mListEnemy.at(i)->IsAlive())
			{
				mListEnemy.at(i)->Init();
				break;
			}
		}
	}
}
