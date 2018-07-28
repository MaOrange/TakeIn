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

	newNode = Rocker::createWith("","");

	newNode->setPosition(Vec2(size.width*0.2,size.height*0.3));

	newNode->setCallBack(std::bind(&HelloWorld::rockerCB, this, std::placeholders::_1));

	this->addChild(newNode);

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


	//test SKillRocker
	newSkill = SkillRocker::createWith("");

	newSkill->setPosition(Vec2(size.width*0.75,size.height*0.5));

	newSkill->OnSkillTrigerCallBack = CC_CALLBACK_1(HelloWorld::SKillCB,this);

	this->addChild(newSkill,5);

	//keyboard listener
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) 
	{
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_C:
			//cd start
			newSkill->CDStart(10);
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_R:
			//cd ready synchronize
			newSkill->CDReadySynchronize();
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			newSkill->CDAdvance(2.0f);
			break;

		default:
			break;
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::MenuCB(Ref * sender)
{
	Node * ptr = (Node*)sender;

	switch (ptr->getTag())
	{
	case 1:
		newNode->setEnabled(false);
		break;

	case 2:
		newNode->setEnabled(true);
		break;

	case 3:
		newNode->setPosition(CCRANDOM_0_1()*size.width,CCRANDOM_0_1()*size.height);
		break;

	default:
		break;
	}

}

void HelloWorld::rockerCB(Vec2 & rockerInfo)
{
	CCLOG("rockerCB: angle:%f  length:%f",rockerInfo.getAngle(),rockerInfo.getLength());
}

void HelloWorld::SKillCB(SkillInfo * skillInfo)
{
	CCLOG("SkillCB: Vec.length()=%f, Vec.angle()=%f",skillInfo->direction.getLength(), skillInfo->direction.getAngle());

	newSkill->CDStart(10);

	scheduleOnce([=](float dt) {newSkill->CDReadySynchronize(); }
	, 10.0f,"key");
}


