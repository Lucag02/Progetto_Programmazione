//
// Created by luca on 24/06/22.
//

#include "Enemy.h"
const float Enemy::moveTime=100;
float Enemy::timer=0;
Enemy::Enemy(ResourceManager &resources, float x, float y, int type) : GameCharacter(resources, x, y), type(
        static_cast<CharacterType>(type)),active(false),direction(sf::Vector2i(0,0)),dead(false),aggro(false){
    if (this->type==CharacterType::SKELETON) {
        scaleFactor=sf::Vector2f(1.3,1.3);
        sprite = sf::Sprite(resources.getTexture("SKELETON"));
        sprite.setTextureRect(sf::IntRect(0, 0, 50, 48));
        sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
        sprite.setScale(scaleFactor);
        sprite.setPosition(sf::Vector2f(x, y));
        hitbox = std::make_unique<Hitbox>(sprite, 25.f, 40.f, false,10,15);
        damageHitbox=std::make_unique<Hitbox>(sprite,20.f,40.f,true);
        animation=AnimationName::MOVE;
        attackDistance=47;
    }
    else{
        sprite = sf::Sprite(resources.getTexture("SLIME"));
        scaleFactor=sf::Vector2f(1,1);
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 25));
        sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
        sprite.setPosition(sf::Vector2f(x, y));
        hitbox = std::make_unique<Hitbox>(sprite, 32.f, 18.f, false,15,5);
        damageHitbox=std::make_unique<Hitbox>(sprite,20.f,18.f,true);
        animation=AnimationName::MOVE;
        attackDistance=40;
    }
}

void Enemy::update(const float &dt, PlayableCharacter &player) {
    float distance= distanceToPlayer(player.getPosition());
    if(distance<800) {
        active = true;
        if (distance < 600)
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
        }else if(distance>attackDistance-10&&!resources.getAnimation(AnimationName::ATTACK).isPlaying())
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
        if(hp<1)
            dead=true;
    }
    if (dead && resources.getAnimation(AnimationName::DEATH).isPlaying()) {
        animation =AnimationName::DEATH;
        resources.playAnimation(animation, dt, sprite);
    } else if (active && !dead) {
        if (resources.getAnimation(AnimationName::ATTACK).isPlaying()|| distance < attackDistance) {
            animation = AnimationName::ATTACK;
            damageActive = true;
            if (sprite.getScale().x > 0)
                damageHitbox->setPosition(hitbox->getPosition().x + hitbox->getSize().x, hitbox->getPosition().y);
            else
                damageHitbox->setPosition(hitbox->getPosition().x - damageHitbox->getSize().x, hitbox->getPosition().y);
        } else {
            damageActive = false;
            animation = AnimationName::MOVE;
        }
        resources.playAnimation(animation, dt, sprite);
    }
}

void Enemy::render(sf::RenderTarget &target) {
    if(active) {
        target.draw(sprite);
#if DEBUG
        if(!dead) {
            target.draw(*hitbox);
            if (damageActive)
                target.draw(*damageHitbox);
            }
#endif
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



