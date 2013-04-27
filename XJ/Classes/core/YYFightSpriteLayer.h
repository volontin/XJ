//
//  YYFightSpriteLayer.h
//  XJ
//  战斗精灵层
//  Created by 于志鹏 on 13-4-27.
//
//

#ifndef __XJ__YYFightSpriteLayer__
#define __XJ__YYFightSpriteLayer__

#include "cocos2d.h"
class YYPlayer;

class YYFightSpriteLayer : public cocos2d::CCLayer{
private:
    YYPlayer * player;
public:
    YYFightSpriteLayer();
    ~YYFightSpriteLayer();
    
    CREATE_FUNC(YYFightSpriteLayer);
    void onEnter();
    void update(void);
    YYPlayer * getPlayer();
    void sortSprite();
};

#endif /* defined(__XJ__YYFightSpriteLayer__) */
