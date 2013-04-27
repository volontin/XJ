//
//  YYAnimation.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-4.
//
//

#include "FileReadManager.h"
#include "YYAnimation.h"
#include "YYAnimationData.h"
#include "YYFrameData.h"
#include "YYRect.h"

YYAnimation::YYAnimation()
:imageAmount(0)
,clipAmount(0)
,frameAmount(0)
,actionAmount(0)
,imageRectCountArray(NULL)
,imageRectDataArray(NULL)
,actionDataArray(NULL)
,frameDataArray(NULL)
,frameIDArray(NULL)
,delayArray(NULL)
,offsetXArray(NULL)
,offsetYArray(NULL)
{
}

YYAnimation::~YYAnimation(){
    CC_SAFE_DELETE(imageRectCountArray);
    CC_SAFE_DELETE(imageRectDataArray);
    CC_SAFE_DELETE(actionDataArray);
    CC_SAFE_DELETE(frameDataArray);
    CC_SAFE_DELETE(frameIDArray);
    CC_SAFE_DELETE(delayArray);
    CC_SAFE_DELETE(offsetXArray);
    CC_SAFE_DELETE(offsetYArray);
}
static CCDictionary * resCache = NULL;
CCDictionary * YYAnimation::resourcesCache(){
    if(resCache == NULL){
        resCache = new CCDictionary::CCDictionary();
    }
    return resCache;
}

YYAnimation* YYAnimation::createAnimationWithFile(const std::string& aniFileName){
    YYAnimation *ani = NULL;
    CCDictionary * dictionary = YYAnimation::resourcesCache();
    ani = (YYAnimation*)dictionary-> objectForKey(aniFileName);
    if (ani != NULL) {
        return ani;
    }
    ani = new YYAnimation();
    FileReadManager * fileReadManager = new FileReadManager();
    fileReadManager->readFileData(aniFileName.c_str(),"r");
    fileReadManager-> readShort();//文件字节数？
    fileReadManager-> readUTF();//版本号？
    
    ani->actionAmount =  fileReadManager->readByte();//包含动作数
    ani->actionDataArray = new CCArray(ani->actionAmount);
    
    for (int i = 0; i<ani->actionAmount; i++) {
        short startIndex = fileReadManager->readShort();//起始帧序号
        short endIndex = fileReadManager->readShort();//终止帧序号
        YYAnimationData * actData = YYAnimationData::createActionDataFrom(startIndex ,endIndex);
        ani->actionDataArray-> addObject(actData);
    }
    ani->frameAmount = fileReadManager->readShort();//总帧数
    
    ani->frameIDArray = new CCArray(ani->frameAmount);
    ani->delayArray = new CCArray(ani->frameAmount);
    ani->offsetXArray = new CCArray(ani->frameAmount);
    ani->offsetYArray = new CCArray(ani->frameAmount);
    unsigned char delay = 1;
    unsigned short frameID = 0,offX = 0,offY = 0;
    for (int i = 0; i< ani->frameAmount; i++) {
        frameID = fileReadManager->readShort();//帧序号
        delay = fileReadManager->readByte(); //延迟
        offX = fileReadManager->readShort();//x轴方向位移
        offY = fileReadManager->readShort();//y轴方向位移
        ani->frameIDArray-> addObject(CCInteger::create(frameID));
        ani->delayArray ->addObject(CCInteger::create(delay));
        ani->offsetXArray-> addObject(CCInteger::create(offX));
        ani->offsetYArray ->addObject(CCInteger::create(offY));
    }
    ani->clipAmount = fileReadManager->readShort();//组成帧的切片总数
    
    int frameNum = fileReadManager->readShort();//实际帧数
    ani->frameDataArray = new CCArray(frameNum);
    
    for (int i = 0; i < frameNum; i++) {
        short clipCount = fileReadManager->readShort();//每帧所包含的切片数量
        YYFrameData *fd = YYFrameData::createFrameData(clipCount);
        
        for (int j = 0; j<clipCount; j++) {
            short rectIndex = fileReadManager->readShort();//切块在图片中的索引
            //图片切块在该帧内的位置信息
            short x =fileReadManager->readShort();
            short y= fileReadManager->readShort();
            
            char transformType =fileReadManager->readByte();//翻转类型
            fd->rectIndexArray ->addObject(CCInteger::create(rectIndex));
            fd->rectXArray ->addObject(CCInteger::create(x));
            fd->rectYArray ->addObject(CCInteger::create(y));
            fd->transformTypeArray-> addObject(CCInteger::create(transformType));
        }
        ani->frameDataArray-> addObject(fd);
    }
    short imgClipCount = fileReadManager->readShort();//总切片数
    
    ani->imageRectDataArray = new CCArray(imgClipCount);
    ani->imageAmount = fileReadManager->readByte();//图片数
    
    ani->imageRectCountArray = new CCArray(ani->imageAmount);
    
    for (int i = 0; i < ani->imageAmount; i++) {
        short rectNum = fileReadManager->readShort();//单张图片的切片数
        ani->imageRectCountArray-> addObject(CCInteger::create(rectNum));
        for (int j = 0; j<rectNum; j++) {
            //切片在图片上的位置信息
            short u = fileReadManager->readShort();
            short v = fileReadManager->readShort();
            short width = fileReadManager->readShort();
            short height = fileReadManager->readShort();
            YYRect *rect = YYRect::createRect(u,v,width ,height);
            rect->imageIndex = i;
            ani->imageRectDataArray ->addObject(rect);
        }
    }
    dictionary->setObject(ani,aniFileName);
    return ani;
    
}