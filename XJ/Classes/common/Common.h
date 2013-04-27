//
//  Common.h
//  XJ
//
//  Created by 于志鹏 on 13-2-7.
//
//
#include "cocos2d.h"

#ifndef XJ_Common_h
#define XJ_Common_h

#define RANDOM_INT(__MIN__, __MAX__) ((__MIN__) + random() % ((__MAX__ + 1) - (__MIN__)))

//---------游戏状态----------

enum {
    kStateLoading = 0, //游戏加载状态
    kStateCity,
    kStateDungeons,
    kStateArena,
    kStateMenu,
};

//————————动作状态————————————
enum {
    kActionNormal = 0,
    kActionAttack
};

//-----------精灵切片翻转方式------------
#define TRANS_NONE 0
#define TRANS_MIRROR_ROT180 1
#define TRANS_MIRROR 2
#define TRANS_ROT180 3
#define TRANS_MIRROR_ROT270 4
#define TRANS_ROT90 5
#define TRANS_ROT270 6
#define TRANS_MIRROR_ROT90 7
//-----------精灵切片翻转方式end------------

//-------------联网主机地址---------------
#define CON_SOCKET_URL "119.161.223.42"//测试网
#define CON_SOCKET_PORT 9026
//-------------联网主机地址end---------------

//——————————登录信息——————————
#define Kc "YoyO0DTXY1"
#define INS "DT100"
#define SP "00"
#define DEVICE "zMUD"
#define UPW "ooozoooz"
//——————————登录信息end——————————

//--------------战斗相关--------------
/**
 * 待机，静止不动
 */
#define HERO_STAND  0

/**
 * 待机的休闲动作
 */
#define HERO_RELAXATION 1
/**
 * 移动
 */
#define HERO_MVOE 2
/**
 * 攻击1
 */
#define HERO_ATTACK1 3

/**
 * 攻击2
 */
#define HERO_ATTACK2 4

/**
 * 释放技能
 */
#define HERO_SKILL 5

/**
 * 死亡
 */
#define HERO_DEAD 6

/**
 * 挨打
 */
#define HERO_BIT 7

/**
 * 单向动作总数
 */
#define ACTION_AMOUNT 8

#define STATE_EMBATTLE 0 //等待

#define STATE_BATTLE_START 1 //开始战斗

#define STATE_BATTLE_OVER 2 //战斗结束

#define STATE_BATTLE_REPORT 3//战报
//--------------战斗相关end--------------

enum {
    kDirectionNull = -1,
    kDirectionUp,
    kDirectionDown,
    kDirectionLeft,
    kDirectionRight,
    kDirectionUp_Left,
    kDirectionUp_Right,
    kDirectionDown_Left,
    kDirectionDown_Right
};

static cocos2d::CCArray * split_string(const char *src, char token){
    assert(src != NULL);
    if(*src == -1){
        return NULL;
    }else{
        std::vector<std::string> vec_result;
        char *start = (char *)src;
        char *end = NULL;
        int count = 0;
        while ( (end = strchr(start, token)) != NULL )
        {
            if ( end != start )
            {
                std::string buffer(start, end - start);
                vec_result.push_back(buffer);
                ++count;
            }
            start = end + 1;
        }
        if(start){
            vec_result.push_back(start);
        }else{
            vec_result.push_back("");
        }
        ++count;
        cocos2d::CCArray * array = new cocos2d::CCArray(count);
        for (int i = 0; i < count; i++) {
            std::string str = vec_result.at(i);
            array-> addObject(new cocos2d::CCString(str));
        }
        return array;
    }
}

static bool isPointInCircle(cocos2d::CCPoint point,cocos2d::CCPoint centerPoint,int16_t radius){
    int distanceSquare = (point.x - centerPoint.x) * (point.x - centerPoint.x) + (point.y - centerPoint.y) * (point.y - centerPoint.y);
    if (distanceSquare < radius * radius) {
        return true;
    }
    return false;
}

static int getDirection(cocos2d::CCPoint point,cocos2d::CCPoint centerPoint,int16_t radius){
    if (isPointInCircle(point, centerPoint, radius)) {
        int horizontalDistanceSquare = (point.x - centerPoint.x) * (point.x - centerPoint.x);
        int verticalDistanceSquare = (point.y - centerPoint.y) *(point.y - centerPoint.y);
        if ((horizontalDistanceSquare << 2) < verticalDistanceSquare) {
            if (point.y > centerPoint.y) {
                return kDirectionUp;
            }else{
                return kDirectionDown;
            }
        }else if((verticalDistanceSquare << 2) < horizontalDistanceSquare){
            if (point.x > centerPoint.x) {
                return kDirectionRight;
            }else{
                return kDirectionLeft;
            }
        }else{
            if (point.x > centerPoint.x) {
                if(point.y > centerPoint.y){
                    return kDirectionUp_Right;
                }else{
                    return kDirectionDown_Right;
                }
            }else{
                if(point.y > centerPoint.y){
                    return kDirectionUp_Left;
                }else{
                    return kDirectionDown_Left;
                }
            }
        }
    }
    return kDirectionNull;
}

#endif
