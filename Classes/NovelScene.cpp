//
//  NovelScene.cpp
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#include "NovelScene.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include "LabelSprite.h"
#include "MenuItemSelectLabelSprite.h"

#include "table/TableViewTestScene.h"

#include "cocos-ext.h"

#include "picojson.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace cocos2d;
USING_NS_CC_EXT;
using namespace std;

picojson::array createPicojson(unsigned char* novelJsonFile);

NovelScene::NovelScene()
:m_textIndex(0),
isMenuSelect(false),
isShowTextLog(false),
m_novelJsonFile(NULL)
{
    // jsonファイル読み込み
    unsigned long size = 0;
    m_novelJsonFile = CCFileUtils::sharedFileUtils()->getFileData("test.json", "r", &size);
    CCLog("Data is : %s",m_novelJsonFile);
    CCLog("Size: %lu\n\n", size);
    fflush(stdout);
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
    this->addChild(background, kZOrder_Background, kTag_Background);
    
    // TODO: BGM再生
    
    // -----------------------------
    // TODO: テキスト表示 Class化したい・・・
    // -----------------------------
    
    // 本文
    CCLayerColor * textLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7), winSize.width, winSize.height * 0.25);
    textLayer->setPosition(CCPointZero);
    this->addChild(textLayer, kZOrder_TextLayer, kTag_TextLayer);
    
    CCString* string = CCString::createWithFormat("w = %f.1 h = %f.1 f = %f", winSize.width, winSize.height, BASE_FONT_SIZE);
    CCLog("%s", string->getCString());
    // 本文テキスト
    CCLabelTTF* textLabel = CCLabelTTF::create(string->getCString(), "", BASE_FONT_SIZE);
    textLabel->setAnchorPoint(ccp(0, 0));
    textLabel->setColor(ccWHITE);
    textLabel->setPosition(ccp(BASE_FONT_SIZE, textLayer->getContentSize().height - textLabel->getContentSize().height - BASE_FONT_SIZE));
    textLayer->addChild(textLabel, kZOrder_TextLayer, kTag_TextLayer_textLabel);
    
    // 名前
    CCLayerColor * nameTextLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.7), winSize.width * 0.4, winSize.height * 0.1);
    nameTextLayer->setPosition(ccp(textLayer->getPositionX(), textLayer->getPositionY() + textLayer->getContentSize().height + nameTextLayer->getContentSize().height * 0.05));
    this->addChild(nameTextLayer, kZOrder_TextLayer, kTag_TextLayer_name);
    // 名前テキスト
    CCLabelTTF* nameTextLabel = CCLabelTTF::create("システムメッセージ", "", BASE_FONT_SIZE);
    nameTextLabel->setAnchorPoint(ccp(0, 0));
    nameTextLabel->setColor(ccGREEN);
    nameTextLabel->setPosition(ccp(BASE_FONT_SIZE, nameTextLayer->getContentSize().height - nameTextLabel->getContentSize().height - BASE_FONT_SIZE * 0.5));    
    nameTextLayer->addChild(nameTextLabel, kZOrder_TextLayer, kTag_TextLayer_nameTextLabel);
    
    // -----------------------------
    // TODO: キャラ顔画像表示
    
    // -----------------------------
    // ログ表示用ボタン配置
    
    CCLabelTTF* logButtonLabel = CCLabelTTF::create("Log", "Arial", BASE_FONT_SIZE);
    CCMenuItemLabel* logButtonMenuItem = CCMenuItemLabel::create(logButtonLabel, this, menu_selector(NovelScene::logMenuSelectCallback));
    logButtonMenuItem->setPosition(ccp(winSize.width * 0.95, logButtonMenuItem->getContentSize().height));
    
    CCMenu* pMenu = CCMenu::create(logButtonMenuItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, kZOrder_MenuItem, kTag_MenuItem_log);
    
    return true;
}

/**
 タッチイベント
 */
bool NovelScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("%s", "------ ccTouchBegan ------");
    // 選択肢とバックログ表示中は何もしない
    if (isMenuSelect || isShowTextLog)
    {
        return false;
    }
    
    return true;
}
void NovelScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // テキストエリアのタッチを判定
    CCLayer* pLayer = (CCLayer*) this->getChildByTag(kTag_TextLayer);
    if (pLayer->boundingBox().containsPoint(pTouch->getLocation()))
    {
        // テキストをすすめる
        nextNovelJson();
    }
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

