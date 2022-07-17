//
// Created by luca on 07/07/22.
//
#include "gtest/gtest.h"
#include "../PlayableCharacter.h"
#include "../Enemy.h"
#define private public
#include "../Map.h"
class MapTest: public ::testing::Test {
protected:
    std::vector<ResourceManager> charactersResources;
    std::vector<ResourceManager> abilityResources;
    sf::Texture tileMap;
    std::unique_ptr<PlayableCharacter> player;
    std::unique_ptr<Map> map;
    std::list<std::unique_ptr<Enemy>> enemies;
    MapTest() {
        for (int i=KNIGHT;i<=SKELETON;i++)
            charactersResources.emplace_back();
        for(int i=THUNDER;i<=THUNDER_STORM;i++)
            abilityResources.emplace_back();
        tileMap.loadFromFile("../Resources/DungeonCrawl_ProjectUtumnoTileset.png");
        charactersResources[KNIGHT].addTexture("KNIGHT", "../Resources/Knight.png");
        charactersResources[SKELETON].addTexture("SKELETON", "../Resources/Skeleton.png");
        charactersResources[SLIME].addTexture("SLIME", "../Resources/Slime.png");
        charactersResources[KNIGHT].addAnimation(AnimationName::IDLE, 50, 37, 0, 0, 3, 0, 100);
        charactersResources[SKELETON].addAnimation(AnimationName::MOVE, 50, 48, 0, 2, 5, 2, 150);
        charactersResources[SKELETON].addAnimation(AnimationName::ATTACK, 50, 48, 0, 1, 5, 1, 200);
        charactersResources[SLIME].addAnimation(AnimationName::MOVE, 32, 25, 0, 4, 3, 4, 150);
        charactersResources[SLIME].addAnimation(AnimationName::ATTACK, 32, 25, 0, 0, 4, 0, 200);
        player=std::make_unique<PlayableCharacter>(charactersResources[KNIGHT],abilityResources);
        map=std::make_unique<Map>(tileMap,charactersResources,*player,enemies);
    }
};

TEST_F(MapTest,mapCollisions){
    map->map[0][0].setTile(Map::TileType::WALL,map->tiles);
    player->setPosition(map->tileWidth,0);
    ASSERT_TRUE(map->checkCollision(player->getHitbox()));
    player->move(20,0);
    ASSERT_FALSE(map->checkCollision(player->getHitbox()));

}
TEST_F(MapTest,pathFinding){
    Enemy::updateTimer(1000);
    sf::Vector2i roomCenter=map->rooms[0].getCenter();
    Enemy enemy=Enemy(charactersResources[SKELETON],roomCenter.x,roomCenter.y);
    player->setPosition(roomCenter.x+80,roomCenter.y);
    enemy.update(0.01,*player);
    ASSERT_TRUE(enemy.isAggroed());
    ASSERT_EQ(enemy.distanceToPlayer(player->getPosition()),80);
    map->updateDistanceValues();
    enemy.setDirection(map->getDiredctionToPlayer(enemy.getPosition().x/map->tileWidth,enemy.getPosition().y/map->tileHeight));
    enemy.update(0.01,*player);
    ASSERT_TRUE(enemy.distanceToPlayer(player->getPosition())>78.9&&enemy.distanceToPlayer(player->getPosition())<79.1);
}