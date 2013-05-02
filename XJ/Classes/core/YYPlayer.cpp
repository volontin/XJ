//
//  YYPlayer.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-22.
//
//

#include "../common/Common.h"
#include "YYPlayer.h"
#include "YYScene.h"

#define HORIZONTAL_SPEED 21
#define VERTICAL_SPEED 14

#define UP_BORDER 250
#define DOWN_BORDER 10
#define BODY_WIDTH 20



YYPlayer::YYPlayer()
:isHoldFire(false)
,isContinueAttack(false)
{
    spriteType = SPRITE_TYPE_PLAYER;
}

YYPlayer::~YYPlayer(){
    
}

void YYPlayer::update(void){
    if (isHoldFire) {
        if (getActionState() == kActionNormal) {
            setActionState(kActionAttack);
            setAnimation(ACTION_ATTACK_0, false, isFaceToRight());
        }else if(currentFrameIndex > getCurrentActionData()->startFrameIndex + 1){
            isContinueAttack = true;
        }
    }
    updateAnimation();
    
}

void YYPlayer::move(void){
    
}

void YYPlayer::move(CCSize offset){
    
}

void YYPlayer::updateAnimation(){
    if (frameIntervalCount< actualInterval) {
        frameIntervalCount ++;
    }else{
        frameIntervalCount = 0;
        if(currentFrameIndex < getCurrentActionData()->endFrameIndex){
            currentFrameIndex ++;
            setFrame(currentFrameIndex,isFaceToRight());
        }else{
            isAnimationOver = true;
            if(isRepeatAnimation){
                currentFrameIndex = getCurrentActionData()->startFrameIndex;
                setFrame(currentFrameIndex,isFaceToRight());
            }else{
                switch (_animationID) {
                    case ACTION_STAND:
                    case ACTION_WALK:
                        currentFrameIndex = getCurrentActionData()->startFrameIndex;
                        setFrame(currentFrameIndex,_isFaceToRight);
                        break;
                    case ACTION_ATTACK_0:
                        if(isContinueAttack){
                            isContinueAttack = false;
                            setAnimation(ACTION_ATTACK_0, false, isFaceToRight());
                            setActionState(kActionAttack);
                        }else{
                            setAnimation(ACTION_STAND, true, isFaceToRight());
                            setActionState(kActionNormal);
                        }
                        
                        break;
                    default:
                        currentFrameIndex = getCurrentActionData()->endFrameIndex;
                        break;
                }
            }
        }

        CCPoint tempPosition = ccpAdd(offsetPerFrame, getPosition());
        if (tempPosition.x < BODY_WIDTH) {
            tempPosition.x = BODY_WIDTH;
        }else if(tempPosition.x > YYScene::sharedScene()->getSceneSize().width - BODY_WIDTH){
            tempPosition.x = YYScene::sharedScene()->getSceneSize().width - BODY_WIDTH;
        }
        if (tempPosition.y < DOWN_BORDER) {
            tempPosition.y = DOWN_BORDER;
        }else if(tempPosition.y > UP_BORDER){
            tempPosition.y = UP_BORDER;
        }
        setPosition(tempPosition);
    }
}

void YYPlayer::touchBegan(CCPoint preTouch,CCPoint currentTouch){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if (isPointInCircle(currentTouch, ccp(size.width - 120,120), 50)) {//attack
        isHoldFire = true;
    }else if(getActionState() == kActionNormal && getDirection(currentTouch, ccp(120,120),100) != kDirectionNull){//walk
        setActionState(kActionNormal);
        switch (getDirection(currentTouch, ccp(120,120), 100)) {
            case kDirectionUp:
                setOffsetPerFrame(ccp(0,VERTICAL_SPEED));
                break;
            case kDirectionDown:
                setOffsetPerFrame(ccp(0,-VERTICAL_SPEED));
                break;
            case kDirectionLeft:
                setOffsetPerFrame(ccp(-HORIZONTAL_SPEED,0));
                setFaceToRight(false);
                break;
            case kDirectionRight:
                setOffsetPerFrame(ccp(HORIZONTAL_SPEED,0));
                setFaceToRight(true);
                break;
            case kDirectionUp_Left:
                setOffsetPerFrame(ccp(-HORIZONTAL_SPEED,VERTICAL_SPEED));
                setFaceToRight(false);
                break;
            case kDirectionUp_Right:
                setOffsetPerFrame(ccp(HORIZONTAL_SPEED,VERTICAL_SPEED));
                setFaceToRight(true);
                break;
            case kDirectionDown_Left:
                setOffsetPerFrame(ccp(-HORIZONTAL_SPEED,-VERTICAL_SPEED));
                setFaceToRight(false);
                break;
            case kDirectionDown_Right:
                setOffsetPerFrame(ccp(HORIZONTAL_SPEED,-VERTICAL_SPEED));
                setFaceToRight(true);
                break;
            default:
                break;
        }
        setAnimation(ACTION_WALK, true,isFaceToRight());
    }
}

void YYPlayer::touchMoved(CCPoint preTouch,CCPoint currentTouch){
    
}

void YYPlayer::touchEnded(CCPoint preTouch,CCPoint currentTouch){
    isHoldFire = false;
    if (getActionState() == kActionNormal) {
        setOffsetPerFrame(ccp(0,0));
        setAnimation(ACTION_STAND,true,isFaceToRight());
    }
}