//
// Created by luca on 14/07/22.
//

#include "Inventory.h"

Inventory::Inventory(int size) : size(size) {
    background.setSize(sf::Vector2f(600, 320));
    background.setFillColor(sf::Color(0, 0, 0, 100));
    for (int i = 0; i < size; i++)
        containers.emplace_back();
    for (auto &i: containers) {
        i.setFillColor(sf::Color(224, 224, 224, 100));
        i.setSize(sf::Vector2f(64, 64));
    }
}

void Inventory::updatePosition(sf::Vector2f viewPos) {
    background.setPosition(viewPos.x + 100, viewPos.y + 55);
    int sizeX = background.getSize().x / containers[0].getSize().x - 1;
    int sizeY = background.getSize().y / containers[0].getSize().y - 1;
    for (int i = 0; i < sizeX; i++)
        for (int j = 0; j < sizeY; j++)
            containers[i * sizeY + j].setPosition(viewPos.x + 110 + i * 74, viewPos.y + 65 + j * 74);
    int i = 0;
    for (auto &item: items) {
        item->setPosition(containers[i++].getPosition());
    }
}

void Inventory::render(sf::RenderTarget &target) {
    target.draw(background);
    for (const auto &container: containers)
        target.draw(container);
    if (!items.empty()) {
        auto item = items.end();
        item--;
        while (item != items.begin()) {
            (*item)->render(target);
            item--;
        }
        (*item)->render(target);
    }
}

void Inventory::update(PlayableCharacter &player, sf::Vector2f mousePos) {
    auto item=items.begin();
    while(item!=items.end()){
        (*item)->update(player,mousePos);
        if((*item)->isUsed()) {
            auto tmp=item;
            item++;
            items.erase(tmp);
        }
        else
            item++;
    }
}

void Inventory::add(std::unique_ptr<Item> item) {
    items.emplace_back(std::move(item));
}

int Inventory::getMaxSize() {
    return size;
}

int Inventory::getCurrentSize() {
    return items.size();
}
