//
//  MenuItemSelectLabelSprite.h
//  NovelGame
//
//  Created by kyokomi on 2013/09/07.
//
//

#ifndef __NovelGame__MenuItemSelectLabelSprite__
#define __NovelGame__MenuItemSelectLabelSprite__

#include "cocos2d.h"
#include "LabelSprite.h"

USING_NS_CC;

class MenuItemSelectLabelSprite : public CCMenuItemSprite
{
public:
    virtual bool initWithLabelSprite(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B normalColor, ccColor3B selectedColor, ccColor3B disabledColor, int nextId, CCObject* target, SEL_MenuHandler selector);
    static MenuItemSelectLabelSprite* createWithLabelSprite(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B normalColor, ccColor3B selectedColor, ccColor3B disabledColor, int nextId, CCObject* target, SEL_MenuHandler selector);
    
    void setNovelText(const char *string, int nextId);
    
    std::string m_labelText;
    int m_nextId;
};

#endif /* defined(__NovelGame__MenuItemSelectLabelSprite__) */
