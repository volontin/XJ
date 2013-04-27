//
//  YYCloseShotLayer.h
//  XJ
//  近景层
//  Created by 于志鹏 on 13-4-27.
//
//

#ifndef __XJ__YYCloseShotLayer__
#define __XJ__YYCloseShotLayer__

#include "cocos2d.h"

class YYCloseShotLayer : public cocos2d::CCLayer{
private:
    const char * closeShotSpriteTexturePath;
    cocos2d::CCSprite * closeShotSprite_0,* closeShotSprite_1;
public:
    YYCloseShotLayer();
    ~YYCloseShotLayer();
    
    CREATE_FUNC(YYCloseShotLayer);
    void onEnter();
    void setCloseShotSpriteTexturePath(const char * nearlySpritePath);
};
#endif /* defined(__XJ__YYCloseShotLayer__) */
