//
//  YYAnimationData.h
//  Datang
//
//  Created by 于志鹏 on 13-2-4.
//
//

#ifndef __Datang__YYAnimationData__
#define __Datang__YYAnimationData__

#include "cocos2d.h"

USING_NS_CC;

class YYAnimationData:public CCObject{

public:
    YYAnimationData();
    ~YYAnimationData();
    //起始帧序号
    unsigned short startFrameIndex;
    //终止帧序号
    unsigned short endFrameIndex;
    static YYAnimationData * createActionDataFrom(unsigned short startFrameIndex,unsigned short endFrameIndex);
};

#endif /* defined(__Datang__YYAnimationData__) */