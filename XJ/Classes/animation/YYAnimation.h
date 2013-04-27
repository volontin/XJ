//
//  YYAnimation.h
//  Datang
//
//  Created by 于志鹏 on 13-2-4.
//
//

#ifndef __Datang__YYAnimation__
#define __Datang__YYAnimation__

#include <cocos2d.h>
USING_NS_CC;

class YYAnimation:public CCObject{
public:
    YYAnimation();
    ~YYAnimation();
    /** 图片数量 */
    unsigned char imageAmount;
    /** 总切片数*/
    unsigned short clipAmount;
    /** 总帧数*/
    unsigned short frameAmount;
    /** 动作数 */
    unsigned short actionAmount;
    
    /** 图片矩形块数 */
    CCArray *imageRectCountArray;
    /** 矩形块数据 */
    CCArray *imageRectDataArray;
    /** 动作数据 */
    CCArray *actionDataArray;
    /** 帧数据*/
    CCArray *frameDataArray;
    /** 帧ID数据*/
    CCArray *frameIDArray;
    /** 延迟的帧数*/
    CCArray * delayArray;
    /** 每帧在x轴方向的偏移量 */
    CCArray * offsetXArray;
    /** 每帧在y轴方向的偏移量 */
    CCArray * offsetYArray;
    static CCDictionary * resourcesCache();
    static YYAnimation* createAnimationWithFile(const std::string& aniFileName);
};
#endif /* defined(__Datang__YYAnimation__) */