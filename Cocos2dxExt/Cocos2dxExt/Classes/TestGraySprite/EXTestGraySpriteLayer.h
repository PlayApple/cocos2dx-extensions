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
    bool m_isGray;
    CCSprite* m_graySprite1;
    void initData();
    void menuCallback(CCObject* sender);
};

#endif /* defined(__Cocos2dxExt__EXTestGraySpriteLayer__) */
