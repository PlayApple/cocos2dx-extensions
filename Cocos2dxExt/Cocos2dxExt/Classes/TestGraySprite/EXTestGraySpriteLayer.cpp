//
//  EXTestGraySpriteLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#include "EXTestGraySpriteLayer.h"
#include "EXGraySprite.h"
#include "EXGrayUtility.h"

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
    
    CCLayerColor* bgLayer = CCLayerColor::create(ccc4(255, 255, 255, 255));
    addChild(bgLayer);
    
    CCSprite* normalSprite = CCSprite::create("Icon.png");
    normalSprite->setPosition(ccp(size.width * .35, size.height * .5));
    addChild(normalSprite);
    
    m_isGray = true;
    m_graySprite1 = CCSprite::create("Icon.png");
    m_graySprite1->setPosition(ccp(size.width * .5, size.height * .5));
    addChild(m_graySprite1);
    EXGrayUtility::disableSprite(m_graySprite1);
    
    EXGraySprite* graySprite2 = EXGraySprite::create("Icon.png");
    graySprite2->setPosition(ccp(size.width * .65, size.height * .5));
    addChild(graySprite2);
    
    CCLabelTTF* label = CCLabelTTF::create("Click Change Gray", "Arial", 30);
    label->setColor(ccc3(255, 0, 0));
    CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(EXTestGraySpriteLayer::menuCallback));
    item->setPosition(ccp(0, size.height * -.2));
    CCMenu* menu = CCMenu::createWithItem(item);
    addChild(menu);
}

void EXTestGraySpriteLayer::menuCallback(CCObject* sender)
{
    m_isGray = !m_isGray;
    if (m_isGray) {
        EXGrayUtility::disableSprite(m_graySprite1);
    }else{
        EXGrayUtility::enableSprite(m_graySprite1);
    }
    
}