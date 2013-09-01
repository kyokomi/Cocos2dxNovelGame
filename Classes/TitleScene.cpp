//
//  TitleScene.cpp
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#include "TitleScene.h"
#include "cocos2d.h"

#include "NovelScene.h"

using namespace cocos2d;
using namespace std;

CCScene* TitleScene::scene()
{
    CCScene* scene = CCScene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool TitleScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::create("ノベルゲーム", "Arial", 24);
    CCMenuItemLabel* menuItem = CCMenuItemLabel::create(label, this, menu_selector(TitleScene::menuItemCallback));
    menuItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    menuItem->setTag(1);
    
    CCMenu* pMenu = CCMenu::create(menuItem, NULL);
    pMenu->setPosition(CCPointZero);
    pMenu->setTag(100);
    this->addChild(pMenu);
    
    return true;
}

void TitleScene::menuItemCallback(CCObject *pSender)
{
    CCLog("%s", "menuItemCallback");
    CCMenuItemLabel* menuItemLabel = (CCMenuItemLabel*)pSender;
    int tag = menuItemLabel->getTag();
    if (tag == 1)
    {
        // Scene切替
        CCLog("%s", "NovelScene start");
        CCScene* scene = NovelScene::scene();
        CCTransitionProgressInOut* tran = CCTransitionProgressInOut::create(1, scene);
        CCDirector::sharedDirector()->replaceScene(tran);
    }
}
//
//CCFiniteTimeAction* TitleScene::buttonAnimation()
//{
//    CCScaleTo* scale1 = CCScaleTo::create(0.1, 0.8);
//    CCScaleTo* scale2 = CCScaleTo::create(0.1, 1.0);
//    CCSequence* seq = CCSequence::create(scale1, scale2, NULL);
//    
//    return seq;
//}

