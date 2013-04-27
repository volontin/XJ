//
//  YYBackgroundLayer.h
//  XJ
//  背景层
//  Created by 于志鹏 on 13-4-22.
//
//

#ifndef __XJ__YYBackgroundLayer__
#define __XJ__YYBackgroundLayer__

#include <cocos2d.h>

class YYBackgroundLayer : public cocos2d::CCLayer{
    
protected:
    const char * backgroundTexturePath;//
public:
    void onEnter();
    CREATE_FUNC(YYBackgroundLayer);
    void setBackgroundTexturePath(const char * texturePath);
};

#endif /* defined(__XJ__YYBackgroundLayer__) */
