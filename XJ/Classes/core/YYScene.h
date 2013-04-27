//
//  YYScene.h
//  XJ
//
//  Created by 于志鹏 on 13-4-19.
//
//

#ifndef __XJ__YYScene__
#define __XJ__YYScene__

#include <cocos2d.h>

class YYRoadLayer;
class YYBackgroundLayer;
class YYForegroundLayer;
class YYControlUILayer;
class YYFightSpriteLayer;
class YYCloseShotLayer;

class YYScene : public cocos2d::CCScene,public cocos2d::CCStandardTouchDelegate{
    
    CC_SYNTHESIZE(cocos2d::CCSize, sceneSize, SceneSize);//场景大小
    CC_SYNTHESIZE(cocos2d::CCPoint, screenDatumPoint, ScreenDatumPoint);//屏幕基准点（左下点）相对游戏场景的坐标
private:
    bool isTouchBegan,isTouchesMoved,isTouchesEnded;//是否有触屏操作(滑动、点击)
    cocos2d::CCPoint preTouchPoint,currentTouchPoint;//上一触摸点和当前触摸点
protected:
    YYBackgroundLayer * backgroundLayer;
    YYForegroundLayer * foregroundLayer;
    YYRoadLayer * roadLayer;
    YYFightSpriteLayer * fightSpriteLayer;
    YYCloseShotLayer * closeShotLayer;
    YYControlUILayer * controlUILayer;
public:
    YYScene();
    ~YYScene();
    static YYScene * sharedScene();
    void onEnter();
    //背景层
//    void setBackgroundLayer(YYBackgroundLayer * layer);
    YYBackgroundLayer * getBackgroundLayer();
    //前景层
//    void setForegroundLayer(YYForegroundLayer * layer);
    YYForegroundLayer * getForegroundLayer();
    //道路层
//    void setRoadLayer(YYRoadLayer * layer);
    YYRoadLayer * getRoadLayer();
    //触控UI层
//    void setControlUILayer(YYControlUILayer * layer);
    YYControlUILayer * getControlUILayer();
    
    YYFightSpriteLayer * getfightSpriteLayer();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void update(float delayTime);
    void touchHandle(void);
    void updateScreenDatumPoint();
};
#endif /* defined(__XJ__YYScene__) */
