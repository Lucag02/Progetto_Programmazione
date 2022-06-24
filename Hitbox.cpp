//
// Created by luca on 24/06/22.
//

#include "Hitbox.h"
Hitbox::Hitbox(const sf::Sprite &characterSprite, float width, float height, bool damage, float offsetX, float offsetY)
        : damageHitbox(damage), offsetX(offsetX), offsetY(offsetY) {
    setSize(sf::Vector2f(width, height));
    setPosition(characterSprite.getPosition().x - offsetX, characterSprite.getPosition().y - offsetY);
    setOutlineThickness(1);
    setFillColor(sf::Color::Transparent);
    if (damageHitbox)
        this->setOutlineColor(sf::Color::Red);
    else
        this->setOutlineColor(sf::Color::Green);
}
float Hitbox::getOffsetX() const {
    return offsetX;
}
float Hitbox::getOffsetY() const {
    return offsetY;
}

bool Hitbox::intersects(const sf::FloatRect &rect) {
    return rect.intersects(sf::FloatRect(this->getPosition().x,this->getPosition().y,this->getSize().x,this->getSize().y));
}