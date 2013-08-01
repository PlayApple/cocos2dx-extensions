//
//  EXTestWebViewLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-8-1.
//
//

#include "EXTestWebViewLayer.h"
#include "EXWebViewLayer.h"

EXTestWebViewLayer::EXTestWebViewLayer()
{
    
}

EXTestWebViewLayer::~EXTestWebViewLayer()
{
    
}

bool EXTestWebViewLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXTestWebViewLayer::initData()
{
    EXWebViewLayer* web = EXWebViewLayer::create("http://www.cocos2dev.com");
    web->setPosition(CCPointZero);
    addChild(web);
}