#include "SkillRocker.h"

Sprite* SkillRocker::_cancel = nullptr;

SkillRocker* SkillRocker::createWith(const char * fileName)
{
	auto newNode = SkillRocker::create();

	if (!(newNode->initWith(_SKILLICON)))
	{
		//?delete newNode?
		return nullptr;
	}

	return newNode;
}

bool SkillRocker::initWith(const char * fileName)
{
	if (!Rocker::initWith(_ROCKER, _ROCKERBG))
	{
		return false;
	}
	//got a rocker, going to modify the rocker into skill rocker
	//DOt
	this->_rockerDot->setVisible(false);
	this->_rockerBg->setVisible(false);

	//_skillOutLine
	_skillOutLine = Sprite::create(_SKILLOUTLINE);
	_skillOutLine->setPosition(Point::ZERO);
	this->addChild(_skillOutLine, 4);

	//_CDIndicator
	_CDIndicator = Sprite::create(_CDINDICATOR);
	_CDIndicator->setVisible(false);
	_CDIndicator->setPosition(Point::ZERO);
	_CDIndicator->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(_CDIndicator, 5);

	//_CDDemostrate
	_CDDemostrate = ControlPotentiometer::create(_SKILLCD, _SKILLICON,NULLTEXTURE);
	_CDDemostrate->setEnabled(false);
	_CDDemostrate->setMinimumValue(0);
	_CDDemostrate->setMaximumValue(1);
	_CDDemostrate->setValue(0.75);//init the CD ready 
	_CDDemostrate->setPosition(Point::ZERO);
	this->addChild(_CDDemostrate, 3);

	//_SKillDisabled
	_skillDisabled = Sprite::create(_SKILLDISABLED);
	_skillDisabled->setPosition(Point::ZERO);
	_skillDisabled->setVisible(false);
	this->addChild(_skillDisabled,6);

	//_skillNoPower
	_skillNoPower = Sprite::create(_SKILLNOPOWER);
	_skillNoPower->setVisible(false);
	_skillNoPower->setPosition(Point::ZERO);
	this->addChild(_skillNoPower,4);

	//_CDLabel
	_CDLabel = Label::createWithSystemFont("","",50);
	_CDLabel->setSystemFontSize(50);
	_CDLabel->setVisible(false);
	this->addChild(_CDLabel, 7);

	//Class level init static _cancel  single instance
	if (!_cancel)
	{
		_cancel = Sprite::create(_CANCEL);
		_cancel->setPosition(Vec2(0, 190));
		//_cancel->setGlobalZOrder();//
		_cancel->setVisible(false);
		this->addChild(_cancel);
	}

	return true;
}

void SkillRocker::setIsEnable(bool value)
{
	if (isEnable && !value)//change from true to false
	{
		isEnable = value;

		_skillDisabled->setVisible(true);
	}
	else if (!isEnable && value)//change from false to true
	{
		isEnable = value;

		_skillDisabled->setVisible(false);
	}
}

bool SkillRocker::getIsEnable()
{
	return isEnable;
}

void SkillRocker::setIsNoPower(bool value)
{
	if (value!=isNoPower)
	{
		isNoPower = value;
		_skillNoPower->setVisible(value);
	}
}

bool SkillRocker::getIsNoPower()
{
	return isNoPower;
}

void SkillRocker::CDStart(float CDtime)
{
	CD = CDtime;
	CDPassed = 0;
	isCD = true;
	_CDDemostrate->setValue(0);
	_CDDemostrate->setMaximumValue(CDtime);

	_CDIndicator->setVisible(true);
	_CDIndicator->setRotation(0.0f);

	_CDLabel->setVisible(true);
	_CDLabel->setString(String::createWithFormat("%i", (int)CD)->getCString());

	schedule(schedule_selector(SkillRocker::CDUpdate), 1.0f / 60);
}

void SkillRocker::CDReadySynchronize()
{
	_CDIndicator->setVisible(false);

	isCD = false;

	//CD ready effect particle

	//////////////////////////

	CD = 0;

	CDPassed = 0;

	_CDDemostrate->setValue(_CDDemostrate->getMaximumValue());
	unschedule(schedule_selector(SkillRocker::CDUpdate));

	_CDLabel->setVisible(false);
}

void SkillRocker::CDAdvance(float time)
{
	CDPassed += time;

	CDUpdate(0.0f);
}

void SkillRocker::CDUpdate(float dt)
{
	CDPassed += dt;

	_CDDemostrate->setValue(CDPassed);

	_CDIndicator->setRotation(CDPassed / CD * 360);

	float left = (CD - CDPassed);


	if (left < 0)
	{
		_CDLabel->setString(String::createWithFormat("0.0")->getCString());
	}
	else if (left <= 1.0f)
	{
		_CDLabel->setString(String::createWithFormat("%.1f", left)->getCString());
	}
	else
	{
		_CDLabel->setString(String::createWithFormat("%i", (int)left)->getCString());
	}




	if (CDPassed >= CD)//CD already finished
	{
		_CDIndicator->setRotation(0.0f);
		unschedule(schedule_selector(SkillRocker::CDUpdate));
	}

}

bool SkillRocker::onTouchBeginCB(Touch * touch, Event * event)
{
	//relative location
	auto delataLocation = this->convertToNodeSpace(touch->getLocation());

	Size s = _CDDemostrate->getContentSize();

	Rect rect = Rect(-s.width / 2, -s.height / 2, s.width, s.height);

	if (rect.containsPoint(delataLocation) && isEnable && !isNoPower && !isCD)
	{
		_rockerDot->setVisible(true);

		_rockerDot->setPosition(delataLocation);

		_cancel->setVisible(true);

		//CCLOG("SkillRocker::onTouchBegin returned true! location:%d", delataLocation);

		return true;
	}

	return false;
}

void SkillRocker::onTouchMovedCB(Touch * touch, Event * event)
{
	auto location = touch->getLocation();
	//CCLOG("onTouchMovedCB called the location:x:%f, y:%f",location.x,location.y);


	_rockerDot->setPosition(locationTranslate(location));
}

void SkillRocker::onTouchEndedCB(Touch * touch, Event * event)
{
	auto delataLocation = _cancel->convertToNodeSpace(touch->getLocation());

	Size s = _cancel->getContentSize();

	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(delataLocation))
	{
		CCLOG("SKill cancel!");
	}
	else//skill didn't cancel
	{
		deltaPrev = delta;

		//to generate skillInfo
		SkillInfo * newInfo = new SkillInfo;

		OnSkillTriger(newInfo);

		delete newInfo;

	}

	_rockerDot->setVisible(false);

	_rockerDot->setPosition(Point::ZERO);

	_cancel->setVisible(false);

	//inherit
	delta = Vec2::ZERO;
	if (rockerOnChange)
	{
		rockerOnChange(delta);
	}
}


void SkillRocker::OnSkillTriger(SkillInfo * skillInfo)
{
	OnSkillTrigerCallBack(skillInfo);
	//other thing to handle
	CCLOG("OnSKillTriger!");
}
