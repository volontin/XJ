//
//  YYSprite.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-5.
//
//

#include "../common/Common.h"

#include "YYFrameData.h"
#include "YYRect.h"
#include "YYSprite.h"

YYSprite :: YYSprite(void)
:spriteType(0)
,actionState(0)
,actualInterval(0)
,frameIntervalCount(0)
,currentFrameIndex(0)//在帧列表中的序号
,pngFileNameArray(NULL)
,ani(NULL)
,currentActionData(NULL)
,isRepeatAnimation(false)
,isAnimationOver(false)
{
}

YYSprite::~YYSprite(){
    CC_SAFE_DELETE(pngFileNameArray);
    CC_SAFE_DELETE(ani);
    CC_SAFE_DELETE(currentActionData);
}

YYSprite * YYSprite::createWithAnimation(const std::string& aniFile,const std::string& pngFileName,const std::string& path){
    YYSprite * sprite = create();
    if (sprite != NULL) {
        sprite->initWithAnimation(aniFile,pngFileName,path);
    }
    return sprite;
    
}
void YYSprite::initWithAnimation(const std::string& aniFile,const std::string& pngFileName,const std::string& path){
    const std::string aniPath = path +"/"+ aniFile + ".anu";
    ani = YYAnimation::createAnimationWithFile(aniPath);
    
    CCArray* array = split_string(pngFileName.c_str(),',');
    pngFileNameArray = new CCArray(array->count());
    for (int i = 0; i < array->count(); i++) {
        CCString * str = (CCString*)array->objectAtIndex(i);
        if (str->isEqual(new CCString(""))) {//处理空图片
            pngFileNameArray-> addObject(new CCString("null"));
        }else{
            pngFileNameArray-> addObject(new CCString(path+"/"+str->getCString()+".png"));
        }
    }
    if (ani->imageAmount != pngFileNameArray->count()) {
        CCLog("error! imageAmount: %d,get imageCount:%d",ani->imageAmount,pngFileNameArray ->count());
    }
//    setFrameByID(0,false);
}
void YYSprite::setMoudle(int imgID ,CCRect rect, CCPoint position, unsigned char transform , int zOrder,bool isMirror){
    CCString* pngFileName = (CCString*)pngFileNameArray-> objectAtIndex(imgID);
    if (pngFileName->isEqual(new CCString("null"))) {//处理空图片
        return;
    }
    CCSprite *sprite = CCSprite::create(pngFileName->getCString(), rect);
    //    sprite->texture->setAntiAliasTexParameters();
    sprite->setPosition(position);
    if(isMirror){
        sprite->setScaleX(-1);
    }
    if (transform != 0) {
        unsigned char transformType = (transform & 0x07 >> 1);
        if (transformType == 1) {
            sprite->setScaleY(-1);
        }else if(transformType == 2){
            sprite->setScaleX(-1);
        }
        
    }
    //    spriteBatchNode.zOrder = zOrder;
    this->addChild(sprite , 1);
}
/**
 *清除上一帧切片
 */
void YYSprite::cleanupClipRect(){
    this->removeAllChildrenWithCleanup(true);
}
/**
 *通过精灵帧数据设置精灵帧
 */
void YYSprite::setFrame(YYFrameData * frameData,bool isMirror){
    if(frameData->rectAmount <= 0){
        return;
    }
    cleanupClipRect();
    for (int i = 0; i < frameData->rectAmount;i++) {
        int rectID = ((CCInteger *)frameData->rectIndexArray-> objectAtIndex(i))->getValue();
        YYRect *rect = (YYRect*)ani->imageRectDataArray ->objectAtIndex(rectID);
        float offSetX = ((CCInteger *)frameData->rectXArray->objectAtIndex(i))->getValue();
        float offSetY = ((CCInteger *)frameData->rectYArray-> objectAtIndex(i))->getValue();

        unsigned char transformType = ((CCInteger*)frameData->transformTypeArray->objectAtIndex(i))->getValue();
        
        CCRect rect1 = CCRectMake(rect->x, rect->y, rect->width, rect->height );
        
        CCPoint point = CCPointMake((offSetX + rect->width / 2.0f), -(offSetY + rect->height / 2.0f) );
        if (isMirror) {
            point  = CCPointMake(- (offSetX + rect->width / 2.0f), -(offSetY + rect->height / 2.0f) );
        }
        setMoudle(rect->imageIndex ,rect1, point ,transformType ,i,isMirror);
    }
}

