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
	size = Director::getInstance()->getVisibleSize();

	int width = size.width;

	int height = size.height;

	Sprite * dot = Sprite::create("rocker.png");

	rockerDot = dot;

	Sprite * bg = Sprite::create("rockerBG.png");

	rockerBg = bg;

	Sprite * direction = Sprite::create("rockerDir.png");

	rockerDir = direction;

	Sprite * start = Sprite::create("rockerStart.png");

	rockerStart = start;

	Sprite * disabled = Sprite::create("rockerDisabled.png");

	rockerDisabled = disabled;

	//set position
	dot->setPosition(Vec2(width*originX,height*originY));

	bg->setPosition(Vec2(width*originX, height*originY));

	direction->setPosition(Vec2(width*originX, height*originY));

	start->setPosition(Vec2(width*originX, height*originY));

	disabled->setPosition(Vec2(width*originX, height*originY));

	//set setOpacity
	dot->setOpacity(180);

	bg->setOpacity(180);//bg is already 

	direction->setOpacity(0);

	rockerStart->setOpacity(0);

	disabled->setOpacity(0);

	//add to this
	this->addChild(dot,2,tag_dot);

	this->addChild(bg,0,tag_bg);

	this->addChild(direction,1,tag_dir);

	this->addChild(start, 1, tag_start);

	this->addChild(disabled,3,tag_disabled);

	//new listener
	auto newListener = EventListenerTouchOneByOne::create();

	newListener->setSwallowTouches(true);//swallow enabled

	newListener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBeginCB, this);//_dispatch???????

	newListener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMovedCB, this);

	newListener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEndedCB, this);

	listener = newListener;

	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(newListener, rockerDot);//this

	D = bg->getContentSize().width;
}

float Rocker::getDiretionByRad() const
{
	return angle;
}

float Rocker::getDirectionByTheta() const
{
	return CC_RADIANS_TO_DEGREES(angle);
}

Vec2 Rocker::getRockerPosition() const
{
	return Vec2(size.width*originX,size.height);
}

void Rocker::setRockerPosition(Vec2 newLocation)
{
	
}

void Rocker::setRockerPosition(float x,float y)
{
	originX = x;

	originY = y;

	rockerBg->setPosition(Vec2(size.width*originX, size.height*originY));

	rockerDot->setPosition(Vec2(size.width*originX, size.height*originY));

	rockerDir->setPosition(Vec2(size.width*originX, size.height*originY));

	rockerStart->setPosition(Vec2(size.width*originX, size.height*originY));

	rockerDisabled->setPosition(Vec2(size.width*originX, size.height*originY));
}

void Rocker::setEnabled(bool able)
{
	if (able == enabled)
	{

	}
	else
	{
		if (enabled == true)
		{
			enabled = false;
			rockerDisabled->setOpacity(190);
			//dispatcher->removeEventListener(listener);
			listener->setEnabled(false);
			onTouchEndedCB(nullptr,nullptr);
		} 
		else
		{
			enabled = true;
			rockerDisabled->setOpacity(0);
			//dispatcher->addEventListenerWithSceneGraphPriority(listener,rockerDot);
			listener->setEnabled(true);
		}
	}
}

bool Rocker::getEnabled() const
{
	return enabled;
}


bool Rocker::onTouchBeginCB(Touch * touch, Event * event)
{
	//relative location
	auto delataLocation = rockerDot->convertToNodeSpace(touch->getLocation());

	Size s = rockerDot->getContentSize();

	Rect rect = Rect(0,0,s.width,s.height);

	if (rect.containsPoint(delataLocation) && enabled)
	{
		rockerBg->setOpacity(255);

		rockerDot->setOpacity(200);

		rockerStart->setOpacity(180);

		CCLOG("onTouchBegin returned true! location:%d",delataLocation);

		return true;
	}

	return false;
}

void Rocker::onTouchMovedCB(Touch * touch, Event * event)
{
	auto location =  touch->getLocation();
	//CCLOG("onTouchMovedCB called the location:x:%f, y:%f",location.x,location.y);
	rockerDir->setOpacity(200);

	//rockerStart->setOpacity(0);
	if (rockerStart->getNumberOfRunningActions() == 0)
	{
		rockerStart->runAction(FadeTo::create(0.1, 0));
	}

	rockerDir->setRotation(-CC_RADIANS_TO_DEGREES(angle));
	rockerDot->setPosition(locationTranslate(location));
}

void Rocker::onTouchEndedCB(Touch * touch, Event * event)
{
	rockerDot->setOpacity(180);

	rockerBg->setOpacity(220);//bg is already 

	//rockerDir->setOpacity(0);
	rockerDir->runAction(FadeTo::create(0.2, 0));

	//rockerStart->setOpacity(0);
	rockerStart->runAction(FadeTo::create(0.1,0));

	rockerDot->setPosition(Vec2(size.width*originX,size.height*originY));
}

Vec2 Rocker::locationTranslate(const Vec2 & location)
{
	auto origin = Vec2(size.width*originX,size.height*originY);

	auto delta = location- origin;

	float dis = delta.length();
	angle = delta.getAngle();
	if (dis > D / 2)
	{
		//delta = Vec2(delta.x / dis*D / 2, delta.y/dis*D/2);
		delta *= D/2/dis;
		CCLOG("the angle for delta:%f",delta.getAngle());
		
	}
	else
	{
		return location;
	}

	//auto newLocation = origin + delta;

	return (origin + delta);
}
