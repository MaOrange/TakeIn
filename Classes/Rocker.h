#pragma once
#include<cocos2d.h>
USING_NS_CC;


typedef enum
{
	tag_dot, tag_bg, tag_dir,tag_start,tag_disabled
}tagForRocker;

class Rocker:public Layer
{
public:
    Rocker();

	CREATE_FUNC(Rocker);

	static Rocker* createWith(const char *rockerDotName,const char * rockerBgName);

	float getDiretionByRad() const;//return the direction in normal system in the unit of rad

	float getDirectionByTheta() const;//return the direction in normal system in the unit of degree

	Vec2 getRockerPosition() const; //return the origin location of the rocker

	void setRockerPosition(Vec2);//set the RockerPosition with Vec2

	void setRockerPosition(float, float);//set the RockerPosition with two int

	void setEnabled(bool);

	bool getEnabled()const;

protected:
	void initWith(const char *rockerDotName, const char * rockerBgName);

	bool onTouchBeginCB(Touch * touch, Event * event);

	void onTouchMovedCB(Touch * touch, Event * event);

	void onTouchEndedCB(Touch * touch, Event * event);

	Vec2 locationTranslate(const Vec2 &location);

	EventListenerTouchOneByOne *listener;

	Sprite * rockerDot;

	Sprite * rockerDir;

	Sprite * rockerBg;

	Sprite * rockerStart;

	Sprite * rockerDisabled;

	int D;

	float originX=0.2;

	float originY = 0.3;

	Size size;

	float angle;

	bool enabled = true;

	EventDispatcher* dispatcher=Director::getInstance()->getEventDispatcher();
};


