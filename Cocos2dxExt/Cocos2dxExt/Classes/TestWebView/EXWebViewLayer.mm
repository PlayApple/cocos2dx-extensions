//
//  EXWebViewLayer.mm
//  COG
//
//  Created by Liu Yanghui on 12-12-28.
//  Copyright (c) 2012年 BoyoJoy. All rights reserved.
//

#include "EXWebViewLayer.h"
#include "EXUIWebViewBridge.h"

static EXUIWebViewBridge *g_EXUIWebViewBridge=nil;

EXWebViewLayer::EXWebViewLayer(){
    
}

EXWebViewLayer::~EXWebViewLayer(){
    [g_EXUIWebViewBridge release];
}

void EXWebViewLayer::webViewDidFinishLoad(){
    
}

void EXWebViewLayer::onBackbuttonClick(){
    this->removeFromParentAndCleanup(true);
}

bool EXWebViewLayer::init(std::string url){
    if ( !CCLayer::init() ){
        return false;
    }
    g_EXUIWebViewBridge = [[EXUIWebViewBridge alloc] init];
    [g_EXUIWebViewBridge setLayerWebView : this URLString:url.c_str()];
    return true;
}

EXWebViewLayer *EXWebViewLayer::create(std::string url){
    EXWebViewLayer *pRet = new EXWebViewLayer();
    if (pRet && pRet->init(url)){
        pRet->autorelease();
        return pRet;
    }else{
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}