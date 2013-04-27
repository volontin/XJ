//
//  YYEnemy.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-22.
//
//

#include "YYEnemy.h"
#include "Common.h"

#define HORIZONTAL_SPEED 15
#define VERTICAL_SPEED 10

YYEnemy::YYEnemy(void)
:attackInterval(0)
,attackIntervalCounter(0)
,targetSprite(NULL)
{
    spriteType = SPRITE_TYPE_PLAYER;
}

YYEnemy::~YYEnemy(void){
    
}

void YYEnemy::setFightData(){
    setRangeOfVisibility(CCSizeMake(450, 150));
    setRangeOfAttack(CCSizeMake(80, 20));
    attackInterval = 30;
    attackIntervalCounter = 30;
}

void YYEnemy::update(void){
    processAI();
    calcDamage();
    updateAnimation();
}

void YYEnemy::move(void){
    
}

void YYEnemy::move(CCSize offset){
    
}

void YYEnemy::updateAnimation(){
    if (frameIntervalCount< actualInterval) {
        frameIntervalCount ++;
    }else{
        frameIntervalCount = 0;
        if(currentFrameIndex < getCurrentActionData()->endFrameIndex){
            currentFrameIndex ++;
            setFrameByID(currentFrameIndex,isFaceToRight());
        }else{
            isAnimationOver = true;
            if(isRepeatAnimation){
                currentFrameIndex = getCurrentActionData()->startFrameIndex;
                setFrameByID(currentFrameIndex,isFaceToRight());
            }else{
                switch (_animationID) {
                    case ACTION_STAND:
                    case ACTION_WALK:
                        currentFrameIndex = getCurrentActionData()->startFrameIndex;
                        setFrameByID(currentFrameIndex,_isFaceToRight);
                        break;
                    case ACTION_ATTACK_0:
                        setAnimationByID(ACTION_STAND, true, isFaceToRight());
                        setActionState(kActionNormal);
                        break;
                    default:
                        currentFrameIndex = getCurrentActionData()->endFrameIndex;
                        break;
                }
            }
        }
        setPosition(ccpAdd(offsetPerFrame, getPosition()));
    }
}

void YYEnemy::processAI(){
    if(targetSprite){
        //攻击间隔计算
        if (attackIntervalCounter < attackInterval) {
            attackIntervalCounter ++;
        }else{
            attackIntervalCounter = 0;
            isAttackable = true;
        }
        if (getActionState() != kActionAttack) {//不中断已经进行的攻击
            //视距范围内发现目标
            if (targetSprite->getPosition().x > getPosition().x - rangeOfVisibility.width
                && targetSprite->getPosition().x < getPosition().x + rangeOfVisibility.width
                && targetSprite->getPosition().y > getPosition().y - rangeOfVisibility.height
                && targetSprite->getPosition().y < getPosition().y + rangeOfVisibility.height)
            {
                setFaceToRight(targetSprite->getPosition().x > getPosition().x);//根据目标位置设置朝向
                
                if (getPosition().y >= targetSprite->getPosition().y + VERTICAL_SPEED) {
                    setOffsetPerFrame(ccp(0,-VERTICAL_SPEED));
                    setAnimationByID(ACTION_WALK, true, isFaceToRight());
                }else if(getPosition().y <= targetSprite->getPosition().y - VERTICAL_SPEED){
                    setOffsetPerFrame(ccp(0,VERTICAL_SPEED));
                    setAnimationByID(ACTION_WALK, true, isFaceToRight());
                }else{
                    int8_t offsetX = 0;
                    int8_t offsetY = targetSprite->getPosition().y - getPosition().y;
                    if (isFaceToRight()) {
                        if (targetSprite->getPosition().x > getPosition().x + rangeOfAttack.width){//攻击范围外
                            if(targetSprite->getPosition().x >= getPosition().x + rangeOfAttack.width + HORIZONTAL_SPEED){
                                setOffsetPerFrame(ccp(HORIZONTAL_SPEED,offsetY));
                            }else{
                                offsetX = targetSprite->getPosition().x - getPosition().x - rangeOfAttack.width;
                                setOffsetPerFrame(ccp(offsetX,offsetY));
                            }
                            setAnimationByID(ACTION_WALK, true, isFaceToRight());
                        }else{
                            setOffsetPerFrame(ccp(0,0));
                            if(isAttackable){
                                setAnimationByID(ACTION_ATTACK_0, false, isFaceToRight());
                                setActionState(kActionAttack);
                                isAttackable = false;
                            }else{
                                setAnimationByID(ACTION_STAND, true, isFaceToRight());
                            }
                        }
                        
                    }else{
                        if(targetSprite->getPosition().x < getPosition().x - rangeOfAttack.width){//攻击范围外
                            if(targetSprite->getPosition().x <= getPosition().x - rangeOfAttack.width - HORIZONTAL_SPEED){
                                setOffsetPerFrame(ccp(-HORIZONTAL_SPEED,offsetY));
                            }else{
                                offsetX = targetSprite->getPosition().x - (getPosition().x - rangeOfAttack.width);
                                setOffsetPerFrame(ccp(offsetX,offsetY));
                            }
                            setAnimationByID(ACTION_WALK, true, isFaceToRight());
                        }else{
                            setOffsetPerFrame(ccp(0,0));
                            if(isAttackable){
                                setAnimationByID(ACTION_ATTACK_0, false, isFaceToRight());
                                setActionState(kActionAttack);
                                isAttackable = false;
                            }else{
                                setAnimationByID(ACTION_STAND, true, isFaceToRight());
                            }
                        }
                    }
                }
            }else{
                setOffsetPerFrame(ccp(0,0));
                setAnimationByID(ACTION_STAND, true, isFaceToRight());
            }
        }
    }
}

void YYEnemy::calcDamage(){
    
}