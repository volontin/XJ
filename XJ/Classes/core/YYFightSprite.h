//
//  YYFightSprite.h
//  XJ
//  战斗精灵
//  Created by 于志鹏 on 13-4-24.
//
//

#ifndef XJ_YYFightSprite_h
#define XJ_YYFightSprite_h

#include "YYSprite.h"

class YYFightSprite : public YYSprite{
    CC_SYNTHESIZE(CCSize, rangeOfAttack, RangeOfAttack);
protected:
    int16_t hp;
    //    int16_t mp;
    //    int8_t strenghPoint;//力量
    //    int8_t intelligencePoint;//智力
    //    int8_t agilityPoint;//敏捷
    //    int8_t spiritPoint;//精神
    //    int8_t endurancePoint;//耐力
    //    int8_t luckPoint;//幸运
    int16_t attackPoint;//攻击力
    int16_t defencePoint;//防御力
    //    int16_t spellAttackPoint;//法术攻击
    //    int16_t spellResistence;//法术抗性
    //    int8_t attackFrequenry;//攻击频次
    //    int8_t spellInterval;//施法间隔
public:
    YYFightSprite(void);
    ~YYFightSprite(void);
    virtual void updateAnimation(void){
    }
    virtual void update(void){
    }
    virtual void move(void){
    }
    virtual void move(CCSize offset){
        CC_UNUSED_PARAM(offset);
    }
};

#endif
