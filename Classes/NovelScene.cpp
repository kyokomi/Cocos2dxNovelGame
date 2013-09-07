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
#include "LabelSprite.h"
#include "MenuItemSelectLabelSprite.h"

#include "picojson.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace cocos2d;
using namespace std;

NovelScene::NovelScene()
:m_textIndex(0),
isMenuSelect(false)
{
    // jsonファイル読み込み
    unsigned long size = 0;

    unsigned char* smth = CCFileUtils::sharedFileUtils()->getFileData("test.json", "r", &size);
    CCLog("Data is : %s",smth);
    CCLog("Size: %lu\n\n",size);
    fflush(stdout);

    std::stringstream ss;
    ss << smth;
    
    picojson::value json; ss >> json;
    picojson::object& o = json.get<picojson::object>();
    double hoge = o["hoge"].get<double>();
//    bool fuga = o["fuga"].get<bool>();
    string piyo = o["piyo"].get<string>();
//    picojson::array hogehoge = o["hogehoge"].get<picojson::array>();
    CCLog("hoge is : %.0f", hoge);
    CCLog("piyo is : %s", piyo.c_str());
    
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
    
    // TODO: 背景表示
    CCSprite* background = CCSprite::create("013-PostTown01.jpg");
    background->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(background);
    
    // TODO: BGM再生
    
    // TODO: 立ち絵表示
    
    // -----------------------------
    // TODO: テキスト表示 Class化したい・・・
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
    // TODO: キャラ顔画像表示
        
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
        // 選択肢1
        MenuItemSelectLabelSprite* menuSprite1 = MenuItemSelectLabelSprite::createWithLabelSprite("menu_button.png", str1.c_str(), "Arial", 24, ccBLACK, ccBLUE, ccRED, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.55));
        // 選択肢2
        MenuItemSelectLabelSprite* menuSprite2 = MenuItemSelectLabelSprite::createWithLabelSprite("menu_button.png", str2.c_str(), "Arial", 24, ccBLACK, ccBLUE, ccRED, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.45));
        
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

    MenuItemSelectLabelSprite* menuItem = (MenuItemSelectLabelSprite*) pSender;
    dispText(menuItem->labelText);
}