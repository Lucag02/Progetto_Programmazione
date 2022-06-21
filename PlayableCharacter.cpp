//
// Created by luca on 21/06/22.
//

#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(const ResourceManager &resources, int HP, int m, float x, float y, float movespeed,
                                     float manaregen) : GameCharacter(resources,HP, m, x, y, movespeed, manaregen){
    sprite=sf::Sprite(*resources.getTexture("IDLE_ANIMATION"));
    sprite.setTextureRect(sf::IntRect(0,0,120,80));
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(sf::Vector2f(x,y));
}

void PlayableCharacter::update(const float &dt) {

}

void PlayableCharacter::render(sf::RenderTarget &target) {
    target.draw(sprite);
}

PlayableCharacter::~PlayableCharacter() {

}

sf::Vector2f PlayableCharacter::getPosition() {
    return sprite.getPosition();
}
