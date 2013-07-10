//
//  EXTestDynamicLabelLayer.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#ifndef __Cocos2dxExt__EXTestDynamicLabelLayer__
#define __Cocos2dxExt__EXTestDynamicLabelLayer__

#include "cocos2d.h"
USING_NS_CC;

class EXTestDynamicLabelLayer : public CCLayer
{
public:
    EXTestDynamicLabelLayer();
    ~EXTestDynamicLabelLayer();
    virtual bool init();
    CREATE_FUNC(EXTestDynamicLabelLayer);
    
private:
    void initData();
};

#endif /* defined(__Cocos2dxExt__EXTestDynamicLabelLayer__) */
