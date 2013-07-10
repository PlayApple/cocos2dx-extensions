//
//  EXTestZoomControllerLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#include "EXTestZoomControllerLayer.h"
#include "EXZoomController.h"

EXTestZoomControllerLayer::EXTestZoomControllerLayer()
{
    
}

EXTestZoomControllerLayer::~EXTestZoomControllerLayer()
{
    
}

bool EXTestZoomControllerLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXTestZoomControllerLayer::initData()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            CCSprite* normalSprite = CCSprite::create("HelloWorld.png");
            normalSprite->setAnchorPoint(CCPointZero);
            normalSprite->setPosition(ccp(j * 480, i * 320));
            addChild(normalSprite);
        }
    }
    
    EXZoomController* controller = EXZoomController::controllerWithNode(this);
    controller->setBoundingRect(CCRectMake(0, 0, 480 * 5, 320 * 4));
    controller->zoomOutLimit = controller->getOptimalZoomOutLimit();
    controller->zoomInLimit = 2.0f;
    addChild(controller);
    controller->enableWithTouchPriority(0,true);
}