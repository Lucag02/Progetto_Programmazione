//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#include "GameCharacter.h"
#include "Hitbox.h"

enum AbilityType:int {THUNDER=0,THUNDER_STORM};
class PlayableCharacter: public GameCharacter{
public:
    explicit PlayableCharacter(ResourceManager &resources, std::vector<ResourceManager> &abilityResources,CharacterType type=KNIGHT,
                               float x = 0, float y = 0, int HP = 300, int m = 0, int stamina = 200,float movespeed = 150,
                               float manaregen = 2);
    bool isAnimationLocked() const;
    void setAnimationLock(bool lock);
    bool isAnimationPlaying();
    void update(const float &dt, sf::Vector2f mousePos);
    void render(sf::RenderTarget& target) override;
    void setPosition(float x, float y);
    const sf::Vector2f& getPrevPos();
    void move(float x,float y);
    bool isAttacking() const;
    Hitbox& getDamageHitbox();
    sf::Vector2f getPosition();
    int getHealth() const;
    int getStamina() const;
    void getHit(int damage);
    void heal(int heal);
    AbilityType ability;
    std::vector<ResourceManager>& abilityResources;
    std::list<std::unique_ptr<Projectile>> projectiles;
    std::list<std::unique_ptr<Projectile>>& getProjectiles();
    void increaseSpeed(float speedIncrease);
    void equipAbility(AbilityType newAbility);
    ~PlayableCharacter() override;
private:
    CharacterType type;
    int maxHP;
    int maxStamina;
    int stamina;
    bool animationLock;
    bool hardLock;
    AnimationName lockAnimation;
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H