#pragma once



#ifndef ROCKER
#define ROCKER
#include<cocos2d.h>
USING_NS_CC;



#define _ROCKER "RockerResources/rocker.png"
#define _ROCKERBG "RockerResources/rockerBG.png"
#define _ROCKERDIR "RockerResources/rockerDir.png"
#define _ROCKERDISABLED "RockerResources/rockerDisabled.png"
#define _ROCKERSTART "RockerResources/rockerStart.png"
#define _SKILLICON "RockerResources/SkillIcon.png"
#define _SKILLCD "RockerResources/SkillCD.png"
#define _SKILLOUTLINE "RockerResources/skillOutLine.png"
#define _CDINDICATOR "RockerResources/CDIndicator.png"

#define NULLTEXTURE "RockerResources/null.png"

#define  _SKILLDISABLED "RockerResources/skillDisabled.png"
#define _SKILLNOPOWER "RockerResources/SkillNoPower.png"

#define _CANCEL "RockerResources/cancel.png"
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



#endif // !ROCKER