void NovelScene::dispName(string name)
{
    CCLayer* pLayer = (CCLayer*) this->getChildByTag(kTag_TextLayer_name);
    if (pLayer)
    {
        // テキストをすすめる
        CCLabelTTF* nameTextLabel = (CCLabelTTF*) pLayer->getChildByTag(kTag_TextLayer_nameTextLabel);
        nameTextLabel->setString(name.c_str());
    }
}

void NovelScene::nextNovelJson()
{
    picojson::array novelArray = createPicojson(m_novelJsonFile);
    CCLOG("index = %d", m_textIndex);
    while (m_textIndex < novelArray.size())
    {
        picojson::object& novel = novelArray[m_textIndex].get<picojson::object>();
        int textType = novel["type"].get<double>();
        if (textType == kSelectItem)
        {
            // 選択肢表示
            isMenuSelect = true;
            makeSelectSpriteButton(novel["select1"].get<string>(), novel["next1Id"].get<double>(),
                                   novel["select2"].get<string>(), novel["next2Id"].get<double>());
        }
        else if (textType == kActorImageShow)
        {
            // アクター生成と表示
            int dict = novel["dict"].get<double>();
            string imgFilePath = novel["imgPath"].get<string>();
            makeActorImage(imgFilePath.c_str(), dict);
        }
        else if (textType == kActorImageHide)
        {
            // 表示中のアクターを消去
            int dict = novel["dict"].get<double>();
            removeActorImage(dict);
        }
        else if (textType == kBackgroundShow)
        {
            // 背景切替
            string imgFilePath = novel["imgPath"].get<string>();
            
            CCSprite* background = (CCSprite*)this->getChildByTag(kTag_Background);
            background->runAction(NovelScene::changeBackgroundAnimation(imgFilePath));
        }

        m_textIndex++;

        if (novel["name"])
        {
            dispName(novel["name"].get<string>());
        }
        
        if (novel["text"])
        {
            // テキスト取得できたらループを抜ける
            dispText(novel["text"].get<string>());
            break;
        }
    }
}

CCFiniteTimeAction* NovelScene::changeBackgroundAnimation(string imgFilePath)
{
    CCString* imgFilePathString = new CCString(imgFilePath);
    CCLog("imgFilePath = %s", imgFilePathString->getCString());
    
    CCFadeOut* fadeOut = CCFadeOut::create(0.5);
    CCCallFuncND* func = CCCallFuncND::create(this, callfuncND_selector(NovelScene::changeBackground), imgFilePathString);
    CCFadeIn* fadeIn = CCFadeIn::create(0.5);
    return CCSequence::create(fadeOut, func, fadeIn, NULL);
}

void NovelScene::changeBackground(CCObject *pSender, void* node)
{
    CCString* imgFilePath = (CCString*) node;
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(imgFilePath->getCString());
    ((CCSprite*)pSender)->setTexture(texture);
    imgFilePath->release();
}


void NovelScene::makeSelectSpriteButton(string str1, int next1Id, string str2, int next2Id)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu* pMenu = (CCMenu*) this->getChildByTag(kTag_MenuSelect);
    if (pMenu)
    {
        pMenu->setVisible(true);
        MenuItemSelectLabelSprite* menuSprite1 = (MenuItemSelectLabelSprite*) pMenu->getChildByTag(kTag_MenuSelect1);
        menuSprite1->setNovelText(str1.c_str(), next1Id);
        
        MenuItemSelectLabelSprite* menuSprite2 = (MenuItemSelectLabelSprite*) pMenu->getChildByTag(kTag_MenuSelect2);
        menuSprite2->setNovelText(str2.c_str(), next2Id);
    }
    else
    {
        // 選択肢1
        MenuItemSelectLabelSprite* menuSprite1 = MenuItemSelectLabelSprite::createWithLabelSprite("menu_button.png", str1.c_str(), "Arial", BASE_FONT_SIZE, ccBLACK, ccBLUE, ccRED, next1Id, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.55));
        menuSprite1->setTag(kTag_MenuSelect1);
        menuSprite1->setZOrder(kZOrder_MenuSelect);
        // 選択肢2
        MenuItemSelectLabelSprite* menuSprite2 = MenuItemSelectLabelSprite::createWithLabelSprite("menu_button.png", str2.c_str(), "Arial", BASE_FONT_SIZE, ccBLACK, ccBLUE, ccRED, next2Id, this, menu_selector(NovelScene::menuSelectCallback));
        menuSprite2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.45));
        menuSprite2->setTag(kTag_MenuSelect2);
        menuSprite2->setZOrder(kZOrder_MenuSelect);
        
        //メニュー作成
        pMenu = CCMenu::create(menuSprite1, menuSprite2, NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu, kZOrder_MenuSelect, kTag_MenuSelect);
    }
}


