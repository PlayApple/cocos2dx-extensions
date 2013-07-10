//
//  EXTestTurnCardLayer.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#ifndef __Cocos2dxExt__EXTestTurnCardLayer__
#define __Cocos2dxExt__EXTestTurnCardLayer__

#include "cocos2d.h"
USING_NS_CC;

class EXTestTurnCardLayer : public CCLayer
{
public:
    EXTestTurnCardLayer();
    ~EXTestTurnCardLayer();
    virtual bool init();
    CREATE_FUNC(EXTestTurnCardLayer);
    
private:
    void initData();
};

#endif /* defined(__Cocos2dxExt__EXTestTurnCardLayer__) */
