//
// Created by luca on 03/07/22.
//

#include "Item.h"

Item::Item(const sf::Texture &texture, float x, float y, int type):type(static_cast<ItemType>(type)),listPosition(0),isOnGround(true) {
    shape.setPosition(x,y);
    sf::Font font;
    font.loadFromFile("../Config/ComicSans.ttf");
    description.setFont(font);
    description.setCharacterSize(15);
    description.setPosition(x+42,y+10);
    description.setFillColor(sf::Color::White);
    if(this->type==ItemType::HEALING_POTION) {
        shape.setTextureRect(sf::IntRect(25 * 32, 2 * 32, 32, 32));
        description.setString("Restore 30 HP");
    }
    else if(this->type==ItemType::SPEED_POTION) {
        shape.setTextureRect(sf::IntRect(25 * 32, 3 * 32, 32, 32));
        description.setString("Increase your movement speed");
    }
    shape.setScale(0.5,0.5);
}

void Item::update(const Hitbox &hitbox, std::list<std::unique_ptr<Item>> &groundItems,
                  std::list<std::unique_ptr<Item>> &inventory) {
    if(isOnGround&&hitbox.getGlobalBounds().intersects(shape.getGlobalBounds())) {
        isOnGround = false;
        shape.setScale(1,1);
        for(auto& item: groundItems){
            if(item.get()==this) {
                inventory.emplace_back(std::move(item));
                groundItems.erase(std::find(groundItems.begin(), groundItems.end(),item));
                break;
            }

        }
    }
}

void Item::render(sf::RenderTarget &target) {

}
