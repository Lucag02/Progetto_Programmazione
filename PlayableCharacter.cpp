//
// Created by luca on 21/06/22.
//
#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(ResourceManager &resources, std::vector<ResourceManager> &abilityResources,
                                     CharacterType type,
                                     float x, float y, int HP, int m, int stamina, float movespeed, float manaregen) :
                                                        GameCharacter(resources, x, y, HP, m, movespeed, manaregen),
                                                        animationLock(false), hardLock(false),stamina(stamina),maxStamina(stamina),dead(false),
                                                        maxHP(HP),ability(THUNDER),abilityResources(abilityResources),type(type),maxMana(m),
                                                        inventory(std::make_unique<Inventory>()),spellsCast(0),monstersKilled(0){
    animation=AnimationName::IDLE;
    lockAnimation=AnimationName::IDLE;
    switch(type) {
        case(KNIGHT):
            scaleFactor = sf::Vector2f(1.4, 1.4);
            sprite = sf::Sprite(resources.getTexture("KNIGHT"));
            sprite.setTextureRect(sf::IntRect(0, 0, 50, 37));
            sprite.setScale(scaleFactor);
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
            hitbox = std::make_unique<Hitbox>(sprite, 20.f, 37.f, false, 10, 15);
            damageHitbox = std::make_unique<Hitbox>(sprite, 20.f, 40.f, true);
            break;
        case(MAGE):
            scaleFactor = sf::Vector2f(1.2, 1.2);
            sprite = sf::Sprite(resources.getTexture("MAGE"));
            sprite.setTextureRect(sf::IntRect(0, 0, 56, 48));
            sprite.setScale(scaleFactor);
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2+8);
            hitbox = std::make_unique<Hitbox>(sprite, 20.f, 37.f, false, 10, 17);
            damageHitbox = std::make_unique<Hitbox>(sprite, 20.f, 40.f, true);
            break;
    }
    sprite.setPosition(sf::Vector2f(x, y));
}

void PlayableCharacter::update(const float &dt, sf::Vector2f mousePos) {
    sf::Vector2f move=sf::Vector2f(0,0);
    animation=AnimationName::IDLE;
    stamina+=dt*100;
    mana+=manaRegen*dt*100;
    if(hp<0) {
        dead = true;
        animation = AnimationName::DEATH;
    }
    if(mana>maxMana)
        mana=maxMana;
    if(stamina>maxStamina)
        stamina=maxStamina;
    if(!dead) {
        if (!hardLock) {
            if (!animationLock && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                lockAnimation = AnimationName::ATTACK;
                animationLock = true;
                hardLock = true;
            } else {
                if (!animationLock && sf::Mouse::isButtonPressed(sf::Mouse::Right) && mana >= 70) {
                    if (mousePos.x - sprite.getPosition().x > 0)
                        sprite.setScale(scaleFactor.x, scaleFactor.y);
                    else
                        sprite.setScale(-scaleFactor.x, scaleFactor.y);
                    lockAnimation = AnimationName::ABILITY;
                    animationLock = true;
                    hardLock = true;
                } else {
                    prevPos = sprite.getPosition();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                        move.x -= 1;
                        animation = AnimationName::MOVE;
                        sprite.setScale(-scaleFactor.x, scaleFactor.y);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                        move.y += 1;
                        animation = AnimationName::MOVE;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                        move.x += 1;
                        animation = AnimationName::MOVE;
                        sprite.setScale(scaleFactor);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                        move.y -= 1;
                        animation = AnimationName::MOVE;
                    }
                    if (!animationLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && stamina > 40 &&
                        (move.x != 0 || move.y != 0)) {
                        lockAnimation = AnimationName::ROLL;
                        animationLock = true;
                    }
                }
            }
        }
        if (animationLock)
            animation = lockAnimation;
        if (animation == AnimationName::ROLL) {
            move.x *= 1.6;
            move.y *= 1.6;
            stamina -= 2;
            if (stamina < 0)
                stamina = 0;
        }
        sprite.move(move * dt * moveSpeed);
        hitbox->setPosition(sprite.getPosition().x - hitbox->getOffsetX(),
                            sprite.getPosition().y - hitbox->getOffsetY());
        if (animation == AnimationName::ATTACK && resources.getAnimation(animation).getAnimationFrame() > 2 &&
            resources.getAnimation(animation).getAnimationFrame() < 6) {
            damageActive = true;
            if (sprite.getScale().x > 0)
                damageHitbox->setPosition(hitbox->getPosition().x + hitbox->getSize().x, hitbox->getPosition().y);
            else
                damageHitbox->setPosition(hitbox->getPosition().x - damageHitbox->getSize().x, hitbox->getPosition().y);
        } else
            damageActive = false;
        resources.playAnimation(animation, dt, sprite);
        if (animation == AnimationName::ABILITY && !resources.getAnimation(animation).isPlaying()) {
            projectiles.emplace_back(std::make_unique<Projectile>(abilityResources[ability], mousePos,
                                                                  sprite.getPosition().x, sprite.getPosition().y));
            mana -= 70;
            spellsCast++;
        }
    }
    else if(resources.getAnimation(AnimationName::DEATH).isPlaying())
        resources.playAnimation(animation,dt,sprite);
    auto projectile=projectiles.begin();
    while(projectile!=projectiles.end()) {
        (*projectile)->update(dt);
        if ((*projectile)->canErase()) {
            auto nextProjectile = ++projectile;
            projectiles.erase(--projectile);
            projectile=nextProjectile;
        }
        else
            projectile++;
    }
    notifyObserver(dt);
}

