#include "HelloWorldScene.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }


	//user code here:
	auto size = Director::getInstance()->getVisibleSize();

	auto bgLayer = Layer::create();

	auto bg = Sprite::create("background.png");

	bgLayer->addChild(bg);

	bg->setPosition(Vec2(size.width/2,size.height/2));

	auto newLayer = Rocker::createWith("","");

	this->addChild(newLayer);

	this->addChild(bgLayer,-1);

    return true;
}
