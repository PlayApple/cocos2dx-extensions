//
//  EXTestZoomControllerLayer.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#ifndef __Cocos2dxExt__EXTestZoomControllerLayer__
#define __Cocos2dxExt__EXTestZoomControllerLayer__

#include "cocos2d.h"
USING_NS_CC;

class EXTestZoomControllerLayer : public CCLayer
{
public:
    EXTestZoomControllerLayer();
    ~EXTestZoomControllerLayer();
    virtual bool init();
    CREATE_FUNC(EXTestZoomControllerLayer);
    
private:
    void initData();
};



#endif /* defined(__Cocos2dxExt__EXTestZoomControllerLayer__) */
