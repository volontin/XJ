//
//  YYForegroundLayer.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-22.
//
//

#include "YYForegroundLayer.h"

USING_NS_CC;

void YYForegroundLayer::onEnter(){
    CCSize  size = CCDirector::sharedDirector()->getWinSize();
    setForegroundTexturePath("scene/front00.png");
    cocos2d::CCSprite * sprite = CCSprite::create(foregroundTexturePath);
    sprite->setPosition(ccp(size.width/2,size.height - 188));
    addChild(sprite);
    sprite = CCSprite::create(foregroundTexturePath);
    sprite->setPosition(ccp(size.width/2 + sprite->getContentSize().width,size.height - 188));
    addChild(sprite);
}
void YYForegroundLayer::setForegroundTexturePath(const char * texturePath){
    foregroundTexturePath = texturePath;
}