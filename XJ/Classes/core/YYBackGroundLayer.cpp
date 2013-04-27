//
//  YYBackGroundLayer.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-22.
//
//

#include "YYBackgroundLayer.h"

USING_NS_CC;

void YYBackgroundLayer::onEnter(){
    CCSize  size = CCDirector::sharedDirector()->getWinSize();
    setBackgroundTexturePath("scene/background00.png");
    CCSprite * sprite = CCSprite::create(backgroundTexturePath);
    sprite->setPosition(ccp(size.width/2,size.height - sprite->getContentSize().height/2));
    addChild(sprite);
    sprite = CCSprite::create(backgroundTexturePath);
    sprite->setPosition(ccp(size.width / 2 + sprite->getContentSize().width,size.height - sprite->getContentSize().height/2));
    addChild(sprite);
}

void YYBackgroundLayer::setBackgroundTexturePath(const char * texturePath){
    backgroundTexturePath = texturePath;
}
