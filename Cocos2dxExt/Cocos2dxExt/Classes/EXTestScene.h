//
//  EXTestScene.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-4.
//
//

#ifndef __Cocos2dxExt__EXTestScene__
#define __Cocos2dxExt__EXTestScene__

#include "cocos2d.h"
USING_NS_CC;

class EXTestScene : public CCLayer
{
public:
    EXTestScene();
    ~EXTestScene();
    static EXTestScene* create(int testId, const char* titleStr);
    virtual bool init(int testId, const char* titleStr);
    static CCScene* scene(int testId, const char* titleStr);
    void menuCloseCallback(CCObject* pSender);
    
private:
    void initData(int testId, const char* titleStr);
};

#endif /* defined(__Cocos2dxExt__EXTestScene__) */
