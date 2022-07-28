//
// Created by luca on 03/07/22.
//

#include "Item.h"
#include "PlayableCharacter.h"
Item::Item(const sf::Texture &texture, const sf::Font &font, float x, float y, int type)
        : type(static_cast<ItemType>(type)), onGround(true), showText(false), used(false) {
    shape.setPosition(x,y);
    shape.setSize(sf::Vector2f(32,32));
    shape.setTexture(&texture);
    description.setFont(font);
    description.setCharacterSize(15);
    description.setPosition(x+42,y+10);
    description.setFillColor(sf::Color::White);
    switch(this->type){
        case(ItemType::HEALING_POTION):
            shape.setTextureRect(sf::IntRect(2 * 32, 25 * 32, 32, 32));
            description.setString("Restore 30 HP");
            break;
        case(ItemType::SPEED_POTION):
            shape.setTextureRect(sf::IntRect(3 * 32, 25 * 32, 32, 32));
            description.setString("Increase your movement speed");
            break;
        case(ItemType::THUNDERSTORM_ABILITY):
            shape.setTextureRect(sf::IntRect(16 * 32, 42 * 32, 32, 32));
            description.setString("Equip Thunderstorm ability");
            break;
    }
    shape.setScale(0.7,0.7);
}

void Item::update(PlayableCharacter &player, sf::Vector2f mousePos) {
    description.setPosition(shape.getPosition().x+80,shape.getPosition().y+30);
    if(onGround && player.getHitbox().getGlobalBounds().intersects(shape.getGlobalBounds())) {
        onGround = false;
    }
    if(shape.getGlobalBounds().contains(mousePos)) {
        showText = true;
        if(!onGround && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            use(player);
    }
    else
        showText=false;
}

void Item::render(sf::RenderTarget &target) {
    target.draw(shape);
    if(showText)
        target.draw(description);
}

void Item::use(PlayableCharacter &player) {
    used=true;
    switch(type){
        case(ItemType::HEALING_POTION):
            player.heal(50);
            break;
        case(ItemType::SPEED_POTION):
            player.increaseSpeed(10.f);
            break;
        case(ItemType::THUNDERSTORM_ABILITY):
            player.equipAbility(THUNDER_STORM);
            break;
    }
}

void Item::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
}

bool Item::isUsed() const {
    return used;
}

bool Item::isOnGround() const {
    return onGround;
}

void Item::setScale(sf::Vector2f scale) {
    shape.setScale(scale);
}
