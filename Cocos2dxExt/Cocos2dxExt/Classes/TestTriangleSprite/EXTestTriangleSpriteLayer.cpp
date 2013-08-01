//
//  EXTestTriangleSpriteLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-19.
//
//

#include "EXTestTriangleSpriteLayer.h"

EXTestTriangleSpriteLayer::EXTestTriangleSpriteLayer()
{
    
}

EXTestTriangleSpriteLayer::~EXTestTriangleSpriteLayer()
{
    
}

bool EXTestTriangleSpriteLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXTestTriangleSpriteLayer::initData()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
//    CCSprite* sss = CCSprite::create("coc.jpg");
//    sss->setPosition(ccp(size.width * .5, size.height * .5));
//    addChild(sss);
    
    for (int i = 0; i < 7; ++i) {
        CCNode *stencil = this->shape();
        //    stencil->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 90.0f)));
        
        CCClippingNode *clipper = CCClippingNode::create();
        clipper->setAnchorPoint(ccp(0.5, 0.5));
        clipper->setPosition( ccp(size.width * 1.5, i * 100));
        clipper->setStencil(stencil);
        //    clipper->setInverted(true);
        this->addChild(clipper);
        
        CCSprite* normalSprite = CCSprite::create("bg_theme1.png");
        normalSprite->setPosition(ccp(0, 0));
        
        clipper->addChild(normalSprite);
        
        CCActionInterval *pAction = CCSequence::createWithTwoActions(CCMoveBy::create(4, ccp(-1500, 0)), CCMoveBy::create(2, ccp(1500, 0)));
        
        
        
        clipper->runAction(CCRepeatForever::create(pAction));
    }
    
    
    
    
}



//CCPoint* getTrianglePoints(CCPoint p1, CCPoint p2, CCPoint p3)
//{
//    static CCPoint triangle[3];
//    triangle[0] = p1;
//    triangle[1] = p2;
//    triangle[2] = p3;
//    return triangle;
//}


CCDrawNode* EXTestTriangleSpriteLayer::shape()
{
    CCDrawNode *shape = CCDrawNode::create();
    static CCPoint triangle[3];
    triangle[0] = ccp(0, 0);
    triangle[1] = ccp(100, 0);
    triangle[2] = ccp(100, 100);
//    triangle[3] = ccp(100, 50);
//    triangle[4] = ccp(200, 50);
//    triangle[5] = ccp(200, 100);
//    triangle[6] = ccp(300, 100);
//    triangle[7] = ccp(300, 0);
    
    static ccColor4F green = {0, 1, 0, 1};
    shape->drawPolygon(triangle, 3, green, 0, green);
    return shape;
}