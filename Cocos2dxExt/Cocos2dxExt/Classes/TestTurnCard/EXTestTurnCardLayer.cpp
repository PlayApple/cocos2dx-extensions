//
//  EXTestTurnCardLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#include "EXTestTurnCardLayer.h"
#include "EXTurnCard.h"

EXTestTurnCardLayer::EXTestTurnCardLayer()
{
    
}

EXTestTurnCardLayer::~EXTestTurnCardLayer()
{
    
}

bool EXTestTurnCardLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXTestTurnCardLayer::initData()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    EXTurnCard* turnCard = EXTurnCard::create("2.jpg", "1.jpg", 1);
    turnCard->setPosition(ccp(size.width * .5, size.height * .5));
    addChild(turnCard);
    turnCard->openCard();
}