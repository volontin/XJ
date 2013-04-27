//
//  YYRect.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-4.
//
//

#include "YYRect.h"

YYRect::YYRect()
:x(0)
,y(0)
,width(0)
,height(0)
,imageIndex(0)
{
}

YYRect::~YYRect(){
    
}

YYRect * YYRect::createRect(YYRect *rect){
    YYRect * newRect = new YYRect();
    newRect->x = rect->x;
    newRect->y = rect->y;
    newRect->width = rect->width;
    newRect->height = rect->height;
    return newRect;
}
YYRect * YYRect::createRect(int x,int y,int w,int h){
    YYRect * rect = new YYRect();
    rect->x = x;
    rect->y = y;
    rect->width = w;
    rect->height = h;
    return rect;
}