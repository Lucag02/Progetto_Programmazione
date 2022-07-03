//
// Created by luca on 03/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ITEM_H
#define PROGETTO_PROGRAMMAZIONE_ITEM_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include<memory>
#include "Hitbox.h"

class Item {
private:
    enum class ItemType:int {HEALING_POTION=0,SPEED_POTION=1};
    sf::RectangleShape shape;
    ItemType type;
    sf::Text description;
    bool isOnGround;
    int listPosition;
public:
    explicit Item(const sf::Texture& texture,float x=0,float y=0,int type=0);
    void update(const Hitbox &hitbox, std::list<std::unique_ptr<Item>> &groundItems,
                std::list<std::unique_ptr<Item>> &inventory);
    void render(sf::RenderTarget& target);
};


#endif //PROGETTO_PROGRAMMAZIONE_ITEM_H
