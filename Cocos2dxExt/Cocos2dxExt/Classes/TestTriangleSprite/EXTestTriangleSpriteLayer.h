//
//  EXTestTriangleSpriteLayer.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-19.
//
//

#ifndef __Cocos2dxExt__EXTestTriangleSpriteLayer__
#define __Cocos2dxExt__EXTestTriangleSpriteLayer__

#include "cocos2d.h"
USING_NS_CC;

class EXTestTriangleSpriteLayer : public CCLayer
{
public:
    EXTestTriangleSpriteLayer();
    ~EXTestTriangleSpriteLayer();
    virtual bool init();
    CREATE_FUNC(EXTestTriangleSpriteLayer);
    
private:
    void initData();
    CCDrawNode* shape();
};

#endif /* defined(__Cocos2dxExt__EXTestTriangleSpriteLayer__) */
