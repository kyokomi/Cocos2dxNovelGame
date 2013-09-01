//
//  TextAreaLayer.h
//  NovelGame
//
//  Created by kyokomi on 2013/09/01.
//
//

#ifndef __NovelGame__TextAreaLayer__
#define __NovelGame__TextAreaLayer__

#include "cocos2d.h"

USING_NS_CC;

class TextAreaLayer : public CCLayerColor
{
public:
    CREATE_FUNC(TextAreaLayer);
    static TextAreaLayer * create(const ccColor4B& color, GLfloat width, GLfloat height);
    
    virtual bool init();
    virtual bool initWithColor(const ccColor4B& color, GLfloat w, GLfloat h);
};

#endif /* defined(__NovelGame__TextAreaLayer__) */
