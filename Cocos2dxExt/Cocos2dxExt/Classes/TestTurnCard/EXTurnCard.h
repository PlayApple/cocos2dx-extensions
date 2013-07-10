//
//  EXTurnCard.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#ifndef __Cocos2dxExt__EXTurnCard__
#define __Cocos2dxExt__EXTurnCard__

#include "cocos2d.h"
USING_NS_CC;

class EXTurnCard : public CCSprite
{
public:
    EXTurnCard();
    ~EXTurnCard();
    static EXTurnCard* create(const char* inCardImageName, const char* outCardImageName, float duration);
    virtual bool init(const char* inCardImageName, const char* outCardImageName, float duration);
    
private:
    bool m_isOpened;
    CCActionInterval* m_openAnimIn;
    CCActionInterval* m_openAnimOut;
    
    
    void initData(const char* inCardImageName, const char* outCardImageName, float duration);
    
public:
    void openCard();
};

#endif /* defined(__Cocos2dxExt__EXTurnCard__) */
