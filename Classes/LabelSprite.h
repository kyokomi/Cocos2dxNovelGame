//
//  CCLabelSprite.h
//  NovelGame
//
//  Created by kyokomi on 2013/09/07.
//
//

#ifndef __NovelGame__LabelSprite__
#define __NovelGame__LabelSprite__

#include "cocos2d.h"

USING_NS_CC;

class LabelSprite : public CCSprite
{
    CCLabelTTF* m_pLabel;
public:
    LabelSprite();
    
    virtual bool initWithLabel(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B color);
    static LabelSprite* createWithLabel(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B color);
};

#endif /* defined(__NovelGame__CCLabelSprite__) */
