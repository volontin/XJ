//
//  YYEnemy.h
//  XJ
//  敌人
//  Created by 于志鹏 on 13-4-22.
//
//

#ifndef __XJ__YYEnemy__
#define __XJ__YYEnemy__

#include "YYFightSprite.h"

#define ACTION_STAND 1
#define ACTION_WALK 3
#define ACTION_ATTACK_0 5

class YYEnemy : public YYFightSprite{
    CC_SYNTHESIZE_RETAIN(YYFightSprite *, targetSprite, TargetSprite);//攻击目标
    CC_SYNTHESIZE(CCSize, rangeOfVisibility, RangeOfVisibility);//视距
private:
    uint8_t attackInterval;//攻击间隔
    uint8_t attackIntervalCounter;//间隔计数器
    bool isAttackable;//可以攻击
public:
    YYEnemy();
    ~YYEnemy();
    CREATE_FUNC(YYEnemy);
    virtual void update(void);
    virtual void move(void);
    virtual void move(CCSize offset);
    virtual void updateAnimation(void);
    void processAI();
    void calcDamage();
    void setFightData();
};
#endif /* defined(__XJ__YYEnemy__) */
