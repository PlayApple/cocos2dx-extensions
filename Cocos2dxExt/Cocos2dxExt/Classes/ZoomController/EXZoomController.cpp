//
//  EXZoomController.cpp
//  Cocos2dxExt
//
//  Created by Yanghui.Liu on 13-5-23.
//
//

#include "EXZoomController.h"

//Will return value between 0 and 1, think of it as a percentage of rotation
static inline float vectorsDeviation(CCPoint v1, CCPoint v2) {
    return ccpLength(ccpSub(ccpNormalize(v1), ccpNormalize(v2)))/2.0f;
}

#pragma mark - EXZoomController
EXZoomController::EXZoomController() {
}

EXZoomController::~EXZoomController() {
	_touchesDic->release();
}

EXZoomController* EXZoomController::controllerWithNode(CCNode* node) {
    EXZoomController* pRet = new EXZoomController();
    if (pRet && pRet->initWithNode(node)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool EXZoomController::initWithNode(CCNode* node) {
    if (!CCLayer::init()) {
        return false;
    }

	_touchesDic = CCDictionary::create();
    _touchesDic->retain();
	
	_node = node;
    _tr = ccp(0, 0);
    _bl = ccp(node->getContentSize().width, node->getContentSize().height);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_winTr.x = winSize.width;
	_winTr.y = winSize.height;
    _winBl.x = 0;
    _winBl.y = 0;
    
    centerOnPinch = true;
    zoomOnDoubleTap = true;
    zoomRate = 1/500.0f;
    zoomInLimit = 1.0f;
    zoomOutLimit = 0.5f;
    swipeVelocityMultiplier = 400;
    scrollDuration = .4;
    scrollDamping = .4;
    pinchDamping = .9;
    pinchDistanceThreshold = 3;
    doubleTapZoomDuration = .2;
    
//    setTouchEnabled(true);
    
    return true;
}

void EXZoomController::setBoundingRect(CCRect rect) {
    _bl = rect.origin;
	_tr = ccpAdd(_bl, ccp(rect.size.width, rect.size.height));
}

CCRect EXZoomController::getBoundingRect() {
    CCPoint size = ccpSub(_tr, _bl);
    return CCRectMake(_bl.x, _bl.y, size.x, size.y);
}

void EXZoomController::setWindowRect(CCRect rect) {
    _winBl = rect.origin;
	_winTr = ccpAdd(_winBl, ccp(rect.size.width, rect.size.height));
}

CCRect EXZoomController::getWindowRect() {
    CCPoint size = ccpSub(_winTr, _winBl);
    return CCRectMake(_winBl.x, _winBl.y, size.x, size.y);
}

float EXZoomController::getOptimalZoomOutLimit() {
    //default to 100%
    float xMaxZoom = 1;
    float yMaxZoom = 1;
    
    float width = (_tr.x - _bl.x);
    float height = (_tr.y - _bl.y);
    
    //don't divide by zero
    if (width)
        xMaxZoom = (_winTr.x - _winBl.x) / width;
    if (height)
        yMaxZoom = (_winTr.y - _winBl.y) / height;
    
    //give the best out of the 2 zooms
    return (xMaxZoom > yMaxZoom) ? xMaxZoom : yMaxZoom;
}

CCPoint EXZoomController::boundPos(CCPoint pos) {
	float scale = _node->getScale();
    
    //Correct for anchor
    CCPoint anchor = ccp(_node->getContentSize().width * _node->getAnchorPoint().x,
                         _node->getContentSize().height * _node->getAnchorPoint().y);
    anchor = ccpMult(anchor, (1.0f - scale));
    
    //Calculate corners
    CCPoint topRight = ccpAdd(ccpSub(ccpMult(_tr, scale), _winTr), anchor);
    CCPoint bottomLeft = ccpSub(ccpAdd(ccpMult(_bl, scale), _winBl), anchor);
    
    //bound x
	if (pos.x > bottomLeft.x)
		pos.x = bottomLeft.x;
	else if (pos.x < -topRight.x)
		pos.x = -topRight.x;
	
    //bound y
	if (pos.y > bottomLeft.y)
		pos.y = bottomLeft.y;
	else if (pos.y < -topRight.y)
		pos.y = -topRight.y;
	
	return pos;
}

void EXZoomController::updatePosition(CCPoint pos) {
    //user interface to boundPos basically
	pos = boundPos(pos);
	_node->setPosition(pos);
}

void EXZoomController::enableWithTouchPriority(int priority, bool swallowsTouches) {
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, priority, swallowsTouches);
    setTouchEnabled(true);
//    CCTouchDispatcher::sharedDispatcher->addTargetedDelegate(this, priority, swallowsTouches);
}

void EXZoomController::disable() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void EXZoomController::updateTime(float dt) {
    //keep the time
	_time += dt;
}

void EXZoomController::registerWithTouchDispatcher(void){
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
//     CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void EXZoomController::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++){
        CCTouch* pTouch = (CCTouch*)(*iter);
//        CCPoint location = pTouch->getLocation();
        _touchesDic->setObject(pTouch, CCString::createWithFormat("%d",pTouch->getID())->getCString());
        CCLog("touc id %s,",CCString::createWithFormat("%d",pTouch->getID())->getCString());
    }
	
	bool multitouch = _touchesDic->count() > 1;
	
	if (multitouch){
        //reset history so auto scroll doesn't happen
        _timePointStampCounter = 0;
        
		endScroll(_firstTouch);
        
        CCArray* keys = _touchesDic->allKeys();
        CCTouch *touch1 = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(0))->getCString());
		CCTouch *touch2 = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(1))->getCString());
        
		CCPoint pt = touch1->getLocationInView();
		CCPoint pt2 = touch2->getLocationInView();
        
		beginZoom(pt, pt2);
	} else {
        //record the point for determining velocity
        CCArray* keys = _touchesDic->allKeys();
//        ((CCString*)keys->objectAtIndex(0))->getCString()
        
        _touchesDic->objectForKey(((CCString*)keys->objectAtIndex(0))->getCString());
        
        CCTouch *touch = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(0))->getCString());
        recordScrollPoint(touch);
		beginScroll(_node->convertToNodeSpace(touch->getLocation()));
    }
	
}

