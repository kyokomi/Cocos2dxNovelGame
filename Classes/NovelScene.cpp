//
//  NovelScene.cpp
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#include "NovelScene.h"
#include "cocos2d.h"
#include "TextAreaLayer.h"

using namespace cocos2d;
using namespace std;

NovelScene::NovelScene()
:m_textIndex(0)
{
    m_textArray.push_back("このテキストはテスト用です。");
    m_textArray.push_back("ノベルゲームのようなテキスト送りがやりたい");
    m_textArray.push_back("ログ表示機能も必要");
    m_textArray.push_back("選択肢も必要");
    m_textArray.push_back("画面揺れとかホワイトアウトもできれば");
    m_textArray.push_back("立ちキャラの明暗で会話してるほうをわかりやすく");
    m_textArray.push_back("とりあえずこんなもん");
}

CCScene* NovelScene::scene()
{
    CCScene* scene = CCScene::create();
    NovelScene* layer = NovelScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool NovelScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    // シングルタップイベントを受け付ける
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // 背景表示
    CCSprite* background = CCSprite::create("013-PostTown01.jpg");
    background->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(background);
    
    // BGM再生
    
    // 立ち絵表示
    
    // -----------------------------
    // テキスト表示 Class化したい・・・
    // -----------------------------
    CCLayerColor * textLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7), winSize.width, winSize.height * 0.25);
    textLayer->setPosition(CCPointZero);
    textLayer->setTag(kTag_TextLayer);
    this->addChild(textLayer);
    
    // テキスト
    CCLabelTTF* textLabel = CCLabelTTF::create("ほげほげ", "", 18.0);
    textLabel->setAnchorPoint(ccp(0, textLabel->getAnchorPoint().y));
    textLabel->setColor(ccWHITE);
    textLabel->setPosition(ccp(textLayer->getContentSize().width * 0.05,
                               textLayer->getContentSize().height * 0.7));
    textLabel->setTag(kTag_TextLayer_textLabel);
    textLayer->addChild(textLabel);

    // -----------------------------
    // キャラ顔画像表示
    
    // メニューボタン表示
    
//    CCLabelTTF* label = CCLabelTTF::create("ノベルゲーム", "Arial", 24);
//    CCMenuItemLabel* menuItem = CCMenuItemLabel::create(label, this, menu_selector(TitleScene::menuItemCallback));
//    menuItem->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
//    menuItem->setTag(1);
    
//    CCMenu* pMenu = CCMenu::create(menuItem, NULL);
//    pMenu->setPosition(CCPointZero);
//    pMenu->setTag(100);
//    this->addChild(pMenu);
    
    return true;
}

bool NovelScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("%s", "ccTouchBegan");
    
    CCLayer* pLayer = (CCLayer*) this->getChildByTag(kTag_TextLayer);
    
    if (pLayer->boundingBox().containsPoint(pTouch->getLocation()))
    {
        // テキストをすすめる
        CCLabelTTF* textLabel = (CCLabelTTF*) pLayer->getChildByTag(kTag_TextLayer_textLabel);
        string text = nextText();
        textLabel->setString(text.c_str());
    }
    return true;
}

string NovelScene::nextText()
{
    string text = "おわり";
    
    if (m_textIndex < m_textArray.size())
    {
        text = m_textArray[m_textIndex];
        m_textIndex++;
    }
    return text;
}