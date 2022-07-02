//
// Created by luca on 02/07/22.
//
#include "gtest/gtest.h"
#include "../PlayableCharacter.h"
#include "../Enemy.h"
#include "../Map.h"
class EnemyTest: public ::testing::Test {
protected:
    ResourceManager resources;
    std::unique_ptr<PlayableCharacter> player;
    std::unique_ptr<Enemy> enemy;
    EnemyTest(){
        resources.addTexture("KNIGHT","../../Resources/Knight.png");
        resources.addTexture("SKELETON","../../Resources/Skeleton.png");
        resources.addAnimation(AnimationName::MOVE,50, 48, 0, 2, 5, 2, 150);
        resources.addAnimation(AnimationName::ATTACK, 50, 48, 0, 1, 5, 1, 200);
        player=std::make_unique<PlayableCharacter>(resources);
        enemy=std::make_unique<Enemy>(resources);
    }
};
TEST_F(EnemyTest, CollisionWithPlayer){
    Enemy::updateTimer(10);
    ASSERT_EQ(enemy->distanceToPlayer(player->getPosition()),0);
    ASSERT_EQ(player->getHitbox().intersects(enemy->getHitbox().getGlobalBounds()),true);
    player->move(100,100);
    enemy->update(0.001,*player);
    ASSERT_EQ(enemy->isAggroed(),true);
    ASSERT_EQ(player->getHitbox().intersects(enemy->getHitbox().getGlobalBounds()),false);
}