void EXZoomController::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
    bool multitouch = _touchesDic->count() > 1;
	if (multitouch) {
        CCArray* keys = _touchesDic->allKeys();
        CCTouch *touch1 = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(0))->getCString());
		CCTouch *touch2 = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(1))->getCString());
        
		CCPoint pt1 = touch1->getLocationInView();
		CCPoint pt2 = touch2->getLocationInView();
		
		moveZoom(pt1, pt2);
	} else {
        CCArray* keys = _touchesDic->allKeys();
        CCTouch *touch = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(0))->getCString());
        recordScrollPoint(touch);
		moveScroll(_node->convertToNodeSpace(touch->getLocation()));
	}
}

void EXZoomController::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    bool multitouch = _touchesDic->count() > 1;
	if (multitouch) {
        CCArray* keys = _touchesDic->allKeys();
        CCTouch *touch1 = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(0))->getCString());
		CCTouch *touch2 = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(1))->getCString());
        
		CCPoint pt1 = touch1->getLocationInView();
		CCPoint pt2 = touch2->getLocationInView();
		
		endZoom(pt1, pt2);
		
		//which touch remains?
//		if (touch == touch2)
//			beginScroll(_node->convertToNodeSpace(touch1->getLocation()));
//		else
			beginScroll(_node->convertToNodeSpace(touch2->getLocation()));
	} else {
        CCArray* keys = _touchesDic->allKeys();
        CCTouch *touch = (CCTouch*)_touchesDic->objectForKey(((CCString*)keys->objectAtIndex(0))->getCString());
        recordScrollPoint(touch);
		
        CCPoint pt = _node->convertToNodeSpace(touch->getLocation());
		endScroll(pt);
        
        //handle double-tap zooming
//        if (zoomOnDoubleTap /**&& [touch tapCount] == 2*/)
//            handleDoubleTapAt(pt);
	}
	
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++){
        CCTouch* pTouch = (CCTouch*)(*iter);
        _touchesDic->removeObjectForKey(CCString::createWithFormat("%d",pTouch->getID())->getCString());
    }
}

