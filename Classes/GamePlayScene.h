
#ifndef __GAMPLAY_SCENE_H__
#define __GAMPLAY_SCENE_H__

#include "cocos2d.h"
#include "background.h"
#include "Definition.h"
#include "Ship.h"
#include "Meteor.h"
#include "Bullet.h"
#include "Enemy.h"
#include "ui/CocosGUI.h"
#include "GameOver.h"
class GamePlay : public cocos2d::Scene
{
private:
	Ship *mShip;
	Background *mBackground;
	cocos2d::ui::LoadingBar *mHealthBar;
	std::vector<Meteor*> mListMeteor;
	std::vector<Enemy*> mListEnemy;
	int mCountMetoer = 0;
	int mCountEnemy = 0;
	cocos2d::Label *mScoreLable;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void GenerateMeteor();

	void GenerateEnemy();

	void update(float);

	void MeteorFall();

	void EnemyFall();

    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);
};

#endif // __GAMPLAY_SCENE_H__