void PlayableCharacter::render(sf::RenderTarget &target) {
    target.draw(sprite);
    for(auto& projectile:projectiles)
        projectile->render(target);
#if DEBUG
    target.draw(*hitbox);
    if(damageActive)
        target.draw(*damageHitbox);
#endif
}

bool PlayableCharacter::isAnimationLocked() const {
    return animationLock;
}


void PlayableCharacter::setAnimationLock(bool lock) {
    animationLock=lock;
    hardLock=lock;
}

bool PlayableCharacter::isAnimationPlaying() const{
    return resources.getAnimation(animation).isPlaying();
}

void PlayableCharacter::setPosition(float x, float y) {
    sprite.setPosition(x,y);
    hitbox->setPosition(x - hitbox->getOffsetX(), y - hitbox->getOffsetY());
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

int PlayableCharacter::getHealth() const {
    return hp;
}

void PlayableCharacter::getHit(int damage) {
    hp-=damage;
}

int PlayableCharacter::getStamina() const {
    return stamina;
}

void PlayableCharacter::heal(int heal) {
    hp+=heal;
    if(hp>maxHP)
        hp=maxHP;
}

void PlayableCharacter::increaseSpeed(float speedIncrease) {
    moveSpeed+=speedIncrease;
}

std::list<std::unique_ptr<Projectile>>& PlayableCharacter::getProjectiles() {
    return projectiles;
}

Hitbox &PlayableCharacter::getHitbox() const {
    return GameCharacter::getHitbox();
}

void PlayableCharacter::equipAbility(AbilityType newAbility) {
    ability=newAbility;
}

float PlayableCharacter::getMana() const {
    return mana;
}

AnimationName PlayableCharacter::getAnimation() {
    return animation;
}

Inventory &PlayableCharacter::getInventory() const{
    return *inventory;
}

PlayableCharacter::~PlayableCharacter() {

}

void PlayableCharacter::registerObserver(Observer *o) {
    observers.push_back(o);
}

void PlayableCharacter::notifyObserver(const float &dt) {
    for (auto &observer: observers)
        observer->update(dt, sf::Vector2f(sprite.getPosition().x - 400, sprite.getPosition().y - 225),
                         monstersKilled, spellsCast);
}

void PlayableCharacter::removeObservers(Observer *o) {
    observers.remove(o);
}

void PlayableCharacter::addKill() {
    monstersKilled++;
}

