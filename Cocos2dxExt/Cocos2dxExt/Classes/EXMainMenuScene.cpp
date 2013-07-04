//
//  EXMainMenuScene.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-4.
//
//

#include "EXMainMenuScene.h"

EXMainMenuScene::EXMainMenuScene()
{
    
}
EXMainMenuScene::~EXMainMenuScene()
{
    m_listData->release();
}

CCScene* EXMainMenuScene::scene()
{
    CCScene* scene = CCScene::create();
    EXMainMenuScene* layer = EXMainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool EXMainMenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXMainMenuScene::initData()
{
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    m_listData = CCArray::create();
    m_listData->retain();
    
    m_listData->addObject(CCString::create("DADynamic CCLabelTTF - 动态显示数字"));
    m_listData->addObject(CCString::create("Create Gray Sprite - 创建灰色图"));
    m_listData->addObject(CCString::create("Turn Card - 翻牌效果"));
    m_listData->addObject(CCString::create("Zoom Controller - 场景多点聚焦缩放"));
    
    CCLabelTTF* labTitle = CCLabelTTF::create("git: https://github.com/sunny-liu/cocos2dx-extensions\nBlog: http://www.cocos2dev.com", "Helvetica", 20.0);
    labTitle->setPosition(ccp(m_winSize.width * .5, m_winSize.height * .95));
    addChild(labTitle);
    
    m_tableView = CCTableView::create(this, CCSizeMake(m_winSize.width, m_winSize.height * .9));
	m_tableView->setDirection(kCCScrollViewDirectionVertical);
	m_tableView->setPosition(CCPointZero);
	m_tableView->setDelegate(this);
	m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(m_tableView);
	m_tableView->reloadData();
}


void EXMainMenuScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize EXMainMenuScene::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(m_winSize.width, 60);
}

CCTableViewCell* EXMainMenuScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = (CCString*)m_listData->objectAtIndex(idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(ccp(m_winSize.width * .5, 30));
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    
    return cell;
}

unsigned int EXMainMenuScene::numberOfCellsInTableView(CCTableView *table)
{
    return m_listData->count();
}
