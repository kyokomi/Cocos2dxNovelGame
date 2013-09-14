//
//  NovelScene.h
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#ifndef __NovelGame__NovelScene__
#define __NovelGame__NovelScene__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class NovelScene : public cocos2d::CCLayer
{
    /** 選択肢表示中フラグ */
    bool isMenuSelect;
    /** バックログ表示中フラグ */
    bool isShowTextLog;
    
    /** ノベル情報Json */
    unsigned char* m_novelJsonFile;
    /** ノベルテキスト送りインデックス */
    int m_textIndex;
    
    /** 次のテキストを処理 */
    void nextNovelJson();
    
    /** 選択肢ボタンの生成 */
    void makeSelectSpriteButton(string str1, int next1Id, string str2, int next2Id);
    /** 選択肢を選んだ時のコールバック */
    void menuSelectCallback(CCObject *pSender);
    
    /** テキストを表示させる */
    void dispText(string text);
    /** 名前を表示させる */
    void dispName(string name);
    
    void makeActorImage(const char* imageFilePath, int dict);
    void removeActorImage(int dict);
    
    CCFiniteTimeAction* changeBackgroundAnimation(string imgFilePath);
    void changeBackground(CCObject *pSender, void* node);
    
    void logMenuSelectCallback(CCObject *pSender);
    void showTextLog(int showTextIndex);
    void hideTextLog();
protected:
    
    enum kTag
    {
        kTag_Background = 1,
        kTag_TextLayer = 100,
        kTag_TextLayer_textLabel = 101,
        kTag_TextLayer_name = 200,
        kTag_TextLayer_nameTextLabel = 201,
        
        kTag_ActorDict     = 1000,
        kTag_ActorDictLeft,
        kTag_ActorDictCenter,
        kTag_ActorDictRight,
        
        /** 選択肢用 */
        kTag_MenuSelect   = 10000,
        kTag_MenuSelect1,
        kTag_MenuSelect2,
        
        /** バックログ */
        kTag_TextLogLayer = 20000,
        
        /** メニュー */
        kTag_MenuItem_log = 30000,
    };
    
    enum kZOrder
    {
        kZOrder_Background = 1,
        kZOrder_Actor,
        kZOrder_TextLayer,
        kZOrder_MenuSelect,
        kZOrder_TextLogLayer,
        kZOrder_MenuItem,
    };
    
    enum kNovelType
    {
        kTextType = 1,
        kSelectItem = 2,
        kActorImageShow = 3,
        kActorImageHide = 4,
        kBackgroundShow = 5,
    };
    
public:
    NovelScene();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(NovelScene);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__NovelGame__NovelScene__) */
