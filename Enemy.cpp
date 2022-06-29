//
// Created by luca on 24/06/22.
//

#include "Enemy.h"
const float Enemy::moveTime=100;
float Enemy::timer=0;
Enemy::Enemy(ResourceManager &resources, float x, float y, int type) : GameCharacter(resources, x, y), type(
        static_cast<enemyType>(type)),active(false),direction(sf::Vector2i(0,0)),dead(false),isdying(false),aggro(false){
    if (this->type==enemyType::SKELETON) {
        scaleFactor=sf::Vector2f(1.3,1.3);
        sprite = sf::Sprite(resources.getTexture("SKELETON"));
        sprite.setTextureRect(sf::IntRect(0, 0, 50, 48));
        sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
        sprite.setScale(scaleFactor);
        sprite.setPosition(sf::Vector2f(x, y));
        hitbox = std::make_unique<Hitbox>(sprite, 25.f, 40.f, false,10,15);
    }
    else{
        sprite = sf::Sprite(resources.getTexture("SLIME"));
        scaleFactor=sf::Vector2f(-1,1);
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 25));
        sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
        sprite.setPosition(sf::Vector2f(x, y));
        hitbox = std::make_unique<Hitbox>(sprite, 32.f, 18.f, false,15,5);
    }
}

void Enemy::update(const float &dt, PlayableCharacter &player) {
    if(distanceToPlayer(player.getPosition())<800) {
        active = true;
        if (distanceToPlayer(player.getPosition()) < 600)
            aggro = true;
        else
            aggro=false;
    }
    else  {
        active = false;
        aggro=false;
    }
    if(active&&!dead) {
        prevPos = sprite.getPosition();
        if (direction.x > 0)
            sprite.setScale(1 * scaleFactor.x, 1 * scaleFactor.y);
        else if (direction.x < 0)
            sprite.setScale(-1 * scaleFactor.x, 1 * scaleFactor.y);
        if ((timer > moveTime || (direction.x == 0 && direction.y == 0))&&!aggro) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(-1, 1);
            direction.x = distr(gen);
            direction.y = distr(gen);

            sprite.move(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt);
        }else
            sprite.move(direction.x * moveSpeed * dt, direction.y * moveSpeed * dt);
        hitbox->setPosition(sprite.getPosition().x - hitbox->getOffsetX(),
                            sprite.getPosition().y - hitbox->getOffsetY());
        //FIXME collision don't work properly
        if (player.getHitbox().intersects(hitbox->getGlobalBounds())) {
            sprite.setPosition(prevPos);
            sf::Vector2f move = player.getPrevPos() - player.getPosition();
            sprite.move(-move.x/2, -move.y/2);
            hitbox->move(-move.x/2, -move.y/2);
            player.move(move.x/2, move.y/2);
            if (player.getHitbox().intersects(hitbox->getGlobalBounds())) {
                sprite.move(move.x/2, move.y/2);
                hitbox->move(move.x/2, move.y/2);
            }
            if (player.getHitbox().intersects(hitbox->getGlobalBounds()))
                player.move(move.x/2, move.y/2);
        }
        if (player.isAttacking() && player.getDamageHitbox().intersects(hitbox->getGlobalBounds()))
            hp -= 10;
        if(hp<1) {
            dead=true;
            isdying=true;
        }
    }
    if (type == enemyType::SLIME) {
        if(isdying&&resources.getAnimation(AnimationName::SLIME_DEATH).isPlaying()) {
            resources.playAnimation(AnimationName::SLIME_DEATH, dt, sprite);
        }
        else
            if(active&&!dead)
                resources.playAnimation(AnimationName::SLIME_MOVE, dt, sprite);
    }
    else {
        if (isdying) {
            resources.playAnimation(AnimationName::SKELETON_DEATH, dt, sprite);
            if (!resources.getAnimation(AnimationName::SKELETON_DEATH).isPlaying())
                isdying = false;

        } else if (active && !dead)
            resources.playAnimation(AnimationName::SKELETON_MOVE, dt, sprite);
    }

}

void Enemy::render(sf::RenderTarget &target) {
    if(active) {
        target.draw(sprite);
        //target.draw(*hitbox);
    }
}

float Enemy::distanceToPlayer(sf::Vector2f playerPos) {
    return sqrt(pow(playerPos.x-sprite.getPosition().x,2)+pow(playerPos.y-sprite.getPosition().y,2));
}

void Enemy::updateTimer(const float &dt) {
    timer+=dt*1000;
}

bool Enemy::isAggroed() const {
    return aggro;
}

void Enemy::setDirection(const sf::Vector2i &dir) {
    direction=dir;
}

bool Enemy::canChangeDirection() {
    return timer>moveTime;
}

void Enemy::resetTimer() {
    if(timer>moveTime)
        timer-=moveTime;
}



