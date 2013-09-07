//
//  MenuItemSelectLabelSprite.cpp
//  NovelGame
//
//  Created by kyokomi on 2013/09/07.
//
//

#include "MenuItemSelectLabelSprite.h"

MenuItemSelectLabelSprite* MenuItemSelectLabelSprite::createWithLabelSprite(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B normalColor, ccColor3B selectedColor, ccColor3B disabledColor, int nextId, cocos2d::CCObject *target, SEL_MenuHandler selector)
{
    MenuItemSelectLabelSprite *pRet = new MenuItemSelectLabelSprite();
    if (pRet && pRet->initWithLabelSprite(pszFileName, string, fontName, fontSize, normalColor, selectedColor, disabledColor, nextId, target, selector))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool MenuItemSelectLabelSprite::initWithLabelSprite(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B normalColor, ccColor3B selectedColor, ccColor3B disabledColor, int nextId, cocos2d::CCObject *target, SEL_MenuHandler selector)
{
    LabelSprite* normalLabelSprite = LabelSprite::createWithLabel(pszFileName, string, fontName, fontSize, normalColor);
    if (normalLabelSprite == NULL)
    {
        return false;
    }
    LabelSprite* selectedLabelSprite = LabelSprite::createWithLabel(pszFileName, string, fontName, fontSize, selectedColor);
    if (selectedLabelSprite == NULL)
    {
        return false;
    }
    LabelSprite* disabledLabelSprite = LabelSprite::createWithLabel(pszFileName, string, fontName, fontSize, disabledColor);
    if (disabledLabelSprite == NULL)
    {
        return false;
    }
    
    if (!CCMenuItemSprite::initWithNormalSprite(normalLabelSprite, selectedLabelSprite, disabledLabelSprite, target, selector))
    {
        return false;
    }
    m_labelText = string;
    m_nextId = nextId;
    
    return true;
}

void MenuItemSelectLabelSprite::setNovelText(const char *string, int nextId)
{
    m_labelText = string;
    m_nextId = nextId;
    ((LabelSprite*) this->getNormalImage())->setLabelText(string);
    ((LabelSprite*) this->getSelectedImage())->setLabelText(string);
    ((LabelSprite*) this->getDisabledImage())->setLabelText(string);
}



