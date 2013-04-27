//
//  YYCloseShotLayer.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-27.
//
//


#include "YYCloseShotLayer.h"

USING_NS_CC;

YYCloseShotLayer::YYCloseShotLayer()
:closeShotSpriteTexturePath(NULL)
,closeShotSprite_0(NULL)
,closeShotSprite_1(NULL)
{
    
}

YYCloseShotLayer::~YYCloseShotLayer(){
    CC_SAFE_DELETE(closeShotSpriteTexturePath);
    CC_SAFE_DELETE(closeShotSprite_0);
    CC_SAFE_DELETE(closeShotSprite_1);
}

void YYCloseShotLayer::onEnter(){
    setCloseShotSpriteTexturePath("scene/near_sprite00.png");
    closeShotSprite_0 = CCSprite::create(closeShotSpriteTexturePath);
    closeShotSprite_1 = CCSprite::create(closeShotSpriteTexturePath);
    closeShotSprite_0->setAnchorPoint(ccp(0,0));
    closeShotSprite_1->setAnchorPoint(ccp(0,0));
    closeShotSprite_0->setPosition(ccp(0,0));
    closeShotSprite_1->setPosition(ccp(closeShotSprite_0->getContentSize().width,0));
    addChild(closeShotSprite_0);
    addChild(closeShotSprite_1);
}

void YYCloseShotLayer::setCloseShotSpriteTexturePath(const char * texturePath){
    closeShotSpriteTexturePath = texturePath;
}