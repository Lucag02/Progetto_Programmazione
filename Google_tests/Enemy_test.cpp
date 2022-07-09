//
// Created by luca on 02/07/22.
//
#include "gtest/gtest.h"
#include "../PlayableCharacter.h"
#include "../Enemy.h"
#include "../Map.h"
class EnemyTest: public ::testing::Test {
protected:
    std::vector<ResourceManager> abilityResources;
    ResourceManager resources;
    std::unique_ptr<PlayableCharacter> player;
    std::unique_ptr<Enemy> enemy;
    EnemyTest(){
        resources.addTexture("KNIGHT","../Resources/Knight.png");
        resources.addTexture("SKELETON","../Resources/Skeleton.png");
        resources.addAnimation(AnimationName::MOVE,50, 48, 0, 2, 5, 2, 150);
        resources.addAnimation(AnimationName::ATTACK, 50, 48, 0, 1, 5, 1, 200);
        player=std::make_unique<PlayableCharacter>(resources,abilityResources);
        enemy=std::make_unique<Enemy>(resources);
    }
};
TEST_F(EnemyTest, CollisionWithPlayer){
    ASSERT_EQ(enemy->distanceToPlayer(player->getPosition()),0);
    ASSERT_TRUE(player->getHitbox().intersects(enemy->getHitbox().getGlobalBounds()));
    player->move(100,100);
    enemy->update(0.001,*player);
    ASSERT_EQ(enemy->isAggroed(),true);
    ASSERT_FALSE(player->getHitbox().intersects(enemy->getHitbox().getGlobalBounds()));
    player->setPosition(40,0);
    enemy->update(1,*player);
    enemy->update(1,*player);
    enemy->update(1,*player);
    ASSERT_EQ(player->getHealth(),290);
}
