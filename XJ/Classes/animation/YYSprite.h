//
//  YYSprite.h
//  Datang
//
//  Created by 于志鹏 on 13-2-5.
//
//

#ifndef __Datang__YYSprite__
#define __Datang__YYSprite__

#include "cocos2d.h"

#include "YYAnimation.h"
#include "YYAnimationData.h"
#include "YYFrameData.h"

USING_NS_CC;

#define SPRITE_TYPE_PLAYER 0
#define SPRITE_TYPE_NENMY 1

class YYSprite : public CCSprite{
    CC_SYNTHESIZE(uint8_t, actualInterval, ActualInterval);//实际间隔帧数
    CC_SYNTHESIZE(uint16_t, currentFrameIndex,CurrentFrameIndex);//在帧列表中的序号
    CC_SYNTHESIZE(CCSize ,size, Size);//精灵大小（宽、高）
    CC_SYNTHESIZE(float, top, Top);//精灵顶端
    CC_SYNTHESIZE(float, left, Left);//精灵左侧
    CC_SYNTHESIZE_RETAIN(YYAnimation *, ani, Animation);//精灵动作
    CC_SYNTHESIZE_RETAIN(CCArray *, pngFileNameArray, PngFileNameArray);//图片文件名称集合
    CC_SYNTHESIZE_RETAIN(YYAnimationData *, currentActionData, CurrentActionData);//当前动作数据
    CC_SYNTHESIZE(cocos2d::CCPoint, offsetPerFrame, OffsetPerFrame);//每帧偏移量
protected:
    uint8_t spriteType;//精灵类型
    uint8_t _animationID;//动作ID
    uint8_t actionState;//动作状态
    uint8_t frameIntervalCount;//帧间隔计数器
    bool _isFaceToRight;
    bool isRepeatAnimation,isAnimationOver;//是否重复动作，动作是否结束
public:
    YYSprite();
    ~YYSprite();
    CREATE_FUNC(YYSprite);
    static YYSprite * createWithAnimation(const std::string& aniFile,const std::string& pngFileName,const std::string& path);
    void initWithAnimation(const std::string& aniFile,const std::string& pngFileName,const std::string& path);
    void setMoudleByImageID(int imgID, CCRect rect ,CCPoint position ,unsigned char transform ,int zOrder,bool isMirror);
    void setFrameByFrameData(YYFrameData * frameData,bool isMirror);
    void setFrameByID(uint16_t frameID, bool isMirror);
    void setAnimationByID(uint16_t animationID ,bool isRepeat , bool isMirror);
    void cleanupClipRect(void);
    void setFaceToRight(bool isRight);
    bool isFaceToRight();
    virtual void updateAnimation(void);
    virtual void update(void){
    }
    int8_t getActionState();
    void setActionState(uint8_t actionState);
};
#endif /* defined(__Datang__YYSprite__) */