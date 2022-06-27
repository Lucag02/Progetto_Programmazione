//
// Created by luca on 24/06/22.
//

#include "Enemy.h"
const float Enemy::moveTime=2000;
Enemy::Enemy(ResourceManager &resources, float x, float y, int type) : GameCharacter(resources, x, y), type(
        static_cast<enemyType>(type)),active(false),direction(sf::Vector2i(0,0)),timer(0){
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

void Enemy::update(const float &dt, PlayableCharacter &player) {
    if(distanceToPlayer(player.getPosition())<800)
        active=true;
    else
        active=false;
    if(active) {
        timer += dt * 1000;
        prevPos = sprite.getPosition();
        if (timer > moveTime || (direction.x == 0 && direction.y == 0)) {
            timer -= moveTime;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(-1, 1);
            direction.x = distr(gen);
            direction.y = distr(gen);
            sprite.move(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt);
        } else
            sprite.move(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt);
        hitbox->setPosition(sprite.getPosition().x - hitbox->getOffsetX(),
                            sprite.getPosition().y - hitbox->getOffsetY());
        //FIXME stutter when moving during collision and clip in wall if pushed
        if (player.getHitbox().intersects(hitbox->getGlobalBounds())) {
            sprite.setPosition(prevPos);
            sf::Vector2f move = player.getPrevPos() - player.getPosition();
            sprite.move(-move.x, -move.y);
            player.move(move.x, move.y);
        }
        if (type == enemyType::SLIME)
            resources.playAnimation("SLIME_MOVE", dt, sprite);
        else
            resources.playAnimation("SKELETON_MOVE", dt, sprite);
    }
}

void Enemy::render(sf::RenderTarget &target) {
    if(active) {
        target.draw(sprite);
        target.draw(*hitbox);
        }
}

float Enemy::distanceToPlayer(sf::Vector2f playerPos) {
    return sqrt(pow(playerPos.x-sprite.getPosition().x,2)+pow(playerPos.y-sprite.getPosition().y,2));
}



