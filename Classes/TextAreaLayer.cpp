//
//  TextAreaLayer.cpp
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#include "TextAreaLayer.h"

bool TextAreaLayer::init()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    return initWithColor(ccc4(0,0,0,0), s.width, s.height);
}

bool TextAreaLayer::initWithColor(const ccColor4B& color, GLfloat w, GLfloat h)
{
    if (CCLayerColor::init())
    {
        
    }
    
    return true;
}

TextAreaLayer * TextAreaLayer::create(const ccColor4B& color, GLfloat width, GLfloat height)
{
    TextAreaLayer * pLayer = new TextAreaLayer();
    if( pLayer && pLayer->initWithColor(color,width,height))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}