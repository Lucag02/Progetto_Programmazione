//
// Created by luca on 14/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_INVENTORY_H
#define PROGETTO_PROGRAMMAZIONE_INVENTORY_H
#include "Item.h"
#include "PlayableCharacter.h"
class PlayableCharacter;
class Item;
class Inventory{
private:
    int size;
    sf::RectangleShape background;
    std::vector<sf::RectangleShape> containers;
    std::list<std::unique_ptr<Item>> items;
public:
    explicit Inventory(int size=32);
    int getMaxSize();
    int getCurrentSize();
    void updatePosition(sf::Vector2f viewPos);
    void update(PlayableCharacter &player, sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);
    void add(std::unique_ptr<Item> item);
};


#endif //PROGETTO_PROGRAMMAZIONE_INVENTORY_H
