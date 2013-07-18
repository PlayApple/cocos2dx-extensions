//
//  EXZoomController.h
//  Cocos2dxExt
//
//  Created by Yanghui.Liu on 13-5-23.
//
//

#ifndef ____EXZoomController__
#define ____EXZoomController__

#include "cocos2d.h"
USING_NS_CC;

#define kEXZoomControllerHistoryCount 12

typedef struct {
    float time;
    CCPoint pt;
} CCPanZoomTimePointStamp;

class EXZoomController : public CCLayer {
public:
    EXZoomController();
    ~EXZoomController();

    /*! Create a new control with the node you want to scroll/zoom */
    static EXZoomController* controllerWithNode(CCNode* node);
    
    /*! Initialize a new control with the node you want to scroll/zoom */
    bool initWithNode(CCNode* node);
    
    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
public:
    bool      centerOnPinch;  /*!< Should zoom center on pinch pts, default is YES */
    bool      zoomOnDoubleTap;/*!< Should we zoom in/out on double-tap */
    float     zoomRate;       /*!< How much to zoom based on movement of pinch */
    float     zoomInLimit;    /*!< The smallest zoom level */
    float     zoomOutLimit;   /*!< The hightest zoom level */
    float     swipeVelocityMultiplier; /*!< The velocity factor of the swipe's scroll action */
    float     scrollDuration; /*!< Duration of the scroll action after a swipe */
    float     scrollDamping;  /*!< When scrolling around, this will dampen the movement */
    float     pinchDamping;   /*!< When zooming, this will dampen the zoom */
    float     pinchDistanceThreshold; /*!< The distance moved before a pinch is recognized */
    float     doubleTapZoomDuration;  /*!< Duration of zoom after double-tap */
    
public:
    /*!< The max bounds you want to scroll */
    void setBoundingRect(CCRect rect);
    CCRect getBoundingRect();
    
    /*!< The boundary of your window, by default uses winSize of CCDirector */
    void setWindowRect(CCRect rect);
    CCRect getWindowRect();

    /*!< Get the optimal zoomOutLimit for the current state */
    float getOptimalZoomOutLimit();
    
public:
    /*! Scroll to position */
    void updatePosition(CCPoint pos);
    
    /*! Center point in window view */
    void centerOnPoint(CCPoint pt);
    
    /*! Center point in window view with a given duration */
    void centerOnPoint(CCPoint pt, float duration, float rate);
    
    /*! Zoom in on point with duration */
    void zoomInOnPoint(CCPoint pt, float duration);
    
    /*! Zoom out on point with duration */
    void zoomOutOnPoint(CCPoint pt, float duration);
    
    /*! Zoom to a scale on a point with a given duration */
    void zoomOnPoint(CCPoint pt, float duration, float scale);
    
    /*! Enable touches, convenience method really */
    void enableWithTouchPriority(int priority, bool swallowsTouches);
    
    /*! Disable touches */
    void disable();
    
    

private:
    // properties
    CCNode* _node;
    
    // bounding rect
    CCPoint _tr;
    CCPoint _bl;
    
    // window rect
    CCPoint _winTr;
    CCPoint _winBl;
    
//    bool _centerOnPinch;
//    bool _zoomOnDoubleTap;
//    float _zoomRate;
//    float _zoomInLimit;
//    float _zoomOutLimit;
//    float _swipeVelocityMultiplier;
//    float _scrollDuration;
//    float _scrollDamping;
//    float _pinchDamping;
//    float _pinchDistanceThreshold;
//    float _doubleTapZoomDuration;

    // internals
    float _time;
    int _timePointStampCounter;
    CCPanZoomTimePointStamp _history[kEXZoomControllerHistoryCount];

	// touches
	CCPoint _firstTouch;
	float _firstLength;
	float _oldScale;

    // keep track of touches in order
	CCDictionary* _touchesDic;
    
    // keep around swipe action to get rid of it if needed
    CCAction* _lastScrollAction;
    
public:
    void centerOnPoint(CCPoint pt, float damping);
private:
    void updateTime(float dt);
    CCPoint boundPos(CCPoint pos);
    void recordScrollPoint(CCTouch* touch);
    CCPoint getHistoricSpeed();
    
    void handleDoubleTapAt(CCPoint pt);
    
    void beginScroll(CCPoint pos);
    void moveScroll(CCPoint pos);
    void endScroll(CCPoint pos);
    
    void beginZoom(CCPoint pt, CCPoint pt2);
    void moveZoom(CCPoint pt, CCPoint pt2);
    void endZoom(CCPoint pt, CCPoint pt2);
};

//Special scale action so view stays centered on a given point
class EXZoomControllerScale : public CCScaleTo {
public:
    EXZoomControllerScale();
    ~EXZoomControllerScale();
    static EXZoomControllerScale* actionWithDuration(float duration, float s, EXZoomController* controller, CCPoint pt);
    bool initWithDuration(float duration, float s, EXZoomController* controller, CCPoint pt);

    void update(float t);

public:
    EXZoomController* _controller;
    CCPoint _point;
};

#endif /* defined(____EXZoomController__) */
