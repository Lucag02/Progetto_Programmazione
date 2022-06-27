//
// Created by luca on 21/06/22.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#define PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
#include "GameCharacter.h"
#include "Hitbox.h"
class PlayableCharacter: public GameCharacter{
public:
    explicit PlayableCharacter(ResourceManager &resources, float x = 0, float y = 0, int HP = 10, int m = 0,
                               float movespeed = 150, float manaregen = 2);

    bool isAnimationLocked() const;
    void setAnimationLock(bool lock);
    bool isAnimationPlaying();
    void update(const float &dt);
    void render(sf::RenderTarget& target) override;
    void setPosition(float x, float y);
    const sf::Vector2f& getPrevPos();
    void move(float x,float y);
    bool isAttacking() const;
    Hitbox& getDamageHitbox();
    ~PlayableCharacter() override;
    sf::Vector2f getPosition();
private:
    std::unique_ptr<Hitbox> damageHitbox;
    bool damageActive;
    bool animationLock;
    bool hardLock;
    std::string animation;
    std::string lockAnimation;
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYABLECHARACTER_H
