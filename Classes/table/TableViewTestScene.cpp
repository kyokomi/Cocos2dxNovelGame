#include "TableViewTestScene.h"
#include "CustomTableViewCell.h"

#include "AppMacros.h"

USING_NS_CC;
USING_NS_CC_EXT;

void runTableViewTest()
{
	CCScene *pScene = CCScene::create();
	TableViewTestLayer *pLayer = TableViewTestLayer::create();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

// on "init" you need to initialize your instance
bool TableViewTestLayer::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCTableView* tableView = CCTableView::create(this, CCSizeMake(winSize.width, winSize.height * 0.9));
	tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(tableView->getPositionX(), winSize.height * 0.1));
	tableView->setDelegate(this);
    tableView->setBounceable(false);
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
    
    CCString *string = CCString::createWithFormat("AaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaE\nAaaaaaaE\nAaaaaaaaaE%d", idx);
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
    return 20;
}
