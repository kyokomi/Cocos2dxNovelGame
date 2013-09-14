#include "TableViewTestScene.h"
#include "CustomTableViewCell.h"

#include "AppMacros.h"

USING_NS_CC;
USING_NS_CC_EXT;

TableViewTestLayer::TableViewTestLayer()
:m_textArray(std::vector<std::string>())
{

}


TableViewTestLayer* TableViewTestLayer::createWithTextArray(std::vector<std::string> textArray)
{
    TableViewTestLayer *pRet = new TableViewTestLayer();
    if (pRet && pRet->init(textArray))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

// on "init" you need to initialize your instance
bool TableViewTestLayer::init(std::vector<std::string> textArray)
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }
    m_textArray = textArray;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCTableView* tableView = CCTableView::create(this, CCSizeMake(winSize.width, winSize.height * 0.9));
	tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(tableView->getPositionX(), winSize.height * 0.1));
	tableView->setDelegate(this);
//    tableView->setBounceable(false); // スクロールオーバー
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();

    this->setColor(ccBLACK);
    this->setOpacity(128);
    
    return true;
}

void TableViewTestLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize TableViewTestLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    return CCSizeMake(winSize.width, winSize.height * 0.25);
}

CCTableViewCell* TableViewTestLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    std::string text = "hogehoge";
    
    CCLog("idx = %d size = %ld", idx, m_textArray.size());
    
    if (m_textArray.size() > 0 && idx < m_textArray.size())
    {
        text = m_textArray[idx];
    }
    CCString *string = CCString::createWithFormat("[%d] : %s", idx, text.c_str());
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        
        CCLayerColor * textLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7),
                                                        winSize.width * 0.9, winSize.height * 0.25 * 0.9);
        textLayer->setPosition(winSize.width * 0.05, winSize.height * 0.25 * 0.05);
        textLayer->setTag(123);
        cell->addChild(textLayer);
        
        // 本文テキスト
        CCLabelTTF* textLabel = CCLabelTTF::create(string->getCString(), "Arial", BASE_FONT_SIZE);
        textLabel->setAnchorPoint(ccp(0, 0));
        textLabel->setColor(ccWHITE);
        textLabel->setPosition(ccp(BASE_FONT_SIZE, BASE_FONT_SIZE));
        textLabel->setTag(100124);

        textLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
        textLayer->addChild(textLabel);
    }
    else
    {
        CCLayerColor* textLayer = (CCLayerColor*)cell->getChildByTag(123);
        CCLabelTTF* textLabel = (CCLabelTTF*)textLayer->getChildByTag(100124);
        textLabel->setString(string->getCString());
    }


    return cell;
}

unsigned int TableViewTestLayer::numberOfCellsInTableView(CCTableView *table)
{
    return m_textArray.size();
}
