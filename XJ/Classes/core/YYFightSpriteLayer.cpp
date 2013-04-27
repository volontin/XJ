//
//  YYFightSpriteLayer.cpp
//  XJ
//
//  Created by 于志鹏 on 13-4-27.
//
//

#include "YYFightSpriteLayer.h"
#include "YYPlayer.h"
#include "YYEnemy.h"

USING_NS_CC;

YYFightSpriteLayer::YYFightSpriteLayer()
:player(NULL)
{    
}

YYFightSpriteLayer::~YYFightSpriteLayer(){
    CC_SAFE_DELETE(player);
}

void YYFightSpriteLayer::onEnter(){
    player = YYPlayer::create();
    player->initWithAnimation("role0", "role0", "action");
    CCPoint position = ccp(100,200);
    player->setPosition(position);
    CCPoint point = player->getPosition();
    player->setAnimationByID(1, true, true);
    addChild(player);
    YYEnemy * enemy = YYEnemy::create();
    enemy->initWithAnimation("enemy1", "enemy1", "action");
    position = ccp(700,200);
    enemy->setPosition(position);
    enemy->setAnimationByID(1, true, false);
    enemy->setTargetSprite(player);
    enemy->setFightData();
    addChild(enemy);
}

void YYFightSpriteLayer::update(void){
    sortSprite();
    for(int i = 0;i < getChildren()->count();i++){
        YYFightSprite * fs = (YYFightSprite *)getChildren()->objectAtIndex(i);
        fs -> update();
    }
}

/**
 * 精灵排序
 */
void YYFightSpriteLayer::sortSprite(){
    for (int i = 0; i < getChildren()->count();i++) {
        YYFightSprite * sprite1 = (YYFightSprite *)getChildren()->objectAtIndex(i);
        YYFightSprite * fs = NULL;
        int x = i;
        for (int j = i + 1; j < getChildren()->count();j++) {
            YYFightSprite * sprite2 = (YYFightSprite *)getChildren()->objectAtIndex(j);
            if (sprite1->getPosition().y < sprite2->getPosition().y) {
                fs = sprite2;
                x = j;
            }
        }
        if (fs) {
            sprite1->retain();
            getChildren()->replaceObjectAtIndex(i, fs);//fs->retain(),sprite1->release()
            getChildren()->replaceObjectAtIndex(x, sprite1);
        }
    }
}

YYPlayer * YYFightSpriteLayer::getPlayer(){
    return player;
}