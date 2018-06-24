#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Rocker.h"
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	void MenuCB(Ref * sender);

protected:
	Rocker * newLayer;

	Size size;
};

#endif // __HELLOWORLD_SCENE_H__
