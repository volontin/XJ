//
//  YYRect.h
//  Datang
//
//  Created by 于志鹏 on 13-2-4.
//
//

#ifndef __Datang__YYRect__
#define __Datang__YYRect__

#include "cocos2d.h"
USING_NS_CC;

class YYRect:public CCObject
{
public:
    YYRect();
    ~YYRect();
    int x,y,width,height;
    unsigned char imageIndex;
    static YYRect * createRect(YYRect * rect);
    static YYRect * createRect(int x,int y, int w,int h);
};
#endif /* defined(__Datang__YYRect__) */