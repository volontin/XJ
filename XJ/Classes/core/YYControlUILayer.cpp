//
//  YYControlUILayer.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-23.
//
//

#include "YYControlUILayer.h"
#include "YYScene.h"

USING_NS_CC;

void YYControlUILayer::draw(){
    CCSize  size = CCDirector::sharedDirector()->getWinSize();
    ccDrawColor4B(255,0,0,255);
    ccDrawCircle(ccp(120,120), 100, 0, 360, false, 1, 1);
    ccDrawCircle(ccp(size.width - 120,120), 50, 315, 360, false, 1, 1);
    ccDrawLine(ccp(190.710678,190.710678), ccp(49.289322,49.289322));
    ccDrawLine(ccp(49.289322,190.710678), ccp(190.710678,49.289322));
}