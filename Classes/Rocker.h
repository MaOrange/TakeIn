#pragma once



#ifndef ROCKER
#define ROCKER
#include<cocos2d.h>
USING_NS_CC;


#define _ROCKER "rocker.png"
#define _ROCKERBG "rockerBG.png"
#define _ROCKERDIR "rockerDir.png"
#define _ROCKERDISABELD "rockerDisabled.png"
#define _ROCKERSTART "rockerStart.png"
#define _CANCEL "cancel.png"
#define _SKILLICON "SKillIcon.png"
#define _SKILLCD "SkillCD.png"
#define _CDINDICATOR "CDIndicator.png"


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

	Vec2 getRockerPosition() const; //return the origin location of the rocker

	void setRockerPosition(Vec2);//set the RockerPosition with Vec2

	void setRockerPosition(float, float);//set the RockerPosition with two int

	void setEnabled(bool);

	bool getEnabled()const;

	float getDistance() const;

	float getRockerR() const;

	//rockerOnChangeHandle rockerOnChange=nullptr;

	rockerOnChangeHandler rockerOnChange=nullptr;

	void setCallBack(rockerOnChangeHandler handle);

protected:
	void initWith(const char *rockerDotName, const char * rockerBgName);

	virtual bool onTouchBeginCB(Touch * touch, Event * event);

	virtual void onTouchMovedCB(Touch * touch, Event * event);

	virtual void onTouchEndedCB(Touch * touch, Event * event);

	Vec2 locationTranslate(const Vec2 &location);

	EventListenerTouchOneByOne *listener;

	Sprite * _rockerDot;

	Sprite * rockerDir;

	Sprite * rockerBg;

	Sprite * rockerStart;

	Sprite * rockerDisabled;

	int D;

	float originX = 0.2;

	float originY = 0.3;

	Size size;

	float angle;

	bool enabled = true;

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();

	float Distance;

	Vec2 delta;

	static Sprite* _cancel;
};

#include "cocos-ext.h"
USING_NS_CC_EXT;

typedef  std::function<void()> SkillRockerCallBackHandle;

class SkillRocker :public Rocker
{
public:
	CREATE_FUNC(SkillRocker);

	void createWith(const char * fileName);

	void initWith(const char * fileName);

	void setIsEnable();
	bool getIsEnable();

	void setIsNoPower();
	bool getIsNoPower();

	void CDStart(float CDtime);

	void CDUPdate();

	void CDPassCallBack();

	void CDAdvance(float time);

	static Sprite* _cancel;

protected:
	float CD=0;

	float CDPassed=0;

	bool isCD=false;

	void CDUpdate();

	bool isEnable=true;

	bool isNoPower=false;

	Sprite* _CDIndicator;

	ControlPotentiometer* _CDdemostrate;

	virtual bool onTouchBeginCB(Touch * touch, Event * event)override;

	virtual void onTouchMovedCB(Touch * touch, Event * event)override;

	virtual void onTouchEndedCB(Touch * touch, Event * event)override;

	void OnCDReady();

	SkillRockerCallBackHandle OnCDReadyCallBack;

	SkillRockerCallBackHandle OnCDStartCallBack;

	SkillRockerCallBackHandle OnSkillTrigerCallBack;

};

#endif // !ROCKER

