//
//  EXWebViewLayer.h
//  COG
//
//  Created by Liu Yanghui on 12-12-28.
//  Copyright (c) 2012年 BoyoJoy. All rights reserved.
//

#ifndef COG_EXWebViewLayer_h
#define COG_EXWebViewLayer_h

#include "CCCommon.h"
#include "cocos2d.h"
USING_NS_CC;

class EXWebViewLayer : public CCLayer{
public:
    EXWebViewLayer();
    ~EXWebViewLayer();
    virtual bool init(std::string url);
    static EXWebViewLayer* create(std::string url);
    
    void webViewDidFinishLoad();
    
    void onBackbuttonClick();
    
private:
    int mWebViewLoadCounter;
};
#endif
