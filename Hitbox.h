//
// Created by luca on 24/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_HITBOX_H
#define PROGETTO_PROGRAMMAZIONE_HITBOX_H
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class Hitbox: public sf::RectangleShape {
private:
    bool damageHitbox;
    float offsetX;
    float offsetY;
public:
    Hitbox(const sf::Sprite &characterSprite, float width, float height, bool damage,
           float offsetX = 0, float offsetY = 0);
    float getOffsetX() const;
    bool intersects(const sf::FloatRect& rect);
    float getOffsetY() const;
};


#endif //PROGETTO_PROGRAMMAZIONE_HITBOX_H