void EXZoomController::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
    ccTouchesEnded(pTouches, pEvent);
}

void EXZoomController::handleDoubleTapAt(CCPoint pt) {
    float mid = (zoomInLimit + zoomOutLimit)/2;
    
    //closer to being zoomed out? then zoom in, else zoom out
    if (_node->getScale() < mid)
        zoomInOnPoint(pt, doubleTapZoomDuration);
    else
        zoomOutOnPoint(pt, doubleTapZoomDuration);
}

void EXZoomController::zoomInOnPoint(CCPoint pt, float duration) {
    zoomOnPoint(pt, duration, zoomInLimit);
}

void EXZoomController::zoomOutOnPoint(CCPoint pt, float duration) {
    zoomOnPoint(pt, duration, zoomOutLimit);
}

void EXZoomController::zoomOnPoint(CCPoint pt, float duration, float scale) {
    _node->runAction(EXZoomControllerScale::actionWithDuration(duration, scale, this, pt));
}

void EXZoomController::recordScrollPoint(CCTouch* touch) {
    CCPoint pt = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    CCPanZoomTimePointStamp* record = &_history[_timePointStampCounter++ % kEXZoomControllerHistoryCount];
    record->time = _time;
    record->pt = pt;
}

CCPoint EXZoomController::getHistoricSpeed() {
    CCPoint lastPt;
    CCPoint tPt = ccp(0,0);
    CCPoint speed = ccp(0,0);
    float   lastTime;
    int     count = 0;
    
    //Walk thru our history
    for (int i = 0; i < kEXZoomControllerHistoryCount && i < _timePointStampCounter; i++) {
        CCPanZoomTimePointStamp *record = &_history[(_timePointStampCounter-i-1) % kEXZoomControllerHistoryCount];
        
        CCPoint pt = record->pt;
        float time = record->time;
        
        //Only calculate after first
        if (i != 0) {
            //Sentinels: stop if we have large time chunks
            if ((lastTime-time) > .25)
                break;
            //or sporadic vectors past an amount of history
            if (i > 3 && vectorsDeviation(lastPt, pt) > .1)
                break;
            
            //Get a vector between two touches, but weight it with the time difference,
            //this will eliminate small quick movements and favor sweeping touches
            tPt = ccpAdd(tPt, ccpMult(ccpSub(lastPt, pt), (lastTime-time)));
            count++;
        }
        
        lastPt = pt;
        lastTime = time;
    }
    
    //Calculate speed
    if (count)
        speed = ccpMult(tPt, 1.0f/count);
    
    CCLog("tPt %f,%f",tPt.x, tPt.y);
    CCLog("count %d",count);
    CCLog("speed %f,%f",speed.x, speed.y);
    return speed;
}

void EXZoomController::beginScroll(CCPoint pos) {
	_time = 0;
    _timePointStampCounter = 0;
	_firstTouch = pos;
	
    //keep track of time passed
    schedule(schedule_selector(EXZoomController::updateTime));
}

void EXZoomController::moveScroll(CCPoint pos) {
    //dampen value
	pos = ccpSub(pos, _firstTouch);
	pos = ccpMult(pos, scrollDamping * _node->getScale());
    
    //debug
    //NSLog(@"Moving to: (%.2f, %.2f)", pos.x, pos.y);
	
	updatePosition(ccpAdd(_node->getPosition(), pos));
}

void EXZoomController::endScroll(CCPoint pos) {
    unschedule(schedule_selector(EXZoomController::updateTime));
	
    //Only perform a velocity scroll if we have a good amount of history
	if (_timePointStampCounter > 3) {
        //calculate velocity
        CCPoint velocity = ccpMult(getHistoricSpeed(), swipeVelocityMultiplier * _node->getScale());
        
        //Make sure we have a reasonable speed (more than 5 pts away)
		if (ccpLengthSQ(velocity) > 5*5) {
            //caculate  position of swipe action
			CCPoint newPos = ccpAdd(_node->getPosition(), velocity);
			newPos = boundPos(newPos);
			
            //create the action
			CCMoveTo* moveTo = CCMoveTo::create(scrollDuration, newPos);
			CCEaseOut* ease = CCEaseOut::create(moveTo, 3);
			
            //unconditional stop; cocos handles this properly
			_node->stopAction(_lastScrollAction);
			_node->runAction(ease);
            
            //release our last action since we retain it below
            if (_lastScrollAction) {
                _lastScrollAction->release();
                _lastScrollAction = NULL;
            }
            
            _lastScrollAction = ease;
            _lastScrollAction->retain();
		}
	}
}

