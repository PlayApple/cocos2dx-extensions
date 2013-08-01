//
//  EXUIWebViewBridge.h
//  COG
//
//  Created by Liu Yanghui on 12-12-28.
//  Copyright (c) 2012年 BoyoJoy. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import "EXWebViewLayer.h"

@interface EXUIWebViewBridge : NSObject<UIWebViewDelegate,UIAlertViewDelegate>{
    EXWebViewLayer * mLayerWebView;
    UIView *mView;
    UIWebView *mWebView;
    UIToolbar *mToolbar;
    UIBarButtonItem *mBackButton;
}

-(void) setLayerWebView : (EXWebViewLayer*) iLayerWebView URLString:(const char*) urlString;
-(void) backClicked:(id)sender;

@end


