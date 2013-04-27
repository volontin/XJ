//
//  YYRoadLayer.h
//  XJ
//  道路层
//  Created by 于志鹏 on 13-4-19.
//  
//

#ifndef __XJ__YYRoadLayer__
#define __XJ__YYRoadLayer__

#include <cocos2d.h>

class YYPlayer;

class YYRoadLayer : public cocos2d::CCLayer{

protected:
    const char * roadTexturePath;
    cocos2d::CCArray * elementsInfoArray;//场景元素信息数组
    cocos2d::CCSprite * background_0,* background_1;//道路背景
public:
    YYRoadLayer();
    ~YYRoadLayer();

    CREATE_FUNC(YYRoadLayer);
    void onEnter();
    void setRoadTexturePath(const char * texturePath);
    void setSceneElementInfoArray(cocos2d::CCArray * array);
    void addSceneElements();
};

#endif /* defined(__XJ__YYRoadLayer__) */
