//
// Created by luca on 21/06/22.
//
#include "PlayableCharacter.h"
#define DEBUG 1
PlayableCharacter::PlayableCharacter(ResourceManager &resources, float x, float y, int HP, int m, float movespeed,
                                     float manaregen) : GameCharacter(resources, x, y, HP, m, movespeed, manaregen),
                                                        animationLock(false), hardLock(false){
#if DEBUG
    moveSpeed=1000;
#endif
    sprite=sf::Sprite(resources.getTexture("IDLE_ANIMATION"));
    sprite.setTextureRect(sf::IntRect(0,0,120,80));
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(sf::Vector2f(x,y));
    hitbox= std::make_unique<Hitbox>(sprite,20.f,37.f,false,10,-3);
}

void PlayableCharacter::update(const float &dt) {
    animation="IDLE_ANIMATION";
    if(!hardLock) {
        if (!animationLock&&sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            lockAnimation = "ATTACK_ANIMATION";
            animationLock = true;
            hardLock=true;
        } else{
            prevPos=sprite.getPosition();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                sprite.move(-1 * dt * moveSpeed, 0);
                animation = "RUN_ANIMATION";
                sprite.setScale(-1, 1);
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = "ROLL_ANIMATION";
                    animationLock = true;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                sprite.move(0, 1 * dt * moveSpeed);
                animation = "RUN_ANIMATION";
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = "ROLL_ANIMATION";
                    animationLock = true;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                sprite.move(1 * dt * moveSpeed, 0);
                animation = "RUN_ANIMATION";
                sprite.setScale(1, 1);
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = "ROLL_ANIMATION";
                    animationLock = true;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                sprite.move(0, -1 * dt * moveSpeed);

                animation = "RUN_ANIMATION";
                if (!animationLock&&sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    lockAnimation = "ROLL_ANIMATION";
                    animationLock = true;
                }
            }
        }
    }
    if(animationLock)
        animation=lockAnimation;
    hitbox->setPosition(sprite.getPosition().x - hitbox->getOffsetX(), sprite.getPosition().y - hitbox->getOffsetY());
    resources.playAnimation(animation,dt,sprite);
}

void PlayableCharacter::render(sf::RenderTarget &target) {
    target.draw(sprite);
#if DEBUG
    target.draw(*hitbox);
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

