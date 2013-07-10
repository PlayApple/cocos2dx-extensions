//
//  EXDynamicLabel.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-5.
//
//

#ifndef __Cocos2dxExt__EXDynamicLabel__
#define __Cocos2dxExt__EXDynamicLabel__

#include "cocos2d.h"
USING_NS_CC;

class EXDynamicLabel : public CCLabelTTF {
public:
    EXDynamicLabel();
    ~EXDynamicLabel();
    
    static EXDynamicLabel* create(const char *string, const char *fontName, float fontSize);
    static EXDynamicLabel* create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment);
    static EXDynamicLabel* create(const char *string, const char *fontName, float fontSize,
                               const CCSize& dimensions, CCTextAlignment hAlignment,
                               CCVerticalTextAlignment vAlignment);
    static EXDynamicLabel* createWithFontDefinition(const char *string, ccFontDefinition &textDefinition);
    
private:
    int m_curValue;
    bool m_isInUpdate;
    void initData();
    void updateDynamicValue(float dt);
    
public:
    void setDynamicValue(int value);
    inline int getDynamicValue(){return m_curValue;}
};

#endif /* defined(__Cocos2dxExt__EXDynamicLabel__) */
