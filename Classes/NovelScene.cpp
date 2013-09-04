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
:m_textIndex(0),
isMenuSelect(false)
{
    m_textArray.push_back("このテキストはテスト用です。");
    m_textTypeArray.push_back(1);
    m_textArray.push_back("ノベルゲームのようなテキスト送りがやりたい");
    m_textTypeArray.push_back(1);
    m_textArray.push_back("ログ表示機能も必要");
    m_textTypeArray.push_back(1);
    m_textArray.push_back("選択肢も必要");
    m_textTypeArray.push_back(2);
    m_textArray.push_back("画面揺れとかホワイトアウトもできれば");
    m_textTypeArray.push_back(1);
    m_textArray.push_back("立ちキャラの明暗で会話してるほうをわかりやすく");
    m_textTypeArray.push_back(2);
    m_textArray.push_back("とりあえずこんなもん");
    m_textTypeArray.push_back(1);
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
    
    if (isMenuSelect)
    {
        return false;
    }
    
    // テキストエリアのタッチを判定
    CCLayer* pLayer = (CCLayer*) this->getChildByTag(kTag_TextLayer);
    if (pLayer->boundingBox().containsPoint(pTouch->getLocation()))
    {
        // テキストをすすめる
        dispText(nextText());
    }
    return true;
}

void NovelScene::dispText(string text)
{
    CCLayer* pLayer = (CCLayer*) this->getChildByTag(kTag_TextLayer);
    if (pLayer)
    {
        // テキストをすすめる
        CCLabelTTF* textLabel = (CCLabelTTF*) pLayer->getChildByTag(kTag_TextLayer_textLabel);
        textLabel->setString(text.c_str());
    }
}

string NovelScene::nextText()
{
    string text = "おわり";
    
    if (m_textIndex < m_textArray.size())
    {
        text = m_textArray[m_textIndex];
        
        if (m_textIndex < m_textTypeArray.size())
        {
            int textType = m_textTypeArray[m_textIndex];
            if (textType == 2) {
                isMenuSelect = true;
                makeSelectSpriteButton("YES", "NO");
            }
        }

        m_textIndex++;
    }
    return text;
}

void NovelScene::makeSelectButton(string str1, string str2)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu* pMenu = (CCMenu*) this->getChildByTag(1000000);
    if (pMenu)
    {
        // TODO: テキスト設定
        pMenu->setVisible(true);
    }
    else
    {
        CCLabelTTF* label1 = CCLabelTTF::create(str1.c_str(), "Arial", 24);
//        CCLayerColor* layer1 = CCLayerColor::create(ccc4(0, 0, 0, 128), winSize.width * 0.5, label1->getContentSize().height);
//        label1->setPosition(ccp(layer1->getContentSize().width * 0.5, layer1->getContentSize().height * 0.5));
//        layer1->addChild(label1);

        CCMenuItemLabel* menuItem1 = CCMenuItemLabel::create(label1, this, menu_selector(NovelScene::menuSelectCallback));
        menuItem1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.55));
        menuItem1->setUserData(ccs(str1));

        
        CCLabelTTF* label2 = CCLabelTTF::create(str2.c_str(), "Arial", 24);
//        CCLayerColor* layer2 = CCLayerColor::create(ccc4(0, 0, 0, 128), winSize.width * 0.5, label2->getContentSize().height);
//        label2->setPosition(ccp(layer2->getContentSize().width * 0.5, layer2->getContentSize().height * 0.5));
//        layer2->addChild(label2);

        CCMenuItemLabel* menuItem2 = CCMenuItemLabel::create(label2, this, menu_selector(NovelScene::menuSelectCallback));
        menuItem2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.45));
        menuItem2->setUserData(ccs(str2));
        
        pMenu = CCMenu::create(menuItem1, menuItem2, NULL);
        pMenu->setPosition(CCPointZero);
        pMenu->setTag(1000000);
                
        this->addChild(pMenu);
    }
}

void NovelScene::makeSelectSpriteButton(string str1, string str2)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu* pMenu = (CCMenu*) this->getChildByTag(1000000);
    if (pMenu)
    {
        // TODO: テキスト設定
        pMenu->setVisible(true);
    }
    else
    {
        CCLabelTTF* label1 = CCLabelTTF::create(str1.c_str(), "Arial", 24);
        CCSprite* sprite1 = CCSprite::create("menu_button.png");
        sprite1->setColor(ccBLACK);
        sprite1->setOpacity(128);
        label1->setPosition(ccp(sprite1->getContentSize().width * 0.5, sprite1->getContentSize().height * 0.5));
        sprite1->addChild(label1);
        
        CCLabelTTF* label1_select = CCLabelTTF::create(str1.c_str(), "Arial", 24);
        CCSprite* sprite1_select = CCSprite::create("menu_button.png");
        sprite1_select->setColor(ccBLUE);
        sprite1_select->setOpacity(128);
        label1_select->setPosition(ccp(sprite1_select->getContentSize().width * 0.5, sprite1_select->getContentSize().height * 0.5));
        sprite1_select->addChild(label1_select);
        
        CCMenuItemSprite* menuSprite1 = CCMenuItemSprite::create(sprite1, sprite1_select, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.55));
        menuSprite1->setUserObject(ccs(str1));
        
        // -----------------
        
        CCLabelTTF* label2 = CCLabelTTF::create(str2.c_str(), "Arial", 24);
        CCSprite* sprite2 = CCSprite::create("menu_button.png");
        sprite2->setColor(ccBLACK);
        sprite2->setOpacity(128);
        label2->setPosition(ccp(sprite2->getContentSize().width * 0.5, sprite2->getContentSize().height * 0.5));
        sprite2->addChild(label2);

        
        CCLabelTTF* label2_select = CCLabelTTF::create(str2.c_str(), "Arial", 24);
        CCSprite* sprite2_select = CCSprite::create("menu_button.png");
        sprite2_select->setColor(ccBLUE);
        sprite2_select->setOpacity(128);
        label2_select->setPosition(ccp(sprite2_select->getContentSize().width * 0.5, sprite2_select->getContentSize().height * 0.5));
        sprite2_select->addChild(label2_select);
        
        CCMenuItemSprite* menuSprite2 = CCMenuItemSprite::create(sprite2, sprite2_select, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.45));
        menuSprite2->setUserObject(ccs(str2));
        
        pMenu = CCMenu::create(menuSprite1, menuSprite2, NULL);
        pMenu->setPosition(CCPointZero);
        pMenu->setTag(1000000);
        
        this->addChild(pMenu);
    }
}


void NovelScene::menuSelectCallback(cocos2d::CCObject *pSender)
{
    this->getChildByTag(1000000)->setVisible(false);
    isMenuSelect = false;

    CCMenuItemSprite* menuItem = (CCMenuItemSprite*) pSender;
    if ((CCString*) menuItem->getUserObject())
    {
        CCString* str = (CCString*) menuItem->getUserObject();
        dispText(str->getCString());
    }
    else
    {
        dispText("<<error>>");
    }
}