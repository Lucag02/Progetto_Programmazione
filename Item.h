//
// Created by luca on 03/07/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ITEM_H
#define PROGETTO_PROGRAMMAZIONE_ITEM_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class PlayableCharacter;
class Item {
private:
    enum class ItemType:int {HEALING_POTION=0,SPEED_POTION,THUNDERSTORM_ABILITY};
    sf::RectangleShape shape;
    ItemType type;
    sf::Text description;
    bool onGround;
    bool showText;
    bool used;
public:
    static const int numItems=3;
    Item(const sf::Texture &texture, const sf::Font &font, float x = 0, float y = 0, int type = 0);
    void use(PlayableCharacter& player);
    void update(PlayableCharacter &player, sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);
    void setPosition(sf::Vector2f pos);
    bool isUsed() const;
    bool isOnGround() const;
    void setScale(sf::Vector2f scale);
};
#endif //PROGETTO_PROGRAMMAZIONE_ITEM_H