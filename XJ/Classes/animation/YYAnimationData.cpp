//
//  YYAnimationData.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-4.
//
//

#include "YYAnimationData.h"

YYAnimationData::YYAnimationData(){
    
}

YYAnimationData::~YYAnimationData(){
    
}

YYAnimationData * YYAnimationData::createActionDataFrom(unsigned short startFrameIndex,unsigned short endFrameIndex){
    YYAnimationData * animationData = new YYAnimationData();
    animationData->startFrameIndex = startFrameIndex;
    animationData->endFrameIndex = endFrameIndex;
    return animationData;
}
