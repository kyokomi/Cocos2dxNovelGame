#ifndef __TABLEVIEWTESTSCENE_H__
#define __TABLEVIEWTESTSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class TableViewTestLayer : public cocos2d::CCLayerColor, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
    std::vector<std::string> m_textArray;
    
    enum kTag
    {
        kTag_TextLayer = 1,
        kTag_TextLabel,
        kTag_TableView,
    };
    
public:
    virtual bool init(std::vector<std::string> textArray);  
   
    TableViewTestLayer();
//	void toExtensionsMainLayer(cocos2d::CCObject *sender);
    
    static TableViewTestLayer* createWithTextArray(std::vector<std::string> textArray);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    void makeTextLog(std::vector<std::string> textArray);
};

#endif // __TABLEVIEWTESTSCENE_H__
