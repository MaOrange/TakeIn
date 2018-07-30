#include "Rocker.h"

Rocker::Rocker() {
	
}

Rocker* Rocker::createWith(const char * rockerDotName, const char * rockerBgName)
{
	Rocker * newRocker = Rocker::create();
	if (newRocker)
	{
		newRocker->initWith(_ROCKER, _ROCKERBG);
		return newRocker;
	}
	else 
	{
		CC_SAFE_DELETE(newRocker);
		return nullptr;
	}
}

bool Rocker::initWith(const char * rockerDotName, const char * rockerBgName)
{
	size = Director::getInstance()->getVisibleSize();

	int width = size.width;

	int height = size.height;

	Sprite * dot = Sprite::create(rockerDotName);

	_rockerDot = dot;

	Sprite * bg = Sprite::create(rockerBgName);

	_rockerBg = bg;

	Sprite * direction = Sprite::create(_ROCKERDIR);

	_rockerDir = direction;

	Sprite * start = Sprite::create(_ROCKERSTART);

	_rockerStart = start;

	Sprite * disabled = Sprite::create(_ROCKERDISABLED);

	_rockerDisabled = disabled;

	//set position
	dot->setPosition(Point::ZERO);

	bg->setPosition(Point::ZERO);

	direction->setPosition(Point::ZERO);

	start->setPosition(Point::ZERO);

	disabled->setPosition(Point::ZERO);

	//set setOpacity
	dot->setOpacity(180);

	bg->setOpacity(90);//bg is already 

	direction->setOpacity(0);

	_rockerStart->setOpacity(0);

	disabled->setOpacity(0);

	//add to this
	this->addChild(dot,10,tag_dot);

	this->addChild(bg,0,tag_bg);

	this->addChild(direction,1,tag_dir);

	this->addChild(start, 1, tag_start);

	this->addChild(disabled,7,tag_disabled);

	//new listener
	auto newListener = EventListenerTouchOneByOne::create();

	newListener->setSwallowTouches(true);//swallow enabled

	newListener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBeginCB, this);//_dispatch???????

	newListener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMovedCB, this);

	newListener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEndedCB, this);

	listener = newListener;

	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(newListener, _rockerDot);//this

	D = bg->getContentSize().width;

	return true;
}

float Rocker::getDiretionByRad() const
{
	return angle;
}

float Rocker::getDirectionByTheta() const
{
	return CC_RADIANS_TO_DEGREES(angle);
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
			_rockerDisabled->setOpacity(190);
			//dispatcher->removeEventListener(listener);
			listener->setEnabled(false);
			onTouchEndedCB(nullptr,nullptr);
		} 
		else
		{
			enabled = true;
			_rockerDisabled->setOpacity(0);
			//dispatcher->addEventListenerWithSceneGraphPriority(listener,rockerDot);
			listener->setEnabled(true);
		}
	}
}

bool Rocker::getEnabled() const
{
	return enabled;
}

float Rocker::getDistance() const
{

	return Distance;
}

float Rocker::getRockerR() const
{
	return _rockerBg->getContentSize().width;
}


bool Rocker::onTouchBeginCB(Touch * touch, Event * event)
{
	//relative location
	auto delataLocation = _rockerDot->convertToNodeSpace(touch->getLocation());

	Size s = _rockerDot->getContentSize();

	Rect rect = Rect(0,0,s.width,s.height);

	if (rect.containsPoint(delataLocation) && enabled)
	{
		_rockerBg->setOpacity(150);

		_rockerDot->setOpacity(200);

		_rockerStart->setOpacity(180);

		//CCLOG("onTouchBegin returned true! location:%d",delataLocation);

		return true;
	}

	return false;
}

void Rocker::onTouchMovedCB(Touch * touch, Event * event)
{
	auto location =  touch->getLocation();
	//CCLOG("onTouchMovedCB called the location:x:%f, y:%f",location.x,location.y);
	_rockerDir->setOpacity(200);

	//rockerStart->setOpacity(0);
	if (_rockerStart->getOpacity()!=0 && _rockerStart->getNumberOfRunningActions() == 0)
	{
		_rockerStart->runAction(FadeTo::create(0.1f, 0));
	}



	_rockerDir->setRotation(-CC_RADIANS_TO_DEGREES(angle));
	_rockerDot->setPosition(locationTranslate(location));
}

void Rocker::onTouchEndedCB(Touch * touch, Event * event)
{
	_rockerDot->setOpacity(180);

	_rockerBg->setOpacity(90);//bg is already 

	//rockerDir->setOpacity(0);
	_rockerDir->runAction(FadeTo::create(0.2f, 0));

	//rockerStart->setOpacity(0);
	_rockerStart->runAction(FadeTo::create(0.1f,0));

	_rockerDot->setPosition(Point::ZERO);


	delta = Vec2::ZERO;
	if (rockerOnChange)
	{
		rockerOnChange(delta);
	}
}

Vec2 Rocker::locationTranslate(const Vec2 & location)
{
	delta = this->convertToNodeSpace(location);

	float dis = delta.length();
	angle = delta.getAngle();
	Distance = delta.getLength();

	if (rockerOnChange)
	{
		rockerOnChange(delta);
	}

	if (dis > D / 2)
	{
		//delta = Vec2(delta.x / dis*D / 2, delta.y/dis*D/2);
		delta *= D/2/dis;
		//CCLOG("the angle for delta:%f",delta.getAngle());
		
	}
	else
	{
		return delta;
	}

	return (delta);
}

void Rocker::setCallBack(rockerOnChangeHandler handle)
{
	rockerOnChange = handle;
}


