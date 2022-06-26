//
// Created by luca on 24/06/22.
//

#include "Enemy.h"

Enemy::Enemy(ResourceManager &resources, float x, float y, int type) : GameCharacter(resources, x, y), type(
        static_cast<enemyType>(type)),active(false){
    if (this->type==enemyType::SKELETON) {
        sprite = sf::Sprite(resources.getTexture("SKELETON_MOVE"));
        sprite.setTextureRect(sf::IntRect(0, 0, 50, 48));
        sprite.setScale(1.3,1.3);
        sprite.setPosition(sf::Vector2f(x, y));
        hitbox = std::make_unique<Hitbox>(sprite, 25.f, 40.f, false,-15,-14);
    }
    else{
        sprite = sf::Sprite(resources.getTexture("SLIME_MOVE"));
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 25));
        sprite.setPosition(sf::Vector2f(x, y));
        hitbox = std::make_unique<Hitbox>(sprite, 32.f, 25.f, false);
    }
}

void Enemy::update(const float &dt) {
    if(type==enemyType::SLIME)
        resources.playAnimation("SLIME_MOVE",dt,sprite);
    else
        resources.playAnimation("SKELETON_MOVE",dt,sprite);
}

void Enemy::render(sf::RenderTarget &target) {
    target.draw(sprite);
    //target.draw(*hitbox);
}
