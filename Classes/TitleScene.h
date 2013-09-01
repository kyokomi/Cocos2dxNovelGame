//
//  TitleScene.h
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#ifndef __NovelGame__TitleScene__
#define __NovelGame__TitleScene__

#include "cocos2d.h"

USING_NS_CC;

class TitleScene : public cocos2d::CCLayer
{
protected:
    void menuItemCallback(CCObject* pSender);
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__NovelGame__TitleScene__) */
