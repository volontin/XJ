//
//  YYScene.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-19.
//
//

#include "../common/Common.h"

#include "YYScene.h"
#include "YYRoadLayer.h"
#include "YYBackgroundLayer.h"
#include "YYForegroundLayer.h"
#include "YYControlUILayer.h"
#include "YYPlayer.h"
#include "YYFightSpriteLayer.h"
#include "YYCloseShotLayer.h"

USING_NS_CC;

#pragma mark 构造、析构、初始化

YYScene::YYScene()
:backgroundLayer(NULL)
,foregroundLayer(NULL)
,roadLayer(NULL)
,screenDatumPoint(CCPointZero)
,sceneSize(CCSizeZero)
{
}

YYScene::~YYScene(){
    CC_SAFE_DELETE(backgroundLayer);
    CC_SAFE_DELETE(foregroundLayer);
    CC_SAFE_DELETE(roadLayer);
}

static YYScene * scene = NULL;

YYScene * YYScene::sharedScene(){
    if (scene == NULL) {
        scene = new YYScene();
        return scene;
    }
    return scene;
}

void YYScene::onEnter(){
    this->schedule(schedule_selector(YYScene::update),0.1f);
    //添加触摸协议
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,1);
    setSceneSize(CCSizeMake(960*2, 640));
    backgroundLayer = YYBackgroundLayer::create();
    backgroundLayer->setAnchorPoint(ccp(0,0));
    backgroundLayer->setPosition(ccp(0,0));
    foregroundLayer = YYForegroundLayer::create();
    foregroundLayer->setAnchorPoint(ccp(0,0));
    foregroundLayer->setPosition(ccp(0,0));
    roadLayer = YYRoadLayer::create();
    roadLayer->setAnchorPoint(ccp(0,0));
    roadLayer->setPosition(ccp(0,0));
    
    fightSpriteLayer = YYFightSpriteLayer::create();
    fightSpriteLayer->setAnchorPoint(ccp(0,0));
    fightSpriteLayer->setPosition(ccp(0,0));
    
    closeShotLayer = YYCloseShotLayer::create();
    closeShotLayer->setAnchorPoint(ccp(0,0));
    closeShotLayer->setPosition(ccp(0,0));
    
    controlUILayer = YYControlUILayer::create();
    controlUILayer->setAnchorPoint(ccp(0,0));
    controlUILayer->setPosition(ccp(0,0));
    addChild(backgroundLayer,0);
    addChild(foregroundLayer,1);
    addChild(roadLayer,2);
    addChild(fightSpriteLayer,3);
    addChild(closeShotLayer,4);
    addChild(controlUILayer,5);
    CCScene::onEnter();
}

YYBackgroundLayer * YYScene::getBackgroundLayer(){
    return backgroundLayer;
}

YYForegroundLayer * YYScene::getForegroundLayer(){
    return foregroundLayer;
}

YYRoadLayer * YYScene::getRoadLayer(){
    return roadLayer;
}

YYControlUILayer * YYScene::getControlUILayer(){
    return controlUILayer;
}

#pragma mark 触屏控制

void YYScene::ccTouchesBegan(CCSet *touches,CCEvent * event)
{
    isTouchBegan = true;
    CCTouch *touch = (CCTouch *)touches->anyObject();
    currentTouchPoint = touch->getLocation();
}

void YYScene::ccTouchesMoved(CCSet * touches,CCEvent *event)
{
    isTouchesMoved = true;
    preTouchPoint = currentTouchPoint;
    CCTouch *touch = (CCTouch *)touches->anyObject();
    currentTouchPoint = touch->getLocation();
}

void YYScene::ccTouchesEnded(CCSet * touches,CCEvent *event)
{
    isTouchesEnded = true;
    CCTouch *touch = (CCTouch *)touches->anyObject();
    currentTouchPoint = touch->getLocation();
}

void YYScene::update(float delayTime){
    processRecievedMessages();
    touchHandle();
    fightSpriteLayer->update();
    updateScreenDatumPoint();
}

void YYScene::touchHandle(void){
    if(isTouchBegan){
        isTouchBegan = false;
        fightSpriteLayer->getPlayer()->touchBegan(preTouchPoint,currentTouchPoint);
    }
    if(isTouchesMoved){
        isTouchesMoved = false;
        fightSpriteLayer->getPlayer()->touchMoved(preTouchPoint,currentTouchPoint);
    }
    if(isTouchesEnded){
        isTouchesEnded = false;
        fightSpriteLayer->getPlayer()->touchEnded(preTouchPoint,currentTouchPoint);
    }
}

/**
 *更新屏幕镜头位置
 */
void YYScene::updateScreenDatumPoint(){
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint playerPostion = fightSpriteLayer->getPlayer()->getPosition();
    int screenX = 0,screenY = 0;
    screenX  = playerPostion.x - screenSize.width / 2;
    screenY  = playerPostion.y - screenSize.height / 2;
    if (screenX < 0) {
        screenX = 0;
    }else if (screenX > sceneSize.width - screenSize.width) {
        screenX = sceneSize.width - screenSize.width;
    }
    if (screenY < 0) {
        screenY = 0;
    }else if (screenY > sceneSize.height - screenSize.height) {
        screenY = sceneSize.height - screenSize.height;
    }
    setScreenDatumPoint(ccp(screenX,screenY));
    backgroundLayer->setPosition(ccp(-screenX,-screenY));
    foregroundLayer->setPosition(ccp(-screenX,-screenY));
    roadLayer->setPosition(ccp(-screenX,-screenY));
    fightSpriteLayer->setPosition(ccp(-screenX,-screenY));
    closeShotLayer->setPosition(ccp(-screenX,-screenY));
    //    controlUILayer->setPosition(getScreenDatumPoint());
}
void YYScene::processRecievedMessages(){
    
}

void YYScene::receivedMessage(const char * strings){
    CCArray *array = split_string(strings, '\n');
    messagePool->addObjectsFromArray(array);
}