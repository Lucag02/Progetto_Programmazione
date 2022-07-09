//
// Created by luca on 03/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ITEM_H
#define PROGETTO_PROGRAMMAZIONE_ITEM_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "PlayableCharacter.h"
class Item {
private:
    enum class ItemType:int {HEALING_POTION=0,SPEED_POTION,THUNDERSTORM_ABILITY};
    sf::RectangleShape shape;
    ItemType type;
    sf::Text description;
    bool isOnGround;
    bool showText;
    void use(PlayableCharacter& player);
    const static int maxItems;

public:
    static const int numItems=3;
    Item(const sf::Texture &texture, const sf::Font &font, float x = 0, float y = 0, int type = 0);
    void update(PlayableCharacter &player, sf::Vector2f mousePos, std::list<std::unique_ptr<Item>> &groundItems,
                std::list<std::unique_ptr<Item>> &inventory);
    void render(sf::RenderTarget& target);
    void setPosition(sf::Vector2f pos);
};


#endif //PROGETTO_PROGRAMMAZIONE_ITEM_H
