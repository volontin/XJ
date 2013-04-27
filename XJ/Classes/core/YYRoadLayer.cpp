//
//  YYRoadLayer.cpp
//  test00
//
//  Created by 于志鹏 on 13-4-19.
//
//

#include "YYRoadLayer.h"
#include "Common.h"
#include "YYScene.h"

USING_NS_CC;

YYRoadLayer::YYRoadLayer()
:roadTexturePath(NULL)
,background_0(NULL)
,background_1(NULL)
{
}

YYRoadLayer::~YYRoadLayer(){
    CC_SAFE_DELETE(roadTexturePath);
    CC_SAFE_DELETE(background_0);
    CC_SAFE_DELETE(background_1);

}

void YYRoadLayer::onEnter(){
    setRoadTexturePath("scene/road00.png");
    background_0 = CCSprite::create(roadTexturePath);
    background_1 = CCSprite::create(roadTexturePath);
    background_0->setAnchorPoint(ccp(0,0));
    background_1->setAnchorPoint(ccp(0,0));
    background_0->setPosition(ccp(0,0));
    background_1->setPosition(ccp(background_0->getContentSize().width,0));
    this->addChild(background_0);
    this->addChild(background_1);
    addSceneElements();//添加场景内元素
    cocos2d::CCLayer::onEnter();
}

void YYRoadLayer::setRoadTexturePath(const char * texturePath){
    roadTexturePath = texturePath;
}

void YYRoadLayer::setSceneElementInfoArray(CCArray * array){
    if (elementsInfoArray != array) {
        CC_SAFE_RETAIN(array);
        CC_SAFE_RELEASE(elementsInfoArray);
        elementsInfoArray = array;
    }
}

void YYRoadLayer::addSceneElements(){
    //    for (int i = 0; i < elementsInfoArray->count(); i++) {
    //        CCString * elementsInfo = (CCString *)elementsInfoArray->objectAtIndex(i);
    //        CCArray * array = split_string(elementsInfo->getCString(),'_');
    //        CCString * fileName = (CCString *)array->objectAtIndex(0);
    //        char * buffer = new char[20];
    //        sprintf(buffer, "%s%s%s","prop/",fileName->getCString(),".png");
    //        CCSprite * sceneElement = CCSprite::create(buffer);
    //        int x = ((CCString *)array->objectAtIndex(1))->intValue();
    //        int y = ((CCString *)array->objectAtIndex(2))->intValue();
    //        sceneElement->setPosition(ccp(x,y));
    //        this->addChild(sceneElement,0);
    //        delete buffer;
    //    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite * sceneElement = CCSprite::create("scene/road_sprite00.png");
    sceneElement->setPosition(ccp(250,size.height/2));
    this->addChild(sceneElement,0);
    sceneElement = CCSprite::create("scene/road_sprite01.png");
    sceneElement->setPosition(ccp(size.width- 140,size.height/2 - 20));
    this->addChild(sceneElement);
    sceneElement = CCSprite::create("scene/road_sprite02.png");
    sceneElement->setPosition(ccp(size.width- 100,size.height/2 - 15));
    this->addChild(sceneElement);
    sceneElement = CCSprite::create("scene/road_sprite02.png");
    sceneElement->setPosition(ccp(size.width- 50,size.height/2 - 15));
    this->addChild(sceneElement);
    sceneElement = CCSprite::create("scene/road_sprite02.png");
    sceneElement->setPosition(ccp(40,size.height/2 - 60));
    this->addChild(sceneElement);
    sceneElement = CCSprite::create("scene/road_sprite02.png");
    sceneElement->setPosition(ccp(86,size.height/2 - 60));
    this->addChild(sceneElement);
}
