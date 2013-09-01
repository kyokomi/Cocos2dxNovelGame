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
    vector<string> m_textArray;
    int m_textIndex;
    string nextText();
    
protected:
    enum kTag
    {
        kTag_TextLayer = 1,
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
