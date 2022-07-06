//
// Created by luca on 21/06/22.
//
#include "PlayableCharacter.h"

PlayableCharacter::PlayableCharacter(ResourceManager &resources, std::vector<ResourceManager> &abilityResources,
                                     float x, float y,
                                     int HP, int m, int stamina, float movespeed, float manaregen) : GameCharacter(resources, x, y, HP, m, movespeed, manaregen),
                                                        animationLock(false), hardLock(false),stamina(stamina),maxStamina(stamina),
                                                        maxHP(HP),ability(THUNDER),abilityResources(abilityResources){
    //moveSpeed=1000;
    animation=AnimationName::IDLE;
    lockAnimation=AnimationName::IDLE;
    scaleFactor=sf::Vector2f (1.4,1.4);
    sprite=sf::Sprite(resources.getTexture("KNIGHT"));
    sprite.setTextureRect(sf::IntRect(0,0,50,37));
    sprite.setScale(scaleFactor);
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(sf::Vector2f(x,y));
    hitbox= std::make_unique<Hitbox>(sprite,20.f,37.f,false,10,15);
    damageHitbox=std::make_unique<Hitbox>(sprite,20.f,40.f,true);
}

void PlayableCharacter::update(const float &dt, sf::Vector2f mousePos) {
    sf::Vector2f move=sf::Vector2f(0,0);
    animation=AnimationName::IDLE;
    stamina++;
    if(stamina>maxStamina)
        stamina=maxStamina;
    if(!hardLock) {
        if (!animationLock&&sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            lockAnimation = AnimationName::ATTACK;
            animationLock = true;
            hardLock=true;
        } else {
            if (!animationLock && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if(mousePos.x-sprite.getPosition().x>0)
                    sprite.setScale(scaleFactor.x, scaleFactor.y);
                else
                    sprite.setScale(-scaleFactor.x, scaleFactor.y);
                lockAnimation = AnimationName::ABILITY;
                animationLock = true;
                hardLock=true;
            }
            else {
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
                if (!animationLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && stamina > 40&&(move.x!=0||move.y!=0)) {
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
        stamina-=2;
        if(stamina<0)
            stamina=0;
    }
    sprite.move(move*dt*moveSpeed);
    hitbox->setPosition(sprite.getPosition().x - hitbox->getOffsetX(), sprite.getPosition().y - hitbox->getOffsetY());
    if(animation==AnimationName::ATTACK&&resources.getAnimation(animation).getAnimationFrame()>2&&
            resources.getAnimation(animation).getAnimationFrame()<6) {
        damageActive = true;
        if(sprite.getScale().x>0)
            damageHitbox->setPosition(hitbox->getPosition().x + hitbox->getSize().x, hitbox->getPosition().y);
        else
            damageHitbox->setPosition(hitbox->getPosition().x - damageHitbox->getSize().x, hitbox->getPosition().y);
    }
    else
        damageActive=false;
    resources.playAnimation(animation,dt,sprite);
    if(animation==AnimationName::ABILITY && !resources.getAnimation(animation).isPlaying())
        projectiles.emplace_back(std::make_unique<Projectile>(abilityResources[ability],mousePos,
                                                              sprite.getPosition().x,sprite.getPosition().y));
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

PlayableCharacter::~PlayableCharacter() {

}

void PlayableCharacter::equipAbility(AbilityType newAbility) {
    ability=newAbility;
}

