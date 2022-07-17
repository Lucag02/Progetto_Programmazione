//
// Created by luca on 08/07/22.
//
#include "gtest/gtest.h"
#include "../PlayableCharacter.h"
class ItemTest: public ::testing::Test {
protected:
    std::list<std::unique_ptr<Item>> groundItems;
    sf::Texture tileMap;
    sf::Font font;
    std::vector<ResourceManager> abilityResources;
    ResourceManager resources;
    std::unique_ptr<PlayableCharacter> player;
    ItemTest(){
        resources.addTexture("KNIGHT","../Resources/Knight.png");
        player=std::make_unique<PlayableCharacter>(resources,abilityResources);
        tileMap.loadFromFile("../Resources/DungeonCrawl_ProjectUtumnoTileset.png");
        font.loadFromFile("../Config/ComicSans.ttf");
        groundItems.emplace_back(std::make_unique<Item>(tileMap,font));
        player->getInventory().add(std::make_unique<Item>(tileMap,font));
    }
};

TEST_F(ItemTest, itemPickUp){
    player->setPosition(50,0);
    (*groundItems.begin())->update(*player, sf::Vector2f(0, 0));
    ASSERT_TRUE((*groundItems.begin())->isOnGround());
    player->setPosition(0,0);
    (*groundItems.begin())->update(*player, sf::Vector2f(0, 0));
    ASSERT_FALSE((*groundItems.begin())->isOnGround());
}

TEST_F(ItemTest,ItemUse){
    (*groundItems.begin())->use(*player);
    player->getInventory().add(std::move(*groundItems.begin()));
    ASSERT_EQ(player->getInventory().getCurrentSize(),2);
    player->getInventory().update(*player,sf::Vector2f(0,0));
    ASSERT_EQ(player->getInventory().getCurrentSize(),1);
}