void EXZoomController::beginZoom(CCPoint pt, CCPoint pt2) {
    //initialize our zoom vars
	_firstLength = ccpDistance(pt, pt2);
	_oldScale = _node->getScale();
    
    //get the mid point of pinch
    _firstTouch = _node->convertToNodeSpace(ccpMidpoint(pt, pt2));
}

void EXZoomController::moveZoom(CCPoint pt, CCPoint pt2) {
    //what's the difference in length
	float length = ccpDistance(pt, pt2);
	float diff = (length-_firstLength);
    
    //ignore small movements
    if (fabs(diff) < pinchDistanceThreshold)
        return;
    
	//calculate new scale
	float factor = diff * zoomRate * pinchDamping;
	float newScale = _oldScale + factor;
	
    //bound scale
	if (newScale > zoomInLimit)
		newScale = zoomInLimit;
	else if (newScale < zoomOutLimit)
		newScale = zoomOutLimit;
    
    //set the new scale
	_node->setScale(newScale);
    
    //center on midpoint of pinch
    if (centerOnPinch)
        centerOnPoint(_firstTouch, scrollDamping);
    else
        updatePosition(_node->getPosition());
}

void EXZoomController::endZoom(CCPoint pt, CCPoint pt2) {
	//moveZoom(pt, pt2);
}

void EXZoomController::centerOnPoint(CCPoint pt) {
    centerOnPoint(pt, 1.0f);
}

void EXZoomController::centerOnPoint(CCPoint pt, float damping) {
    CCPoint mid = _node->convertToNodeSpace(ccpMidpoint(_winTr, _winBl));
    CCPoint diff = ccpMult(ccpSub(mid, pt), damping);
    
    CCLog("_winTr %f,%f",_winTr.x,_winTr.y);
    CCLog("_winBl %f,%f",_winBl.x,_winBl.y);
    CCLog("mid %f,%f",mid.x,mid.y);
    CCLog("diff %f,%f",diff.x,diff.y);
    CCLog("_node->getPosition() %f,%f",_node->getPosition().x,_node->getPosition().y);
    
    updatePosition(ccpAdd(_node->getPosition(), diff));
}

void EXZoomController::centerOnPoint(CCPoint pt, float duration, float rate) {
    CCPoint mid = _node->convertToNodeSpace(ccpMidpoint(_winTr, _winBl));
    CCPoint diff = ccpSub(mid, pt);
    
    CCPoint final = boundPos(ccpAdd(_node->getPosition(), diff));
    
    CCMoveTo* moveTo = CCMoveTo::create(duration, final);
    CCEaseOut* ease = CCEaseOut::create(moveTo, rate);
    
    _node->runAction(ease);
}

#pragma mark - EXZoomControllerScale
EXZoomControllerScale::EXZoomControllerScale() {
}

EXZoomControllerScale::~EXZoomControllerScale() {
    _controller->release();
}

EXZoomControllerScale* EXZoomControllerScale::actionWithDuration(float duration, float s, EXZoomController* controller, CCPoint pt) {
    EXZoomControllerScale* pRet = new EXZoomControllerScale();
    if (pRet && pRet->initWithDuration(duration, s, controller, pt)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool EXZoomControllerScale::initWithDuration(float duration, float s, EXZoomController* controller, CCPoint pt) {
    if (!CCScaleTo::initWithDuration(duration, s)) {
        return false;
    }

    this->_controller = controller;
    this->_controller->retain();
    _point = pt;

    return true;
}

void EXZoomControllerScale::update(float t) {
    CCScaleTo::update(t);
    
    //use damping, but make sure we get there
    if (t < 1.0f)
        _controller->centerOnPoint(_point, _controller->scrollDamping);
    else
        _controller->centerOnPoint(_point);
}

