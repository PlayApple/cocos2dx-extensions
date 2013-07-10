#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public CCLayer
{
public:
    HelloWorld();
    ~HelloWorld();
    virtual bool init();
    static CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(HelloWorld);
    
private:
    void initData();
};

#endif // __HELLOWORLD_SCENE_H__