void NovelScene::menuSelectCallback(cocos2d::CCObject *pSender)
{
    if (isShowTextLog)
    {
        return;
    }
    
    this->getChildByTag(kTag_MenuSelect)->setVisible(false);
    isMenuSelect = false;

    MenuItemSelectLabelSprite* menuItem = (MenuItemSelectLabelSprite*) pSender;
    dispText(menuItem->m_labelText);
    if (menuItem->m_nextId > 0)
    {
        m_textIndex = menuItem->m_nextId - 1;
            CCLOG("index set = %d", m_textIndex);
    }
}


void NovelScene::makeActorImage(const char* imageFilePath, int dict)
{
    int dictTag = dict + kTag_ActorDict;
    
    // CCSprite生成
    CCSprite* actor = CCSprite::create(imageFilePath);
    actor->setScale(0.75);
    
    // 生成前に念のためremoveしておく
    removeActorImage(dict);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint point = CCPointZero;
    if (dictTag == kTag_ActorDictLeft)
    {
        point = ccp(actor->boundingBox().size.width * 0.5, actor->boundingBox().size.height * 0.5);
        actor->setFlipX(true); // 右向きにする
    }
    else if (dictTag == kTag_ActorDictCenter)
    {
        // TODO: センターあとで
    }
    else if (dictTag == kTag_ActorDictRight)
    {
        point = ccp(winSize.width - actor->boundingBox().size.width * 0.5, actor->boundingBox().size.height * 0.5);
    }
    actor->setPosition(point);    
    this->addChild(actor, kZOrder_Actor, dictTag);
}

void NovelScene::removeActorImage(int dict)
{
    int dictTag = dict + kTag_ActorDict;
    CCSprite* actor = (CCSprite*) this->getChildByTag(dictTag);
    if (actor)
    {
        actor->removeFromParent();
    }
}

void NovelScene::logMenuSelectCallback(cocos2d::CCObject *pSender)
{
    if (isShowTextLog)
    {
        hideTextLog();
    }
    else
    {
        showTextLog(m_textIndex);
    }
}

void NovelScene::showTextLog(int showTextIndex)
{
    if (showTextIndex <= 0)
    {
        return;
    }
    isShowTextLog = true;
    
    std::vector<std::string> textArray;
    picojson::array novelArray = createPicojson(m_novelJsonFile);
    for (int i = 0; i < showTextIndex; i++)
    {
        picojson::object& novel = novelArray[i].get<picojson::object>();
        if (novel["text"])
        {
            textArray.push_back(novel["text"].get<std::string>());
        }
    }
    
    TableViewTestLayer* logLayer = (TableViewTestLayer*) this->getChildByTag(kTag_TextLogLayer);
    if (logLayer)
    {        
        logLayer->makeTextLog(textArray);
        logLayer->setVisible(true);
    }
    else
    {
        logLayer = TableViewTestLayer::createWithTextArray(textArray);
        logLayer->setPosition(CCPointZero);
        this->addChild(logLayer, kZOrder_TextLogLayer, kTag_TextLogLayer);
    }
}

void NovelScene::hideTextLog()
{
    TableViewTestLayer* logLayer = (TableViewTestLayer*) this->getChildByTag(kTag_TextLogLayer);
    if (logLayer)
    {
        logLayer->setVisible(false);
    }
    
    isShowTextLog = false;
}


picojson::array createPicojson(unsigned char* novelJsonFile)
{
    fflush(stdout);
    
    std::stringstream ss;
    ss << novelJsonFile;
    
    picojson::value novelJson;
    ss >> novelJson;
    
    picojson::object& o = novelJson.get<picojson::object>();
    picojson::array novelArray = o["novel"].get<picojson::array>();
    
    return novelArray;
}


