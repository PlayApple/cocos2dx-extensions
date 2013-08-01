//
//  EXTestWebViewLayer.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-8-1.
//
//

#ifndef __Cocos2dxExt__EXTestWebViewLayer__
#define __Cocos2dxExt__EXTestWebViewLayer__

#include "cocos2d.h"
USING_NS_CC;

class EXTestWebViewLayer : public CCLayer
{
public:
    EXTestWebViewLayer();
    ~EXTestWebViewLayer();
    virtual bool init();
    CREATE_FUNC(EXTestWebViewLayer);
    
private:
    void initData();
};



#endif /* defined(__Cocos2dxExt__EXTestWebViewLayer__) */
