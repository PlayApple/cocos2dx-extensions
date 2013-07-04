//
//  EXMainMenuScene.h
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-7-4.
//
//

#ifndef __Cocos2dxExt__EXMainMenuScene__
#define __Cocos2dxExt__EXMainMenuScene__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class EXMainMenuScene : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    EXMainMenuScene();
    ~EXMainMenuScene();
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(EXMainMenuScene);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
private:
    CCSize m_winSize;
    CCArray* m_listData;
    CCTableView* m_tableView;
    
    void initData();
};

#endif /* defined(__Cocos2dxExt__EXMainMenuScene__) */
