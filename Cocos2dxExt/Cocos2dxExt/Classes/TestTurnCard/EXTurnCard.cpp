//
//  EXTurnCard.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#include "EXTurnCard.h"

#define kInAngleZ        270 //里面卡牌的起始Z轴角度
#define kInDeltaZ        90  //里面卡牌旋转的Z轴角度差

#define kOutAngleZ       0   //封面卡牌的起始Z轴角度
#define kOutDeltaZ       90  //封面卡牌旋转的Z轴角度差

enum {
    tag_inCard = 1,
    tag_outCard
};

EXTurnCard::EXTurnCard()
{
    
}

EXTurnCard::~EXTurnCard()
{
    m_openAnimIn->release();
    m_openAnimOut->release();
}

EXTurnCard* EXTurnCard::create(const char* inCardImageName, const char* outCardImageName, float duration)
{
    EXTurnCard *pSprite = new EXTurnCard();
    if (pSprite && pSprite->init(inCardImageName, outCardImageName, duration))
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

bool EXTurnCard::init(const char* inCardImageName, const char* outCardImageName, float duration)
{
    if (!CCSprite::init())
    {
        return false;
    }
    initData(inCardImageName, outCardImageName, duration);
    return true;
}

#pragma mark - initData
void EXTurnCard::initData(const char* inCardImageName, const char* outCardImageName, float duration)
{
    m_isOpened = false;
    
    CCSprite* inCard = CCSprite::create(inCardImageName);
    inCard->setPosition(CCPointZero);
    inCard->setVisible(false);
    inCard->setTag(tag_inCard);
    addChild(inCard);
    
    CCSprite* outCard = CCSprite::create(outCardImageName);
    outCard->setPosition(CCPointZero);
    outCard->setTag(tag_outCard);
    addChild(outCard);
    
    m_openAnimIn = (CCActionInterval*)CCSequence::create(CCDelayTime::create(duration * .5),
                                                         CCShow::create(),
                                                         CCOrbitCamera::create(duration * .5, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
                                                         NULL);
    m_openAnimIn->retain();
    
    m_openAnimOut = (CCActionInterval *)CCSequence::create(CCOrbitCamera::create(duration * .5, 1, 0, kOutAngleZ, kOutDeltaZ, 0, 0),
                                                           CCHide::create(),
                                                           CCDelayTime::create(duration * .5),
                                                           NULL);
    m_openAnimOut->retain();
}

#pragma mark - public func
void EXTurnCard::openCard()
{
    CCSprite* inCard = (CCSprite*)getChildByTag(tag_inCard);
    CCSprite* outCard = (CCSprite*)getChildByTag(tag_outCard);
    inCard->runAction(m_openAnimIn);
    outCard->runAction(m_openAnimOut);
}