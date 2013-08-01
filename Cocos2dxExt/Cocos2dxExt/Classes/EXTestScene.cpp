//
//  EXTestScene.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-4.
//
//

#include "EXTestScene.h"
#include "EXMainMenuScene.h"
#include "EXTestDynamicLabelLayer.h"
#include "EXTestGraySpriteLayer.h"
#include "EXTestTurnCardLayer.h"
#include "EXTestZoomControllerLayer.h"
#include "EXTestTriangleSpriteLayer.h"
#include "EXTestWebViewLayer.h"

EXTestScene::EXTestScene()
{
    
}

EXTestScene::~EXTestScene()
{
    
}

CCScene* EXTestScene::scene(int testId, const char* titleStr)
{
    CCScene *scene = CCScene::create();
    EXTestScene *layer = EXTestScene::create(testId, titleStr);
    scene->addChild(layer);
    return scene;
}

EXTestScene* EXTestScene::create(int testId, const char* titleStr)
{
    EXTestScene* pRet = new EXTestScene();
    if (pRet && pRet->init(testId, titleStr))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool EXTestScene::init(int testId, const char* titleStr)
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData(testId, titleStr);
    return true;
}

void EXTestScene::initData(int testId, const char* titleStr)
{
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(EXTestScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCLabelTTF* labTitle = CCLabelTTF::create(titleStr, "Thonburi", 34);
    labTitle->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(labTitle, 1);
    
    switch (testId) {
        case 0:
            addChild(EXTestDynamicLabelLayer::create());
            break;
            
        case 1:
            addChild(EXTestGraySpriteLayer::create());
            break;
            
        case 2:
            addChild(EXTestTurnCardLayer::create());
            break;
            
        case 3:
            addChild(EXTestZoomControllerLayer::create());
            break;
            
        case 4:
            addChild(EXTestTriangleSpriteLayer::create());
            break;
            
        case 5:
            addChild(EXTestWebViewLayer::create());
            break;

        default:
            break;
    }
    
}

void EXTestScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(EXMainMenuScene::scene());
}
