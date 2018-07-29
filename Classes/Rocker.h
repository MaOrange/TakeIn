#pragma once



#ifndef ROCKER
#define ROCKER
#include<cocos2d.h>
USING_NS_CC;


#define _ROCKER "rocker.png"
#define _ROCKERBG "rockerBG.png"
#define _ROCKERDIR "rockerDir.png"
#define _ROCKERDISABLED "rockerDisabled.png"
#define _ROCKERSTART "rockerStart.png"
#define _SKILLICON "SKillIcon.png"
#define _SKILLCD "SkillCD.png"
#define _SKILLOUTLINE "skillOutLine.png"
#define _CDINDICATOR "CDIndicator.png"


#define  _SKILLDISABLED "skillDisabled.png"

#define _CANCEL "cancel.png"
#define  _CANCEL_X 0.8f
#define _CANCEL_Y 0.8f


struct SkillInfo
{
	Vec2 direction;

};

typedef enum
{
	tag_dot, tag_bg, tag_dir, tag_start, tag_disabled
}tagForRocker;

typedef  std::function<void(Vec2&)> rockerOnChangeHandler;


class Rocker :public Node
{
public:
	Rocker();

	CREATE_FUNC(Rocker);

	static Rocker* createWith(const char *rockerDotName, const char * rockerBgName);

	float getDiretionByRad() const;//return the direction in normal system in the unit of rad

	float getDirectionByTheta() const;//return the direction in normal system in the unit of degree

	void setEnabled(bool);

	bool getEnabled()const;

	float getDistance() const;

	float getRockerR() const;

	//rockerOnChangeHandle rockerOnChange=nullptr;

	rockerOnChangeHandler rockerOnChange=nullptr;

	void setCallBack(rockerOnChangeHandler handle);

protected:
	virtual bool initWith(const char *rockerDotName, const char * rockerBgName);

	virtual bool onTouchBeginCB(Touch * touch, Event * event);

	virtual void onTouchMovedCB(Touch * touch, Event * event);

	virtual void onTouchEndedCB(Touch * touch, Event * event);

	Vec2 locationTranslate(const Vec2 &location);

	EventListenerTouchOneByOne *listener;

	Sprite * _rockerDot;

	Sprite * _rockerDir;

	Sprite * _rockerBg;

	Sprite * _rockerStart;

	Sprite * _rockerDisabled;

	int D;

	Size size;

	float angle;

	bool enabled = true;

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();

	float Distance;

	Vec2 delta;

	static Sprite* _cancel;

	SkillInfo skillInfoPrev;
};

#include "cocos-ext.h"
USING_NS_CC_EXT;

typedef  std::function<void(SkillInfo*)> SkillRockerCallBackHandle;

class SkillRocker :public Rocker
{
public:
	CREATE_FUNC(SkillRocker);

	static SkillRocker* createWith(const char * fileName);

	bool initWith(const char * fileName);

	void setIsEnable(bool value);
	bool getIsEnable();

	void setIsNoPower();
	bool getIsNoPower();

	void CDStart(float CDtime);

	void CDReadySynchronize();//to synchronize the cd progress in skillRocker and hero

	void CDPassCallBack();

	void CDUpdate(float dt);

	void CDAdvance(float time);

	static Sprite* _cancel;

	Vec2 deltaPrev;//to save the prev delta value to be passed by ptr to skillInfo

	SkillRockerCallBackHandle OnSkillTrigerCallBack = [](SkillInfo*) {};
protected:
	float CD=0;

	float CDPassed=0;

	bool isCD=false;

	bool isEnable=true;

	bool isNoPower=false;

	Sprite* _CDIndicator;

	ControlPotentiometer* _CDDemostrate;

	Sprite* _skillDisabled;

	Sprite * _skillOutLine;

	Label* _CDLabel;

	virtual bool onTouchBeginCB(Touch * touch, Event * event)override;

	virtual void onTouchMovedCB(Touch * touch, Event * event)override;

	virtual void onTouchEndedCB(Touch * touch, Event * event)override;

	SkillRockerCallBackHandle OnCDStartCallBack = [](SkillInfo*) {};

	void OnSkillTriger(SkillInfo * skillInfo);

	//for cd progress
	

};

#endif // !ROCKER

