//
//  EXGraySprite.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-10.
//
//

#ifndef __Cocos2dxExt__EXGraySprite__
#define __Cocos2dxExt__EXGraySprite__

#include "sprite_nodes/CCSprite.h"
#include "textures/CCTexture2D.h"
#include "cocoa/CCGeometry.h"
#include "cocos2d.h"
USING_NS_CC;

class EXGraySprite : public CCSprite
{
public:
	EXGraySprite();
	virtual ~EXGraySprite();
	static EXGraySprite* create(const char* pszFileName);
    static EXGraySprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    static EXGraySprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    
	bool initWithTexture(cocos2d::CCTexture2D* pTexture, const cocos2d::CCRect&  tRect);
	virtual void draw();
};


#endif /* defined(__Cocos2dxExt__EXGraySprite__) */
