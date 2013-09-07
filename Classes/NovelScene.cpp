//
//  NovelScene.cpp
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#include "NovelScene.h"
#include "cocos2d.h"
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

    m_novelJsonFile = CCFileUtils::sharedFileUtils()->getFileData("test.json", "r", &size);
    CCLog("Data is : %s",m_novelJsonFile);
    CCLog("Size: %lu\n\n",size);
    fflush(stdout);

    std::stringstream ss;
    ss << m_novelJsonFile;
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
    CCLabelTTF* textLabel = CCLabelTTF::create("", "", 18.0);
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
    CCLog("%s", "------ ccTouchBegan ------");
    
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
        
    std::stringstream ss;
    ss << m_novelJsonFile;
    
    picojson::value novelJson;
    ss >> novelJson;
    
    picojson::object& o = novelJson.get<picojson::object>();
    picojson::array novelArray = o["novel"].get<picojson::array>();
    
    if (m_textIndex < novelArray.size())
    {
        picojson::object& novel = novelArray[m_textIndex].get<picojson::object>();
        text = novel["text"].get<string>();
        int textType = novel["type"].get<double>();
        // TODO: あとでenumにする
        if (textType == 2) {
            isMenuSelect = true;
            makeSelectSpriteButton(novel["select1"].get<string>(), novel["select2"].get<string>());
        }
        
        m_textIndex++;
    }
    return text;
}


void NovelScene::makeSelectSpriteButton(string str1, string str2)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu* pMenu = (CCMenu*) this->getChildByTag(kTag_MenuSelect);
    if (pMenu)
    {
        pMenu->setVisible(true);
        MenuItemSelectLabelSprite* menuSprite1 = (MenuItemSelectLabelSprite*) pMenu->getChildByTag(kTag_MenuSelect1);
        menuSprite1->setText(str1.c_str());
        
        MenuItemSelectLabelSprite* menuSprite2 = (MenuItemSelectLabelSprite*) pMenu->getChildByTag(kTag_MenuSelect2);
        menuSprite2->setText(str2.c_str());
    }
    else
    {
        // 選択肢1
        MenuItemSelectLabelSprite* menuSprite1 = MenuItemSelectLabelSprite::createWithLabelSprite("menu_button.png", str1.c_str(), "Arial", 24, ccBLACK, ccBLUE, ccRED, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.55));
        menuSprite1->setTag(kTag_MenuSelect1);
        // 選択肢2
        MenuItemSelectLabelSprite* menuSprite2 = MenuItemSelectLabelSprite::createWithLabelSprite("menu_button.png", str2.c_str(), "Arial", 24, ccBLACK, ccBLUE, ccRED, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.45));
        menuSprite2->setTag(kTag_MenuSelect2);
        
        pMenu = CCMenu::create(menuSprite1, menuSprite2, NULL);
        pMenu->setPosition(CCPointZero);
        pMenu->setTag(kTag_MenuSelect);
        
        this->addChild(pMenu);
    }
}


void NovelScene::menuSelectCallback(cocos2d::CCObject *pSender)
{
    this->getChildByTag(kTag_MenuSelect)->setVisible(false);
    isMenuSelect = false;

    MenuItemSelectLabelSprite* menuItem = (MenuItemSelectLabelSprite*) pSender;
    dispText(menuItem->labelText);
}