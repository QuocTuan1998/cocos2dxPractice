
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "Definition.h"
#include "GamePlayScene.h"
USING_NS_CC;
using namespace std;
Scene* MenuScene::createScene()
{
    return MenuScene::create();
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

	auto bgSprite = Sprite::create(__BG_URL__);
	bgSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgSprite);
	
	auto label = MenuItemFont::create("SPACE GAME");
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - __PADDING_MENU_ITEM__));
	label->setFontSize(30);
	label->setColor(Color3B::RED);

	auto playItem = MenuItemImage::create("ui/button_play.png", "ui/button_play.png"
		,CC_CALLBACK_1(MenuScene::goToGamePlayScene, this)
	);
	playItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto exitItem = MenuItemImage::create("ui/button_exit.png", "ui/button_exit.png", 
		[](Ref *sender) {
		exit(0);
	});
	exitItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - __PADDING_MENU_ITEM__ ));

	auto menu = Menu::create(label, playItem, exitItem, NULL);
	menu->setPosition(Vec2(0, 0));

	this->addChild(menu);

    return true;
}

void MenuScene::goToGamePlayScene(cocos2d::Ref *sender)
{
	auto scene = GamePlay::create();
	Director::getInstance()->replaceScene(TransitionFade::create(__TRASITION_TIME__, scene));
}

