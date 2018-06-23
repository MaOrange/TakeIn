#pragma once
#include<cocos2d.h>
USING_NS_CC;


typedef enum
{
	tag_dot, tag_bg, tag_dir
}tagForRocker;

class Rocker:public Layer
{
public:
    Rocker();

	CREATE_FUNC(Rocker);

	static Rocker* createWith(const char *rockerDotName,const char * rockerBgName);

	float getDiretionByRad() const;

	float getDirectionByTheta() const;

	void getRockerPosition() const;

	void setRockerPosition();

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

	int D;

	float originX=0.2;

	float originY = 0.3;

	Size size;

	float angle;
};


