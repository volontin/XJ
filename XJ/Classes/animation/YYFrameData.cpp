//
//  YYFrameData.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-4.
//
//

#include "YYFrameData.h"

YYFrameData::YYFrameData()
:rectAmount(0)
,rectIndexArray(NULL)
,transformTypeArray(NULL)
,rectXArray(NULL)
,rectYArray(NULL)
{
}

YYFrameData::~YYFrameData(){
    CC_SAFE_DELETE(rectIndexArray);
    CC_SAFE_DELETE(transformTypeArray);
    CC_SAFE_DELETE(rectXArray);
    CC_SAFE_DELETE(rectYArray);
}

YYFrameData* YYFrameData::createFrameData(unsigned short rectAmount){
    YYFrameData* frameData = new YYFrameData();
    frameData->rectAmount = rectAmount;
    frameData->rectIndexArray = new CCArray(rectAmount);
    frameData->transformTypeArray = new CCArray(rectAmount);
    frameData->rectXArray = new CCArray(rectAmount);
    frameData->rectYArray = new CCArray(rectAmount);
    return frameData;
}