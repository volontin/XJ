//
//  YYForegroundLayer.h
//  XJ
//  前景层
//  Created by 于志鹏 on 13-4-22.
//
//

#ifndef __XJ__YYForegroundLayer__
#define __XJ__YYForegroundLayer__

#include <cocos2d.h>

class YYForegroundLayer : public cocos2d::CCLayer{
    
protected:
    const char * foregroundTexturePath;//
public:
    void onEnter();
    CREATE_FUNC(YYForegroundLayer);
    
    void setForegroundTexturePath(const char * texturePath);
};

#endif /* defined(__XJ__YYForegroundLayer__) */
