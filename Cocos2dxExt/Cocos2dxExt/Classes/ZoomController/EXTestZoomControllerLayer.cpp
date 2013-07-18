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
    CCSprite* normalSprite = CCSprite::create("coc.jpg");
    normalSprite->setAnchorPoint(CCPointZero);
    normalSprite->setPosition(CCPointZero);
    addChild(normalSprite);
    
    EXZoomController* controller = EXZoomController::controllerWithNode(this);
    controller->setWindowRect(CCRectMake(0, 0, 1024, 768));
    CCRect r = normalSprite->getTextureRect();
    controller->setBoundingRect(r);
    controller->zoomOutLimit = controller->getOptimalZoomOutLimit();
    controller->zoomInLimit = 2.0f;
    addChild(controller);
    controller->enableWithTouchPriority(0,true);
}