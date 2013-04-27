//
//  YYFrameData.h
//  Datang
//  帧数据
//  Created by 于志鹏 on 13-2-4.
//
//

#ifndef __Datang__YYFrameData__
#define __Datang__YYFrameData__

#include "cocos2d.h"

USING_NS_CC;

class YYFrameData:public CCObject{

public:
    YYFrameData();
    ~YYFrameData();
    unsigned short rectAmount;//矩形图块数量
    CCArray *rectIndexArray;//矩形图块索引
    CCArray *transformTypeArray;//矩形图块翻转类型
    CCArray *rectXArray,*rectYArray;//矩形图块左上角坐标
    
    static YYFrameData * createFrameData(unsigned short rectAmount);
};

#endif /* defined(__Datang__YYFrameData__) */