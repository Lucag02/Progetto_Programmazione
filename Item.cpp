//
// Created by luca on 03/07/22.
//

#include "Item.h"
const int Item::maxItems=32;
Item::Item(const sf::Texture &texture, const sf::Font &font, float x, float y, int type)
        : type(static_cast<ItemType>(type)), isOnGround(true), showText(false) {
    shape.setPosition(x,y);
    shape.setSize(sf::Vector2f(32,32));
    shape.setTexture(&texture);
    description.setFont(font);
    description.setCharacterSize(15);
    description.setPosition(x+42,y+10);
    description.setFillColor(sf::Color::White);
    if(this->type==ItemType::HEALING_POTION) {
        shape.setTextureRect(sf::IntRect(2 * 32, 25 * 32, 32, 32));
        description.setString("Restore 30 HP");
    }
    else if(this->type==ItemType::SPEED_POTION) {
        shape.setTextureRect(sf::IntRect(3 * 32, 25 * 32, 32, 32));
        description.setString("Increase your movement speed");
    }
    shape.setScale(0.7,0.7);
}

void Item::update(PlayableCharacter &player, sf::Vector2f mousePos, std::list<std::unique_ptr<Item>> &groundItems,
                  std::list<std::unique_ptr<Item>> &inventory) {
    description.setPosition(shape.getPosition().x+80,shape.getPosition().y+30);
    if(isOnGround && inventory.size()<maxItems&&player.getHitbox().getGlobalBounds().intersects(shape.getGlobalBounds())) {
        isOnGround = false;
        shape.setScale(2,2);
        for(auto item=groundItems.begin();item!=groundItems.end();item++){
            if((*item).get()==this) {
                inventory.emplace_back(std::move(*item));
                groundItems.erase(item);
                break;
            }

        }
    }
    if(shape.getGlobalBounds().contains(mousePos)) {
        showText = true;
        if(!isOnGround&&sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            use(player);
            inventory.erase(std::find_if(inventory.begin(),inventory.end(),
                                         [this](std::unique_ptr<Item>& item){return item.get()==this;}));
        }
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
    switch(type){
        case(ItemType::HEALING_POTION):
            player.heal(50);
            break;
        case(ItemType::SPEED_POTION):
            player.increaseSpeed(10.f);
            break;
    }
}

void Item::setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
}
