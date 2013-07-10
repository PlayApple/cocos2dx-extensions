//
//  EXTestGraySpriteLayer.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#ifndef __Cocos2dxExt__EXTestGraySpriteLayer__
#define __Cocos2dxExt__EXTestGraySpriteLayer__

#include "cocos2d.h"
USING_NS_CC;

class EXTestGraySpriteLayer : public CCLayer
{
public:
    EXTestGraySpriteLayer();
    ~EXTestGraySpriteLayer();
    virtual bool init();
    CREATE_FUNC(EXTestGraySpriteLayer);
    
private:
    void initData();
};

#endif /* defined(__Cocos2dxExt__EXTestGraySpriteLayer__) */
