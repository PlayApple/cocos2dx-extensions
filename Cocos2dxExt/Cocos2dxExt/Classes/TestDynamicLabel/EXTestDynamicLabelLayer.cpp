//
//  EXTestDynamicLabelLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#include "EXTestDynamicLabelLayer.h"
#include "EXDynamicLabel.h"

EXTestDynamicLabelLayer::EXTestDynamicLabelLayer()
{
    
}

EXTestDynamicLabelLayer::~EXTestDynamicLabelLayer()
{
    
}

bool EXTestDynamicLabelLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXTestDynamicLabelLayer::initData()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    EXDynamicLabel* label = EXDynamicLabel::create("", "Arial", 30);
    label->setPosition(ccp(size.width * .5, size.height * .5));
    addChild(label);
    label->setDynamicValue(9000);
}