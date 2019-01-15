
#include "HomeScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using std::string;

Scene* Home::createScene()
{
    return Home::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Home::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	///////////Menu///////////////
	auto title = Label::create("Tower Defense", "fonts/Pacifico.ttf", 35);
	title->enableBold();
	title->enableOutline(Color4B::RED, 1);
	auto menuTitle = MenuItemLabel::create(title);
	auto playItem = MenuItemImage::create("play_normal.png", "play_pressed.png",
		[&](Ref* sender) {
		runAction(DelayTime::create(2.0f));
		auto playScene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, playScene, Color3B(0, 255, 255)));
	});
	/*auto exitItem = MenuItemImage::create("exit_normal.png", "exit_pressed.png",
		[&](Ref* sender) {
		log("exit!!");
	});*/
	auto homeMenu = Menu::create(menuTitle, playItem, NULL);
	homeMenu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	this->addChild(homeMenu);

    return true;
}
