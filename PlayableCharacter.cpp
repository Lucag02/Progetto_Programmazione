//
// Created by luca on 21/06/22.
//
#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(ResourceManager &resources, float x, float y, int HP, int m, float movespeed,
                                     float manaregen) : GameCharacter(resources, x, y, HP, m, movespeed, manaregen),
                                                        animationLock(false), hardLock(false){
    animation=AnimationName::IDLE;
    lockAnimation=AnimationName::IDLE;
    //moveSpeed=1000;
    scaleFactor=sf::Vector2f (1.4,1.4);
    sprite=sf::Sprite(resources.getTexture("KNIGHT"));
    sprite.setTextureRect(sf::IntRect(0,0,50,37));
    sprite.setScale(scaleFactor);
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(sf::Vector2f(x,y));
    hitbox= std::make_unique<Hitbox>(sprite,20.f,37.f,false,10,15);
    damageHitbox=std::make_unique<Hitbox>(sprite,20.f,40.f,true);
}

void PlayableCharacter::update(const float &dt) {
    sf::Vector2f move=sf::Vector2f(0,0);
    animation=AnimationName::IDLE;
    if(!hardLock) {
        if (!animationLock&&sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            lockAnimation = AnimationName::ATTACK;
            animationLock = true;
            hardLock=true;
        } else{
            prevPos=sprite.getPosition();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                move.x-=1;
                animation = AnimationName::MOVE;
                sprite.setScale(-scaleFactor.x, scaleFactor.y);
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = AnimationName::ROLL;
                    animationLock = true;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                move.y+=1;
                animation = AnimationName::MOVE;
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = AnimationName::ROLL;
                    animationLock = true;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                move.x+=1;
                animation = AnimationName::MOVE;
                sprite.setScale(scaleFactor);
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = AnimationName::ROLL;
                    animationLock = true;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                move.y-=1;
                animation = AnimationName::MOVE;
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = AnimationName::ROLL;
                    animationLock = true;
                }
            }
        }
    }
    if(animationLock)
        animation=lockAnimation;
    if(animation==AnimationName::ROLL) {
        move.x *= 1.6;
        move.y *= 1.6;
    }
    sprite.move(move*dt*moveSpeed);
    hitbox->setPosition(sprite.getPosition().x - hitbox->getOffsetX(), sprite.getPosition().y - hitbox->getOffsetY());
    if(animation==AnimationName::ATTACK&&resources.getAnimation(animation).getAnimationFrame()>2&&resources.getAnimation(animation).getAnimationFrame()<6) {
        damageActive = true;
        if(sprite.getScale().x>0)
            damageHitbox->setPosition(hitbox->getPosition().x + hitbox->getSize().x, hitbox->getPosition().y);
        else
            damageHitbox->setPosition(hitbox->getPosition().x - damageHitbox->getSize().x, hitbox->getPosition().y);
    }
    else
        damageActive=false;
    resources.playAnimation(animation,dt,sprite);
}

void PlayableCharacter::render(sf::RenderTarget &target) {
    target.draw(sprite);
#if DEBUG
    target.draw(*hitbox);
    if(damageActive)
        target.draw(*damageHitbox);
#endif
}

PlayableCharacter::~PlayableCharacter() {

}


bool PlayableCharacter::isAnimationLocked() const {
    return animationLock;
}

void PlayableCharacter::setAnimationLock(bool lock) {
    animationLock=lock;
    hardLock=lock;
}

bool PlayableCharacter::isAnimationPlaying() {
    return resources.getAnimation(animation).isPlaying();
}

void PlayableCharacter::setPosition(float x, float y) {
    sprite.setPosition(x,y);
}

sf::Vector2f PlayableCharacter::getPosition() {
    return sprite.getPosition();
}

const sf::Vector2f &PlayableCharacter::getPrevPos() {
    return prevPos;
}

void PlayableCharacter::move(float x, float y) {
    sprite.move(x,y);
    hitbox->move(x,y);
}

bool PlayableCharacter::isAttacking() const {
    return damageActive;
}

Hitbox &PlayableCharacter::getDamageHitbox() {
    return *damageHitbox;
}