/**
 *通过精灵帧ID设置精灵帧
 */
void YYSprite::setFrame(uint16_t frameID,bool isMirror){
    unsigned short index = ((CCInteger*)ani->frameIDArray->objectAtIndex(frameID))->getValue();
    YYFrameData *fd = (YYFrameData*)ani->frameDataArray-> objectAtIndex(index);
    setFrame(fd,isMirror);
    actualInterval = ((CCInteger*)ani->delayArray->objectAtIndex(index))->getValue();
}

/**
 *通过精灵动画ID设置精灵动画
 */
void YYSprite::setAnimation(uint16_t animationID ,bool isRepeat,bool isMirror){
    _animationID = animationID;
    isRepeatAnimation = isRepeat;
    isAnimationOver = false;
    currentActionData = (YYAnimationData*)ani->actionDataArray->objectAtIndex(animationID);
    currentFrameIndex = currentActionData->startFrameIndex;
    setFrame(currentFrameIndex,isMirror);
}

/**
 * 更新动画显示
 */
void YYSprite::updateAnimation(){
    if (frameIntervalCount< actualInterval) {
        frameIntervalCount ++;
    }else{
        frameIntervalCount = 0;
        currentFrameIndex ++;
        if(currentFrameIndex >= currentActionData->endFrameIndex){
            isAnimationOver = true;
            if(isRepeatAnimation){
                currentFrameIndex = currentActionData->startFrameIndex;
            }else{
                currentFrameIndex = currentActionData->endFrameIndex;
            }
        }
        setFrame(currentFrameIndex,_isFaceToRight);
    }
}

void YYSprite::setFaceToRight(bool isRight){
    _isFaceToRight = isRight;
}

bool YYSprite::isFaceToRight(){
    return _isFaceToRight;
}

int8_t YYSprite::getActionState(){
    return actionState;
}

void YYSprite::setActionState(uint8_t state){
    actionState = state;
}

bool YYSprite::isCollisioned(CCRect rect){
    YYFrameData * frameData = (YYFrameData *)ani->frameDataArray->objectAtIndex(currentFrameIndex);
    for (int i = 0; i < frameData->rectAmount;i++) {
        int rectID = ((CCInteger *)frameData->rectIndexArray-> objectAtIndex(i))->getValue();
        YYRect * imageRect = (YYRect *)ani->imageRectDataArray ->objectAtIndex(rectID);
        float offSetX = ((CCInteger *)frameData->rectXArray->objectAtIndex(i))->getValue();
        float offSetY = ((CCInteger *)frameData->rectYArray-> objectAtIndex(i))->getValue();
        CCPoint point = ccp(getPosition().x + offSetX, getPosition().y - offSetY);
        if (isFaceToRight()) {
            point  = ccp(getPosition().x - offSetX, getPosition().y - offSetY);
        }
        CCRect rect1 = CCRectMake(point.x, point.y, imageRect->width, imageRect->height);
        if (rect.intersectsRect(rect1)) {
            return true;
        }
    }
    return false;
}

bool YYSprite::isTouched(cocos2d::CCPoint point){
    YYFrameData * frameData = (YYFrameData *)ani->frameDataArray->objectAtIndex(currentFrameIndex);
    for (int i = 0; i < frameData->rectAmount;i++) {
        int rectID = ((CCInteger *)frameData->rectIndexArray-> objectAtIndex(i))->getValue();
        YYRect * imageRect = (YYRect *)ani->imageRectDataArray ->objectAtIndex(rectID);
        float offSetX = ((CCInteger *)frameData->rectXArray->objectAtIndex(i))->getValue();
        float offSetY = ((CCInteger *)frameData->rectYArray-> objectAtIndex(i))->getValue();
        CCPoint point1 = ccp(getPosition().x + offSetX, getPosition().y - offSetY);
        if (isFaceToRight()) {
            point1  = ccp(getPosition().x - offSetX, getPosition().y - offSetY);
        }
        if (point.x > point1.x && point.y > point1.y && point.x < point1.x + imageRect->width && point.y < point1.y + imageRect->height) {
            return true;
        }
    }
    return false;
}