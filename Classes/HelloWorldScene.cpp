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
	size = Director::getInstance()->getVisibleSize();

	auto bgLayer = Layer::create();

	auto bg = Sprite::create("background.png");

	bgLayer->addChild(bg);

	bg->setPosition(Vec2(size.width/2,size.height/2));

	newLayer = Rocker::createWith("","");

	this->addChild(newLayer);

	this->addChild(bgLayer,-1);

	//button
	auto button1 = MenuItemLabel::create(Label::createWithSystemFont("Disabled", "", 50), CC_CALLBACK_1(HelloWorld::MenuCB, this));

	auto button2 = MenuItemLabel::create(Label::createWithSystemFont("Enabled", "", 50), CC_CALLBACK_1(HelloWorld::MenuCB, this));

	auto button3 = MenuItemLabel::create(Label::createWithSystemFont("location", "", 50), CC_CALLBACK_1(HelloWorld::MenuCB, this));

	auto menu = Menu::create(button1,button2,button3,NULL);

	this->addChild(menu);

	button2->setPosition(0,-100);

	button1->setTag(1);

	button2->setTag(2);

	button3 -> setTag(3);

	button3 -> setPosition(0,+100);



    return true;
}

void HelloWorld::MenuCB(Ref * sender)
{
	Node * ptr = (Node*)sender;

	switch (ptr->getTag())
	{
	case 1:
		newLayer->setEnabled(false);
		break;

	case 2:
		newLayer->setEnabled(true);
		break;

	case 3:
		newLayer->setRockerPosition(CCRANDOM_0_1(),CCRANDOM_0_1());
		break;

	default:
		break;
	}

}
