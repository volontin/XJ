//
//  YYPlayer.h
//  XJ
//  玩家可控角色
//  Created by 于志鹏 on 13-4-22.
//
//

#ifndef __XJ__YYPlayer__
#define __XJ__YYPlayer__

#include "YYFightSprite.h"

#define ACTION_STAND 1
#define ACTION_WALK 3
#define ACTION_ATTACK_0 5

class YYPlayer : public YYFightSprite{
    
private:
    bool isContinueAttack;
    bool isHoldFire;
public:
    YYPlayer();
    ~YYPlayer();
    CREATE_FUNC(YYPlayer);
    virtual void update(void);
    virtual void move(void);
    virtual void move(CCSize offset);
    virtual void updateAnimation(void);
    void touchBegan(cocos2d::CCPoint preTouch,cocos2d::CCPoint currentTouch);
    void touchMoved(cocos2d::CCPoint preTouch,cocos2d::CCPoint currentTouch);
    void touchEnded(cocos2d::CCPoint preTouch,cocos2d::CCPoint currentTouch);
};

#endif /* defined(__XJ__YYPlayer__) */
