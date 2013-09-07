//
//  LabelSprite.cpp
//  NovelGame
//
//  Created by kyokomi on 2013/09/07.
//
//

#include "LabelSprite.h"

LabelSprite::LabelSprite()
:m_pLabel(NULL)
{
}

LabelSprite* LabelSprite::createWithLabel(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B color)
{
    LabelSprite *pRet = new LabelSprite();
    if (pRet && pRet->initWithLabel(pszFileName, string, fontName, fontSize, color))
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

bool LabelSprite::initWithLabel(const char *pszFileName, const char *string, const char *fontName, float fontSize, ccColor3B color)
{
    if (!CCSprite::initWithFile(pszFileName))
    {
        return false;
    }
    m_pLabel = CCLabelTTF::create(string, fontName, fontSize);
    if (m_pLabel == NULL)
    {
        return false;
    }
    m_pLabel->setPosition(ccp(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5));
    this->addChild(m_pLabel);
    
    this->setColor(color);
    this->setOpacity(128);
    return true;
}

void LabelSprite::setLabelText(const char *string)
{
    this->m_pLabel->setString(string);
}


