//
//  EXTestGraySpriteLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#include "EXTestGraySpriteLayer.h"
#include "EXGraySprite.h"

EXTestGraySpriteLayer::EXTestGraySpriteLayer()
{
    
}

EXTestGraySpriteLayer::~EXTestGraySpriteLayer()
{
    
}

bool EXTestGraySpriteLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXTestGraySpriteLayer::initData()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* normalSprite = CCSprite::create("Icon.png");
    normalSprite->setPosition(ccp(size.width * .35, size.height * .5));
    addChild(normalSprite);
    
    EXGraySprite* graySprite = EXGraySprite::create("Icon.png");
    graySprite->setPosition(ccp(size.width * .65, size.height * .5));
    addChild(graySprite);
}