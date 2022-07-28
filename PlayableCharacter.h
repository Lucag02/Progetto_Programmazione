//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#include "GameCharacter.h"
#include "Hitbox.h"
#include "Inventory.h"
#include "Subject.h"
enum AbilityType:int {THUNDER=0,THUNDER_STORM};
class PlayableCharacter: public GameCharacter,public Subject{
public:
    explicit PlayableCharacter(ResourceManager &resources, std::vector<ResourceManager> &abilityResources,CharacterType type=KNIGHT,
                               float x = 0, float y = 0, int HP = 300, int m = 200, int stamina = 200,float movespeed = 150,
                               float manaregen = 0.1);
    void registerObserver(Observer* o) override;
    void notifyObserver(const float &dt) override;
    void removeObservers(Observer* o) override;
    bool isAnimationLocked() const;
    void setAnimationLock(bool lock);
    bool isAnimationPlaying() const;
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
    float getMana() const;
    void heal(int heal);
    AbilityType ability;
    std::vector<ResourceManager>& abilityResources;
    std::list<std::unique_ptr<Projectile>> projectiles;
    std::list<std::unique_ptr<Projectile>>& getProjectiles();
    AnimationName getAnimation();
    Hitbox & getHitbox() const override;
    void increaseSpeed(float speedIncrease);
    void equipAbility(AbilityType newAbility);
    Inventory& getInventory() const;
    void addKill();
    ~PlayableCharacter() override;
private:
    std::unique_ptr<Inventory>inventory;
    std::list<Observer*> observers;
    int monstersKilled;
    int spellsCast;
    float maxMana;
    bool dead;
    CharacterType type;
    int maxHP;
    int maxStamina;
    int stamina;
    bool animationLock;
    bool hardLock;
    AnimationName lockAnimation;
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H