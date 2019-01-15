
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    Scene *scene = HelloWorld::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = HelloWorld::create();
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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto mySprite = Sprite::create("darksaber_walk1.png");
	mySprite->setScale(0.25);
	mySprite->setPosition(Vec2(100, 200));
	/////////// move
	/*auto moveBy = MoveBy::create(2, Vec2(300, 10));
	mySprite->runAction(moveBy); 

	auto moveTo = MoveTo::create(2, Vec2(300, mySprite->getPositionY()));
	auto delay = DelayTime::create(1);

	auto seq = Sequence::create(delay, moveBy, nullptr);
	mySprite->runAction(seq);*/

	///////////RotateTo clockwise (duration, degree clockwise)
	//auto rotateTo = RotateTo::create(1.0f, 90.0f);
	////////// RotateBy clockwise
	//auto rotateBy = RotateBy::create(2.0f, 90.0f);
	
	///////////ScaleBy(duration, uniform zoom)
	//auto scaleBy1 = ScaleBy::create(2.0f, 3.0f);
	//////////ScaleBy (duration, x, y)
	//auto scaleBy2 = ScaleBy::create(2.0f, 2.5f, 2.0f);
	//////////ScaleTo(duration, uniform zoom)
	//auto scaleTo = ScaleTo::create(2.0f, 3.0f);
	////////////ScaleTo(duration, x, y)
	//auto scaleTo1 = ScaleTo::create(2.0f, 2.0f, 4.0f);
	
	///////////FadeIn(duration)
	//auto fadeIn = FadeIn::create(2.0f);
	
	//mySprite->runAction(fadeIn);

	//cocos2d::Director::getInstance()->setContentScaleFactor(5.0f);

	//auto seq = Sequence::create(delay, moveBy, nullptr);
	//mySprite->runAction(seq);

	////////////////TinTo(duration, color)
	//auto tintTo = TintTo::create(2.0f, 119.0f, 190.0f, 226.0f);
	//mySprite->runAction(tintTo);

	// create frames
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(39);
	std::string name = "darksaber_walk";
	std::string file = ".png";
	for (int i = 0; i < 39; i++)
	{
		std::string str = "";
		str += name + std::to_string(i) + file;
		animFrames.pushBack(SpriteFrame::create(str, Rect(0, 0, 300, 300)));
	}

	// create animation out of the frames
	Animation* anim = Animation::createWithSpriteFrames(animFrames, 0.005f);
	Animate* animate = Animate::create(anim);
	//mySprite->runAction(RepeatForever::create(animate)); // run and repeate forever

	/////////////////Easing
	auto move = MoveBy::create(2, Vec2(20, 0));
	auto move_ease_in = EaseBounceIn::create(move->clone());
	auto move_ease_in_back = move_ease_in->reverse();

	auto actionRotate = RotateBy::create(2, 20);

	auto delay = DelayTime::create(1.0f);

	auto spawn = Spawn::create(animate, move, actionRotate, nullptr);

	auto seq = Sequence::create(animate,
		move_ease_in, delay,
		move_ease_in_back, delay->clone(), nullptr);

	mySprite->runAction(RepeatForever::create(animate));

	auto bodies = PhysicsBody::createBox(mySprite->getContentSize());
	mySprite->addComponent(bodies);

	this->addChild(mySprite);

    return true;
}
