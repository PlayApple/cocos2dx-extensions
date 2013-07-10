//
//  EXDynamicLabel.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-5.
//
//

#include "EXDynamicLabel.h"

EXDynamicLabel::EXDynamicLabel()
{
    
}

EXDynamicLabel::~EXDynamicLabel()
{
    
}

EXDynamicLabel * EXDynamicLabel::create(const char *string, const char *fontName, float fontSize)
{
    return EXDynamicLabel::create(string, fontName, fontSize,
                              CCSizeZero, kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
}

EXDynamicLabel * EXDynamicLabel::create(const char *string, const char *fontName, float fontSize,
                                const CCSize& dimensions, CCTextAlignment hAlignment)
{
    return EXDynamicLabel::create(string, fontName, fontSize, dimensions, hAlignment, kCCVerticalTextAlignmentTop);
}

EXDynamicLabel* EXDynamicLabel::create(const char *string, const char *fontName, float fontSize,
                               const CCSize &dimensions, CCTextAlignment hAlignment,
                               CCVerticalTextAlignment vAlignment)
{
    EXDynamicLabel *pRet = new EXDynamicLabel();
    if(pRet && pRet->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
    {
        pRet->initData();
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

EXDynamicLabel * EXDynamicLabel::createWithFontDefinition(const char *string, ccFontDefinition &textDefinition)
{
    EXDynamicLabel *pRet = new EXDynamicLabel();
    if(pRet && pRet->initWithStringAndTextDefinition(string, textDefinition))
    {
        pRet->initData();
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void EXDynamicLabel::initData()
{
    m_curValue = 0;
    m_isInUpdate = false;
    setString("0");
}

void EXDynamicLabel::updateDynamicValue(float dt)
{
    int temScore = atoi(getString());
    int addScore = m_curValue - temScore;
    
    if(abs(addScore)>10)
    {   
        temScore += addScore / 10;
        setString(CCString::createWithFormat("%d", temScore)->getCString());
    }
    else if(abs(addScore) > 2 && abs(addScore) <= 10)  
    {
        temScore += addScore / abs(addScore);
        setString(CCString::createWithFormat("%d", temScore)->getCString());
    }
    else
    {
        unschedule(schedule_selector(EXDynamicLabel::updateDynamicValue));
        m_isInUpdate = false;
        setString(CCString::createWithFormat("%d", m_curValue)->getCString());
    }
}

void EXDynamicLabel::setDynamicValue(int value)
{
    m_curValue = value;
    if (!m_isInUpdate)
    {
        m_isInUpdate = true;
        schedule(schedule_selector(EXDynamicLabel::updateDynamicValue));
    }
}