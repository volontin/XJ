//
//  YYFightSprite.h
//  XJ
//  战斗精灵
//  Created by 于志鹏 on 13-4-24.
//
//

#ifndef XJ_YYFightSprite_h
#define XJ_YYFightSprite_h

#include "../animation/YYSprite.h"

class YYFightSprite : public YYSprite{
    CC_SYNTHESIZE(CCSize, rangeOfAttack, RangeOfAttack);
protected:
    int16_t healthPoint;//生命值
    //    int16_t manaPoint魔力值;
    //    int8_t strenghPoint;//力量
    //    int8_t intelligencePoint;//智力
    //    int8_t agilityPoint;//敏捷
    //    int8_t spiritPoint;//精神
    //    int8_t endurancePoint;//耐力
    //    int8_t luckPoint;//幸运
    int16_t attackPoint;//攻击力
    int16_t defencePoint;//防御力
    //    int16_t spellAttackPoint;//法术攻击
    //    int16_t spellResistencePoint;//法术抗性
    //    int8_t attackInterval;//攻击间隔
    //    int8_t spellInterval;//施法间隔
    int16_t metalPowerPoint;//金之力
    int16_t woodPowerPoint;//木之力
    int16_t waterPowerPoint;//水之力
    int16_t firePowerPoint;//火之力
    int16_t soilPowerPoint;//土之力
    int16_t metalResistencePoint;//金之抗
    int16_t woodResistencePoint;//木之抗
    int16_t waterResistencePoint;//水之抗
    int16_t fireResistencePoint;//火之抗
    int16_t soilResistencePoint;//土之抗
public:
    YYFightSprite(void);
    ~YYFightSprite(void);
    virtual void updateAnimation(void){
    }
    virtual void update(void){
    }
};

#endif
