#include "Rocker.h"

Rocker::Rocker() {
	
}

Rocker* Rocker::createWith(const char * rockerDotName, const char * rockerBgName)
{
	Rocker * newRocker = Rocker::create();
	if (newRocker)
	{
		newRocker->initWith(rockerDotName, rockerBgName);
		return newRocker;
	}
	else 
	{
		CC_SAFE_DELETE(newRocker);
		return nullptr;
	}
}

void Rocker::initWith(const char * rockerDotName, const char * rockerBgName)
{
	auto size = Director::getInstance()->getVisibleSize();

	int width = size.width;

	int height = size.height;

	Sprite * dot = Sprite::create("rocker.png");

	rockerDot = dot;

	Sprite * bg = Sprite::create("rockerBG.png");

	rockerBg = bg;

	Sprite * direction = Sprite::create("rockerDir.png");

	rockerDir = direction;

	dot->setPosition(Vec2(width*originX,height*originY));

	bg->setPosition(Vec2(width*originX, height*originY));

	direction->setPosition(Vec2(width*originX, height*originY));

	dot->setOpacity(180);

	bg->setOpacity(235);//bg is already 

	direction->setOpacity(0);

	this->addChild(dot,2,tag_dot);

	this->addChild(bg,0,tag_bg);

	this->addChild(direction,1,tag_dir);

	auto newListener = EventListenerTouchOneByOne::create();

	newListener->setSwallowTouches(true);//swallow enabled

	newListener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBeginCB, this);//_dispatch???????

	newListener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMovedCB, this);

	newListener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEndedCB, this);

	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(newListener, rockerDot);//this

	D = bg->getContentSize().width;
}

float Rocker::getDiretionByRad() const
{
	return 0.0f;
}

float Rocker::getDirectionByTheta() const
{
	return 0.0f;
}

void Rocker::getRockerPosition() const
{

}

void Rocker::setRockerPosition()
{

}



bool Rocker::onTouchBeginCB(Touch * touch, Event * event)
{
	//relative location
	auto delataLocation = rockerDot->convertToNodeSpace(touch->getLocation());

	Size s = rockerDot->getContentSize();

	Rect rect = Rect(0,0,s.width,s.height);

	if (rect.containsPoint(delataLocation))
	{
		rockerBg->setOpacity(255);

		rockerDot->setOpacity(200);

		rockerDir->setOpacity(200);

		CCLOG("onTouchBegin returned true! location:%d",delataLocation);

		return true;
	}

	return false;
}

void Rocker::onTouchMovedCB(Touch * touch, Event * event)
{
	auto location =  touch->getLocation();
	CCLOG("onTouchMovedCB called the location:x:%f, y:%f",location.x,location.y);
}

void Rocker::onTouchEndedCB(Touch * touch, Event * event)
{
}

Vec2 Rocker::locationTranslate(const Vec2 & location)
{
	float dis = sqrt(pow(location.x,2)+pow(location.y,2));

	if (dis > D / 2)
	{
		return Vec2(location.x / dis*D / 2, location.y/dis*D/2);
	}
	else
	{
		return location;
	}

	return Vec2(0,0);//impossible
}
