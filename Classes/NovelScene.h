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
    /** ノベル情報Json */
    unsigned char* m_novelJsonFile;
    /** ノベルテキスト送りインデックス */
    int m_textIndex;
    
    /** 次のテキストを処理 */
    string nextText();
    
    /** 選択肢ボタンの生成 */
    void makeSelectSpriteButton(string str1, string str2);
    /** 選択肢を選んだ時のコールバック */
    void menuSelectCallback(CCObject *pSender);
    
    /** テキストを表示させる */
    void dispText(string text);
protected:
    
    enum kTag
    {
        kTag_TextLayer = 1,
        
        /** 選択肢用 */
        kTag_MenuSelect = 100000,
        kTag_MenuSelect1,
        kTag_MenuSelect2,
    };
    
    enum kTagTextLayer
    {
        kTag_TextLayer_textLabel = 1,
    };
    
public:
    NovelScene();
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(NovelScene);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__NovelGame__NovelScene__) */
